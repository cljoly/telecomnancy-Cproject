#include <assert.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Groupe P, R et Q */
typedef struct {
  gsl_matrix *R; // Matrix to be factorised
  gsl_matrix *P; // P*Q = R
  gsl_matrix *Q;
} factorisation_mat;

/*
  Création de la structure contenant la matrice et sa décomposition apporoximation.

  K est le nombre de critères latents et est déduit du nombres de lignes dans
  les matrices Q et P.
*/
factorisation_mat *initialize_mat(int K, gsl_matrix *R);

/* Modification en place de P et Q, de manière à ce que P et Q constituent une
   factorisation approximative de R.

   Alpha est la vitesse d’approche. Utiliser factorisation_alpha.

   Beta est un paramètre de convergeance. Utiliser factorisation_beta.
*/
void factor(factorisation_mat *fm, double alpha, double beta);

double factorisation_beta;
double factorisation_alpha;
