#include "tools.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
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

// Seed random number generator
static int seeded = 0;
static const gsl_rng_type *T;
static gsl_rng *r;

void rdm_init() {
  if (!seeded) {
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_env_setup();
    seeded = 1;
  }
}

void rdm_free() {
  if (seeded)
    gsl_rng_free(r);
}

gsl_matrix *gen_random_matrix(int nb_row, int nb_col) {
  // Vérifier que le générateur de nombres aléatoires a été correctement
  // initialisé
  if (!seeded || r == NULL) {
    fprintf(
        stderr,
        "Problème à l’initialisation du générateur de nombres aléatoires\n");
  }

  gsl_matrix *random_matrix = gsl_matrix_alloc(nb_row, nb_col);
  for (int row = 0; row < nb_row; row++) {
    for (int col = 0; col < nb_col; col++) {
      gsl_matrix_set(random_matrix, row, col, gsl_rng_uniform(r));
    }
  }
  return random_matrix;
}

int is_nan_in_matrix(gsl_matrix *M) {
  int i, j;
  for (i = 0; i < (int)M->size1; i++)
    for (j = 0; j < (int)M->size2; j++)
      if (gsl_isnan(gsl_matrix_get(M, i, j)))
        return 1;
  return 0;
}
