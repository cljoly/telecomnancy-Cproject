#include "tools.h"
#include <gsl/gsl_matrix.h>
#include <stdlib.h>

/* Fichiers regroupant des outils généraux, notamment de débuggage */

/* Affichage d’une matrice de flotants */
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
