#include "factorisation.h"
#include "tools.h"
#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERBOSE 0
#define NAN_ERROR 0
#define LONG_TEST 0

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
  printf("Factorisation d’une matrice (k=%i, size1=%i, size2=%i)\n", k,
         (int)R->size1, (int)R->size2);

  // Time mesured with help from
  // https://stackoverflow.com/questions/7215764/how-to-measure-the-actual-execution-time-of-a-c-program-under-linux#7216613
  clock_t start, end;
  double cpu_time_used;

  start = clock();

  factorisation_mat *fm = initialize_mat(k, R);
  if (VERBOSE) {
    printf("R\n");
    print_matrix(fm->R);
  }
  if (VERBOSE >= 2) {
    printf("P\n");
    print_matrix(fm->P);
    printf("Q\n");
    print_matrix(fm->Q);
  }
  factor(fm, factorisation_alpha, factorisation_beta);
  if (VERBOSE) {
    printf("P =");
    print_matrix(fm->P);
    printf("Q =");
    print_matrix(fm->Q);
  }

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  gsl_matrix *R_approx = gsl_matrix_alloc(R->size1, R->size2);
  gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, fm->P, fm->Q, 0, R_approx);
  if (VERBOSE) {
    printf("R appprox\n");
    print_matrix(R_approx);
  }
  if (is_nan_in_matrix(R_approx))
    printf("Matrice résultat invalide (NaN)\n");
  printf("Temps CPU : %f seconde(s)\n", cpu_time_used);
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
  gsl_matrix *R4 = gsl_matrix_alloc(70, 80);
  gsl_matrix *R5 = gsl_matrix_alloc(100, 100);

  init(R1, R1_val);
  printf("R1\n");
  run_test(R1, 2);
  run_test(R1, 3);
  printf("-----------------------\n");
  init_rdm(R2);
  run_test(R2, 3);
  run_test(R2, 5);
  run_test(R2, 7);
  printf("-----------------------\n");
  init_rdm(R3);
  if (NAN_ERROR)
    run_test(R3, 5);
  run_test(R3, 10);
  if (LONG_TEST) {
    run_test(R3, 20);
    run_test(R3, 30);
  }
  printf("-----------------------\n");
  init_rdm(R4);
  if (NAN_ERROR) {
    run_test(R4, 5);
    run_test(R4, 10);
  }
  run_test(R4, 20);
  if (LONG_TEST) {
    run_test(R4, 30);
    run_test(R4, 40);
    run_test(R4, 50);
    run_test(R4, 60);
  }
  printf("-----------------------\n");
  init_rdm(R5);
  run_test(R5, 20);
  if (LONG_TEST) {
    run_test(R5, 30);
    run_test(R5, 40);
    run_test(R5, 50);
    run_test(R5, 60);
    run_test(R5, 70);
    run_test(R5, 80);
    run_test(R5, 90);
  }

  rdm_free();

  return 0;
}
