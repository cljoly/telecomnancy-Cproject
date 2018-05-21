#ifndef SRC_TOOLS_H
#define SRC_TOOLS_H


#include <gsl/gsl_matrix.h>

/* Fichiers regroupant des outils généraux, notamment de débuggage */

/* Affichage d’une matrice de flotants */
void print_matrix(gsl_matrix *M);

/* Création d’une matrice remplie de nombres aléatoires, dans [1,6]. */
gsl_matrix *gen_random_matrix(int nb_row, int nb_col);

#endif //SRC_TOOLS_H
