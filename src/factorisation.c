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

// Basé sur http://bit.ly/2qbhehb, avec les mêmes notations
/* Modification en place de P et Q, de manière à ce que P et Q constituent une
   factorisation approximative de R.
   K est le nombre de critères latents. */
void factor(gsl_matrix *R, gsl_matrix *P, gsl_matrix *Q, int K) {
  int steps = 5000;
  double alpha = 0.0002;
  double beta = 0.02;
  double close_enough = 0.001;

  gsl_vector *Q_row_i = gsl_vector_alloc(R->size2);
  gsl_vector *P_col_j = gsl_vector_alloc(R->size1);

  while (--steps > 0) {
    for (int i = 0; i < (int)R->size1; i++) {
      for (int j = 0; j < (int)R->size2; j++) {
        double r_ij = gsl_matrix_get(R, i, j);

        if (r_ij > 0) {
          gsl_matrix_get_row(Q_row_i, Q, i);
          gsl_matrix_get_col(P_col_j, P, j);

          double e_ij;
          // ddot est moins précis que dsdot, mais cela devrait suffire
          gsl_blas_ddot(Q_row_i, P_col_j, &e_ij);
          e_ij = r_ij - e_ij;

          for (int k = 0; k < K; k++) {
            double *pik = gsl_matrix_ptr(P, i, k);
            double *qkj = gsl_matrix_ptr(Q, k, j);

            *pik = *pik + alpha * (2 * e_ij * (*qkj) - beta * (*pik));
            *qkj = *qkj + alpha * (2 * e_ij * (*pik) - beta * (*qkj));
          }
        }
      }
    }

    /* eR = gsl_blas */
    double e = 0;
    for (int i = 0; i < (int) R->size1; i++) {
      for (int j = 0; j < (int) R->size2; j++) {
        double r_ij = gsl_matrix_get(R, i, j);
        if (r_ij > 0) {
          gsl_matrix_get_row(Q_row_i, Q, i);
          gsl_matrix_get_col(P_col_j, P, j);
          double e_ij;
          // ddot est moins précis que dsdot, mais cela devrait suffire
          gsl_blas_ddot(Q_row_i, P_col_j, &e_ij);
          e_ij = r_ij - e_ij;
          e += e_ij * e_ij;

          for (int k = 0; k < K; k++) {
            double *pik = gsl_matrix_ptr(P, i, k);
            double *qkj = gsl_matrix_ptr(Q, k, j);

            e += (beta / 2) * ((*pik) * (*pik)) + ((*qkj) * (*qkj));
          }
        }
      }
    }
    if (e < close_enough) {
      break;
    }
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
