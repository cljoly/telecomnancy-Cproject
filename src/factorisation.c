#include <gsl/gsl_matrix.h>
#include <stdio.h>
#include <stdlib.h>

gsl_matrix *gen_random_matrix(int nb_line, int nb_col) {
  gsl_matrix *random_matrix = gsl_matrix_alloc(nb_line, nb_col);
  srand(6); // Initialize with a number for reproductability
  for (int line = 0; line < nb_line; line++) {
    for (int col = 0; col < nb_col; col++) {
      gsl_matrix_set(random_matrix, line, col, rand() / 10e4);
    }
  }
  return random_matrix;
}

int main() {
  printf("Printing a random matrix\n");

  int size = 10;
  gsl_matrix *random_matrix = gen_random_matrix(size, size);

  gsl_matrix_fprintf(stdout, random_matrix, "%f");

  return 0;
}
