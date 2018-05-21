#include "tools.h"
#include <gsl/gsl_matrix.h>
#include <stdlib.h>
#include <time.h>

/* Fichiers regroupant des outils généraux, notamment de débuggage */

void print_matrix(gsl_matrix *M) {
  int nb_row, nb_col;
  nb_row = M->size1;
  nb_col = M->size2;

  printf("[\n");
  for (int i = 0; i < nb_row; i++) {
    printf("[ ");
    for (int j = 0; j < nb_col; j++) {
      printf("%.4f", gsl_matrix_get(M, i, j));
      if (j != nb_col - 1)
        printf(", ");
      printf("\t");
    }
    printf(" ]\n");
  }
  printf("]\n");
}


gsl_matrix *gen_random_matrix(int nb_row, int nb_col) {

  // XXX Initialise random number generation only once
  static int seeded = 0;
  if (!seeded) {
    srand(time(NULL));
  }

  gsl_matrix *random_matrix = gsl_matrix_alloc(nb_row, nb_col);
  int mark;
  for (int row = 0; row < nb_row; row++) {
    for (int col = 0; col < nb_col; col++) {
      mark = (rand() % 5) + 1;
      gsl_matrix_set(random_matrix, row, col, (double)mark);
    }
  }
  return random_matrix;
}
