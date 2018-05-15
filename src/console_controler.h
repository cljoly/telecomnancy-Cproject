#ifndef PROJECT_CONSOLE_CONTROLER_H
#define PROJECT_CONSOLE_CONTROLER_H

#include "movie.h"
/*
 * gestion de l'authentification
 */
void select_user(movies* movies_list);

/*
 * gestion du menu
 */
void menu(movies* movies_list);

/*
 * gestion du choix des films à noter
 */
void movies_choice(movies* movies_list);

/*
 * gestion de la notation d'un film
 */
void movie_grade(movies* movies_list, movie* m);

#endif //PROJECT_CONSOLE_CONTROLER_H
