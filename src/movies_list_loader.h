#ifndef SRC_MOVIES_LIST_LOADER_H
#define SRC_MOVIES_LIST_LOADER_H


#include <gsl/gsl_matrix.h>
#include "movie.h"
#include <wjelement.h>
#include <dirent.h>


/*
 * fonction permattant de charger une liste de film à partir d'un fichier json
 * retourne un pointeur vers une liste de films
 * elem : WJElement représentant le contenu du fichier json
 * movie_number : nombre max de films dans la liste
 */
movies* load_movies(WJElement elem, int movie_number);

/*
 * fonction permettant de saugarder les notes de l'utilisateur
 */
void save_grade(movies* movies_list);

/*
 * fonction permettant de charger les notes d'un utilisateur
 */
void load_grade(movies* movies_list);

/*
 * fonction permettant de remplire la matrice utilisée lors de la factorisation
 */
gsl_matrix* load_matrix(movies* movies_list);

/*
 * fonction permettant dire si ent est un répertoire
 */
int isDir(struct dirent* ent);




#endif //SRC_MOVIES_LIST_LOADER_H