#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>

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

// TODO Documenter
typedef struct {
  gsl_matrix *R;
  gsl_matrix *P;
  gsl_matrix *Q;
  gsl_vector *Q_row_i;
  gsl_vector *P_col_j;
  double alpha;
  double beta;
  int K;
  double e;
  double e_ij;
} factor_context;

static void factor_walker(void (*g)(factor_context *ctxt),
                          void (*f)(double *p_ik, double *q_kj,
                                    factor_context *ctxt),
                          factor_context *ctxt) {
  for (int i = 0; i < (int)ctxt->R->size1; i++) {
    for (int j = 0; j < (int)ctxt->R->size2; j++) {
      double r_ij = gsl_matrix_get(ctxt->R, i, j);

      if (r_ij > 0) {
        gsl_matrix_get_row(ctxt->Q_row_i, ctxt->Q, i);
        gsl_matrix_get_col(ctxt->P_col_j, ctxt->P, j);

        double e_ij;
        // ddot est moins précis que dsdot, mais cela devrait suffire
        gsl_blas_ddot(ctxt->Q_row_i, ctxt->P_col_j, &e_ij);
        g(ctxt);

        for (int k = 0; k < ctxt->K; k++) {
          double *p_ik = gsl_matrix_ptr(ctxt->P, i, k);
          double *q_kj = gsl_matrix_ptr(ctxt->Q, k, j);

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
  *p_ik = *p_ik + ctxt->alpha * (2 * ctxt->e_ij * (*q_kj) - ctxt->beta * (*p_ik));
  *q_kj = *q_kj + ctxt->alpha * (2 * ctxt->e_ij * (*p_ik) - ctxt->beta * (*q_kj));
}

static void factor_error_update(double *p_ik, double *q_kj,
                                factor_context *ctxt) {
  ctxt->e += (ctxt->beta / 2) * ((*p_ik) * (*p_ik)) + ((*q_kj) * (*q_kj));
}

// Basé sur http://bit.ly/2qbhehb, avec les mêmes notations
/* Modification en place de P et Q, de manière à ce que P et Q constituent une
   factorisation approximative de R.
   K est le nombre de critères latents. */
void factor(gsl_matrix *R, gsl_matrix *P, gsl_matrix *Q, int K) {
  // TODO Passer ces constantes en paramètres
  int steps = 5000;
  double close_enough = 0.001;

  factor_context ctxt;
  ctxt.R = R;
  ctxt.P = P;
  ctxt.Q = Q;
  ctxt.Q_row_i = gsl_vector_alloc(R->size2);
  ctxt.P_col_j = gsl_vector_alloc(R->size1);
  ctxt.alpha = 0.0002;
  ctxt.beta = 0.02;
  ctxt.K = K;
  ctxt.e = 0;
  ctxt.e_ij = 0;

  while (--steps > 0) {
    factor_walker(factor_nop, factor_gradiant_update, &ctxt);
    ctxt.e = 0;
    factor_walker(factor_error_init, factor_error_update, &ctxt);
    if (ctxt.e < close_enough)
      break;
  }
}

int main() {
  printf("Factorizing a random matrix\n");

  int size = 30;
  gsl_matrix *R = gen_random_matrix(size, size);

  int k = 5;
  gsl_matrix *P = gsl_matrix_alloc(R->size1, k);
  gsl_matrix *Q = gsl_matrix_alloc(k, R->size2);
  gsl_matrix_fprintf(stdout, R, "%f");
  factor(R, P, Q, k);
  gsl_matrix_fprintf(stdout, P, "%f");
  gsl_matrix_fprintf(stdout, Q, "%f");
  // Print product, supposed to be similar to R
  gsl_matrix *R_approx = gsl_matrix_alloc(R->size1, R->size2);
  gsl_matrix_fprintf(stdout, R_approx, "%f");

  return 0;
}
