#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>

/* Generate random matrix, filled with mark like data, in [1,5] */
gsl_matrix *gen_random_matrix(int nb_row, int nb_col) {
  gsl_matrix *random_matrix = gsl_matrix_alloc(nb_row, nb_col);
  srand(6); // Initialize with a number for reproductability
  for (int row = 0; row < nb_row; row++) {
    for (int col = 0; col < nb_col; col++) {
      gsl_matrix_set(random_matrix, row, col, (rand() % 5) + 1);
    }
  }
  return random_matrix;
}

// Based on http://bit.ly/2qbhehb, same notation
/* In place modify P and Q, so that P and Q are a factorisation of R. K is the
   number of latent feature */
void factor(gsl_matrix *R, gsl_matrix *P, gsl_matrix *Q, int K) {
  int steps = 5000;
  double alpha = 0.0002;
  double beta = 0.02;
  double close_enough = 0.001;

  double r_ij;
  double e_ij;
  double e;
  gsl_vector *Q_row_i = gsl_vector_alloc(R->size2); // size2: number of column
  gsl_vector *P_col_j = gsl_vector_alloc(R->size1); // size1: number of row
  double *pik;
  double *qkj;
  while (--steps > 0) {
    for (unsigned long i = 0; i < R->size1; i++) {
      for (unsigned long j = 0; j < R->size2; j++) {
        r_ij = gsl_matrix_get(R, i, j);
        if (r_ij > 0) {
          gsl_matrix_get_row(Q_row_i, Q, i);
          gsl_matrix_get_col(P_col_j, P, j);
          // ddot is less precise than dsdot, but should be enough
          gsl_blas_ddot(Q_row_i, P_col_j, &e_ij);
          e_ij = r_ij - e_ij;
          for (int k = 0; k < K; k++) {
            pik = gsl_matrix_ptr(P, i, k);
            qkj = gsl_matrix_ptr(Q, k, j);
            *pik = *pik + alpha * (2 * e_ij * (*qkj) - beta * (*pik));
            *qkj = *qkj + alpha * (2 * e_ij * (*pik) - beta * (*qkj));
          }
        }
      }
    }
    /* eR = gsl_blas */
    e = 0;
    for (unsigned long i = 0; i < R->size1; i++) {
      for (unsigned long j = 0; j < R->size2; j++) {
        r_ij = gsl_matrix_get(R, i, j);
        if (r_ij > 0) {
          gsl_matrix_get_row(Q_row_i, Q, i);
          gsl_matrix_get_col(P_col_j, P, j);
          // ddot is less precise than dsdot, but should be enough
          gsl_blas_ddot(Q_row_i, P_col_j, &e_ij);
          e_ij = r_ij - e_ij;
          e = e + e_ij * e_ij;
          for (int k = 0; k < K; k++) {
            e = e + (beta / 2) * ((*pik) * (*pik)) + ((*qkj) * (*qkj));
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
