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
