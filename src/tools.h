#ifndef SRC_TOOLS_H
#define SRC_TOOLS_H


#include <gsl/gsl_matrix.h>
#include <stdlib.h>

/* Fichiers regroupant des outils généraux, notamment de débuggage */

void print_matrix(gsl_matrix *M);

gsl_matrix *gen_random_matrix(int nb_row, int nb_col);

#endif //SRC_TOOLS_H
