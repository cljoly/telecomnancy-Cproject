#include "factorisation.h"
#include "tools.h"
#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>

// Test de la factorisation de matrice

// Remplissage aléatoire de matrice
void init_rdm(gsl_matrix *R) {
  srand(1); // Répétable
  int i, j;
  for (i = 0; i < (int)R->size1; i++) {
    for (j = 0; j < (int)R->size2; j++) {
      double mark = (rand() % 10) - 5;
      gsl_matrix_set(R, i, j, GSL_MAX(mark, 0));
    }
  }
}

// Remplissage de matrice
void init(gsl_matrix *R, int R_val[]) {
  int i, j;
  for (i = 0; i < (int)R->size1; i++) {
    for (j = 0; j < (int)R->size2; j++) {
      gsl_matrix_set(R, i, j, R_val[i * R->size1 + j]);
    }
  }
}

void run_test(gsl_matrix *R, int k) {
  printf("Factorizing a random matrix (k=%i)\n", k);

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
}

int main() {
  rdm_init();

  // Data
  gsl_matrix *R1 = gsl_matrix_alloc(3, 4);
  int R1_val[] = {
      4, 1, 1, 2, 5, 4, 5, 0, 0, 5, 0, 0,
  };
  gsl_matrix *R2 = gsl_matrix_alloc(9, 8);
  gsl_matrix *R3 = gsl_matrix_alloc(30, 40);

  init(R1, R1_val);
  printf("R1\n");
  run_test(R1, 2);
  printf("-----------------------\n");
  init_rdm(R2);
  run_test(R2, 5);
  printf("-----------------------\n");
  init_rdm(R3);
  run_test(R3, 10);

  rdm_free();

  return 0;
}
