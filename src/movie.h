#ifndef SRC_MOVIE_H
#define SRC_MOVIE_H

#define USERNAME_LENGTH 100
#include "stringlist.h"
#include "recommendation_list.h"

/*
 * enumération permettant de définir un type de film
 * (série ou film)
 */
typedef enum type_movie{
    SERIE,
    MOVIE
}type_movie;

/*
 * structure permettant de définir un film
 */
typedef struct movie{
    int id; //id du film
    char* title; //titre du film
    int year; //année du film
    char* director; //réalisateur du film
    string_list actors; //liste d'acteurs du film
    string_list genre; //liste de genres du film
    int duration; //durée du film
    type_movie type; //type de film (serie ou film)
    char* synopsis; //synopsis du film
    int grade; //note
}movie;

/*
 * structure définissant une liste de films
 */
typedef struct movies{
    int max_length; //longueur de la liste
    char* user; //nom d'utilisateur
    movie** tab; //tableau contenant la liste de film
    recommendations_list recommendations; // liste d'indice des films recommandés
}movies;


/*
 * fonction permettant de créer et de réserver en mémoire un film
 */
movie* create_movie();

/*
 * fonction permettant de libérer l'espace en mémoire d'un film
 */
void destroy_movie(movie* m);
/*
 * fonction permettant de créer et de réserver l'espace en mémoire pour une liste de film
 * N : taille max de la liste de film
 */
movies* create_movies_list(int N);

/*
 * fonction permettant de libérer l'espace en mémore d'une liste de film
 */
void destroy_movies_list(movies* m);

/*
 * fonction permettant de récuperer le pointeur d'un film présent dans une liste de film en lui donnant son indice
 */
movie* get_movies(movies* m, int i);

/*
 * fonction permttant d'ajouter un film à une liste de films
 */
void add_movie(movies* movies_list, movie* m, int i);




#endif //SRC_MOVIE_H