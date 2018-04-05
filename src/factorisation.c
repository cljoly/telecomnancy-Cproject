#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_matrix.h>

int main() {
  printf("Printing a random matrix\n");

  int size = 10;
  gsl_matrix* random_matrix = gsl_matrix_alloc(size, size);
  if (random_matrix == NULL) return 1;

  srand(6); // Initialize with a number for reproductability
  for (int line=0; line<size; line++) {
    for (int col=0; col<size; col++) {
      gsl_matrix_set(random_matrix, line, col, rand()/10e4);
    }
  }

  gsl_matrix_fprintf(stdout, random_matrix, "%f");

  return 0;
}
