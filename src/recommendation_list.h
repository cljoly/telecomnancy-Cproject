#ifndef PROJECT_RECOMMENDATION_LIST_H
#define PROJECT_RECOMMENDATION_LIST_H

#define NB_RECO 10
#include "factorisation.h"

/*
 * structure représentant un élément d'une liste chainé de recommandations
 */
struct recommendations_cell{
    int id;//id du film recommandé
    double grade;//note potentiel de l'utilisateur
    struct recommendations_cell* next;//pointeur vers l'élément suivant
};

// lsite de recommandations
typedef struct recommendations_cell* recommendations_list;

/*
 * fontion permettant de créer une liste vide
 */
recommendations_list create_list_recommendations();

/*
 * fonction permettant d'ajouter un nouvel élément dans la liste selon sa note
 */
recommendations_list add_recommendations(recommendations_list l, int id, double grade);

/*
 * fonction permettant de récupérer l'id d'un film de la liste en lui donnant son indice
 */
int get_id(recommendations_list l, int i);

/*
 * fonction permettant de récupérer la note d'un film de la liste en lui donnant son indice
 */
double get_grade_reco(recommendations_list l, int i);

/*
 * fonction permettant de test si la liste est vide
 */
int isempty_recommendations_list(recommendations_list l);

/*
 * fonction pemrettant de libérer en mémoire l'espace d'une liste
 */
void destroy_recommendations_list(recommendations_list l);



#endif //PROJECT_RECOMMENDATION_LIST_H
