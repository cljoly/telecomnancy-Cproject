#ifndef SRC_MOVIES_LIST_LOADER_H
#define SRC_MOVIES_LIST_LOADER_H



#include "movie.h"
#include <wjelement.h>

/*
 * fonction permattant de charger une liste de film à partir d'un fichier json
 * retourne un pointeur vers une liste de films
 * elem : WJElement représentant le contenu du fichier json
 * movie_number : nombre max de films dans la liste
 */
movies* load_movies(WJElement elem, int movie_number);

#endif //SRC_MOVIES_LIST_LOADER_H