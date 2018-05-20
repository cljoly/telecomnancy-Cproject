#include "factorisation.h"
#include "tools.h"
#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Création d’une matrice remplie de notes aléatoires, dans [1,5]. 0 marque
   l’absence de note et est présent à hauteur d’environ 60 %
   TODO Faire varier la proportion de films non notés */
gsl_matrix *gen_random_matrix(int nb_row, int nb_col) {
  gsl_matrix *random_matrix = gsl_matrix_alloc(nb_row, nb_col);
  // XXX Initialisation avec un nombre pour pouvoir reproduire les tests avec
  // les mêmes erreurs
  srand(10);
  int mark;
  for (int row = 0; row < nb_row; row++) {
    for (int col = 0; col < nb_col; col++) {
      mark = rand() % 20 - 5;
      mark = (mark >= 0 ? mark : 0);
      gsl_matrix_set(random_matrix, row, col, (double)mark);
    }
  }
  return random_matrix;
}

typedef struct {
  gsl_matrix *R;
  gsl_matrix *P;
  gsl_matrix *Q;
  gsl_vector *Q_col_j;   // Colonne j de Q
  gsl_vector *P_row_i;   // Ligne i de P
  double dot_product_QP; // Produit scalaire
  double alpha;
  double beta;
  int K;
  double e;    // Erreur
  double e_ij; // Erreur sur le coefficient i,j
} factor_context;

factorisation_mat *initialize_mat(int k, gsl_matrix *R) {
  factorisation_mat *fm = (factorisation_mat*) malloc(sizeof(factorisation_mat));
  fm->R = R;
  fm->P = gen_random_matrix(R->size1, k);
  fm->Q = gen_random_matrix(k, R->size2);
  return fm;
}

static void factor_walker(void (*g)(double r_ij, factor_context *ctxt),
                          void (*f)(double *p_ik, double *q_kj,
                                    factor_context *ctxt),
                          factor_context *ctxt) {
  for (int i = 0; i < (int)ctxt->R->size1; i++) {
    for (int j = 0; j < (int)ctxt->R->size2; j++) {

      double r_ij = gsl_matrix_get(ctxt->R, i, j);

      if (r_ij > 0) {
        gsl_matrix_get_col(ctxt->Q_col_j, ctxt->Q, j);
        gsl_matrix_get_row(ctxt->P_row_i, ctxt->P, i);
        // ddot est moins précis que dsdot, mais cela devrait suffire
        gsl_blas_ddot(ctxt->Q_col_j, ctxt->P_row_i, &ctxt->dot_product_QP);

        g(r_ij, ctxt);

        for (int k = 0; k < ctxt->K; k++) {
          double *p_ik = gsl_matrix_ptr(ctxt->P, i, k);
          double *q_kj = gsl_matrix_ptr(ctxt->Q, k, j);
          f(p_ik, q_kj, ctxt);
        }
      }
    }
  }
}

static void factor_eij_init(double r_ij, factor_context *ctxt) {
  ctxt->e_ij = r_ij - ctxt->dot_product_QP;
}

static void factor_error_init(double r_ij, factor_context *ctxt) {
  ctxt->e += pow(r_ij - ctxt->dot_product_QP, 2);
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
  ctxt->e += (ctxt->beta / 2) * pow(*p_ik, 2) + pow(*q_kj, 2);
}

// Basé sur http://bit.ly/2qbhehb, avec les mêmes notations
void factor(factorisation_mat *fm, double alpha, double beta) {
  int steps = 5000;
  double epsilon = 0.001;

  // Déduction de K
  assert(fm->Q->size1 == fm->P->size2);
  int K = fm->Q->size1;

  factor_context ctxt;
  ctxt.R = fm->R;
  ctxt.P = fm->P;
  ctxt.Q = fm->Q;
  ctxt.Q_col_j = gsl_vector_alloc(K);
  ctxt.P_row_i = gsl_vector_alloc(K);
  ctxt.alpha = alpha;
  ctxt.beta = beta;
  ctxt.K = K;
  ctxt.e = 0;
  ctxt.e_ij = 0;

  while (--steps > 0) {
    // Manipulation de P, Q
    factor_walker(factor_eij_init, factor_gradiant_update, &ctxt);

    // Mise à jour de l’erreur
    ctxt.e = 0;
    factor_walker(factor_error_init, factor_error_update, &ctxt);
    if (ctxt.e < epsilon)
      break;
  }
}

int main() {
  printf("Factorizing a random matrix\n");

  int size1 = 5;
  int size2 = 3;
  int k = 2;

  gsl_matrix *R = gen_random_matrix(size1, size2);
  factorisation_mat *fm = initialize_mat(k, R);
  printf("R\n");
  print_matrix(fm->R);
  factor(fm, factorisation_alpha, factorisation_beta);
  printf("P\n");
  print_matrix(fm->P);
  printf("Q\n");
  print_matrix(fm->Q);
  // Print product, supposed to be similar to R
  gsl_matrix *R_approx = gsl_matrix_alloc(R->size1, R->size2);
  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, fm->P, fm->Q, 0, R_approx);
  printf("R appprox\n");
  print_matrix(R_approx);

  return 0;
}

double factorisation_beta = 0.0002;
double factorisation_alpha = 0.02;
