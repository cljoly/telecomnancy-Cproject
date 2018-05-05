#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHA 0.0002
#define BETA 0.002
#define DEBUG 1

/* Création d’une matrice remplie de notes aléatoires, dans [1,5]. 0 marque
   l’absence de note et est présent à hauteur d’environ 60 %
   TODO Faire varier la proportion de films non notés */
gsl_matrix *gen_random_matrix(int nb_row, int nb_col) {
  gsl_matrix *random_matrix = gsl_matrix_alloc(nb_row, nb_col);
  // XXX Initialisation avec un nombre pour pouvoir reproduire les tests avec
  // les mêmes erreurs
  srand(6);
  int mark;
  for (int row = 0; row < nb_row; row++) {
    for (int col = 0; col < nb_col; col++) {
      mark = rand() % 20 - 14;
      mark = (mark >= 0 ? mark : 0);
      gsl_matrix_set(random_matrix, row, col, mark);
    }
  }
  return random_matrix;
}

typedef struct {
  gsl_matrix *R;
  gsl_matrix *P;
  gsl_matrix *Q;
  gsl_vector *Q_col_i; // Ligne i de Q
  gsl_vector *P_row_j; // Colonne j de P
  double alpha;
  double beta;
  int K;
  double e;    // Erreur
  double e_ij; // Erreur sur le coefficient i,j
} factor_context;

static void factor_walker(void (*g)(factor_context *ctxt),
                          void (*f)(double *p_ik, double *q_kj,
                                    factor_context *ctxt),
                          factor_context *ctxt) {
  for (int i = 0; i < (int)ctxt->R->size1; i++) {
    for (int j = 0; j < (int)ctxt->R->size2; j++) {
      if (DEBUG)
        printf("i: %i, j: %i, size1: %lu; size2: %lu\n", i, j, ctxt->R->size1,
               ctxt->R->size2);

      double r_ij = gsl_matrix_get(ctxt->R, i, j);

      if (r_ij > 0) {
        if (DEBUG)
          printf("a\n");
        gsl_matrix_get_col(ctxt->Q_col_i, ctxt->Q, i);
        if (DEBUG)
          printf("a, %lu %i\n", ctxt->P->size2, ctxt->K);
        gsl_matrix_get_row(ctxt->P_row_j, ctxt->P, j);
        if (DEBUG)
          printf("a\n");

        double e_ij;
        // ddot est moins précis que dsdot, mais cela devrait suffire
        if (DEBUG)
          printf("c %lu %lu\n", ctxt->Q_col_i->size, ctxt->P_row_j->size);
        gsl_blas_ddot(ctxt->Q_col_i, ctxt->P_row_j, &e_ij);
        g(ctxt);

        for (int k = 0; k < ctxt->K; k++) {
          if (DEBUG)
            printf("b\n");
          double *p_ik = gsl_matrix_ptr(ctxt->P, i, k);
          if (DEBUG)
            printf("b\n");
          double *q_kj = gsl_matrix_ptr(ctxt->Q, k, j);
          if (DEBUG)
            printf("b\n");

          f(p_ik, q_kj, ctxt);
        }
      }
    }
  }
}

static void factor_nop(factor_context *ctxt) {}

static void factor_error_init(factor_context *ctxt) {
  ctxt->e = ctxt->e_ij * ctxt->e_ij;
}

static void factor_gradiant_update(double *p_ik, double *q_kj,
                                   factor_context *ctxt) {
  *p_ik =
      *p_ik + ctxt->alpha * (2 * ctxt->e_ij * (*q_kj) - ctxt->beta * (*p_ik));
  *q_kj =
      *q_kj + ctxt->alpha * (2 * ctxt->e_ij * (*p_ik) - ctxt->beta * (*q_kj));
}

static void factor_error_update(double *p_ik, double *q_kj,
                                factor_context *ctxt) {
  ctxt->e += (ctxt->beta / 2) * ((*p_ik) * (*p_ik)) + ((*q_kj) * (*q_kj));
}

// Basé sur http://bit.ly/2qbhehb, avec les mêmes notations
/* Modification en place de P et Q, de manière à ce que P et Q constituent une
   factorisation approximative de R.
   K est le nombre de critères latents.
   alpha est la vitesse d’approche. Utiliser la valeur de la macro en cas de
   doute. beta est un paramètre de convergeance. Utiliser la valeur de la macro
   en cas de doute.
*/
void factor(gsl_matrix *R, gsl_matrix *P, gsl_matrix *Q, int K, double alpha,
            double beta) {
  int steps = 5000;
  double epsilon = 0.001;

  factor_context ctxt;
  ctxt.R = R;
  ctxt.P = P;
  ctxt.Q = Q;
  ctxt.Q_col_i = gsl_vector_alloc(K);
  ctxt.P_row_j = gsl_vector_alloc(K);
  ctxt.alpha = alpha;
  ctxt.beta = beta;
  ctxt.K = K;
  ctxt.e = 0;
  ctxt.e_ij = 0;

  while (--steps > 0) {
    factor_walker(factor_nop, factor_gradiant_update, &ctxt);
    ctxt.e = 0;
    factor_walker(factor_error_init, factor_error_update, &ctxt);
    if (ctxt.e < epsilon)
      break;
  }
}

int main() {
  printf("Factorizing a random matrix\n");

  int size1 = 23;
  int size2 = 30;
  gsl_matrix *R = gen_random_matrix(size1, size2);

  int k = 5;
  gsl_matrix *P = gsl_matrix_alloc(R->size1, k);
  gsl_matrix *Q = gsl_matrix_alloc(k, R->size2);
  gsl_matrix_fprintf(stdout, R, "%f");
  factor(R, P, Q, k, ALPHA, BETA);
  gsl_matrix_fprintf(stdout, P, "%f");
  gsl_matrix_fprintf(stdout, Q, "%f");
  // Print product, supposed to be similar to R
  gsl_matrix *R_approx = gsl_matrix_alloc(R->size1, R->size2);
  gsl_matrix_fprintf(stdout, R_approx, "%f");

  return 0;
}
