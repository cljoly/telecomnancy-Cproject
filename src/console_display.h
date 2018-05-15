#ifndef PROJECT_CONSOLE_DISPLAY_H
#define PROJECT_CONSOLE_DISPLAY_H


#include "movie.h"


/*
 * affichage des détails d'un film
 */
void print_movie_details(movie* m);

/*
 * affichage de la liste de fichiers
 */
void print_movies_list(movies* m);

/*
 * affichage de l'authentification
 */
void print_select_user();

/*
 * affichage du menu principale
 */
void print_menu(char* username);



#endif //PROJECT_CONSOLE_DISPLAY_H