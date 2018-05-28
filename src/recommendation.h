#ifndef PROJECT_RECOMMENDATION_H
#define PROJECT_RECOMMENDATION_H

#include "movie.h"
#include "recommendation.h"

/*
 * fonction permettant de trouver les recommandations d'un utilisateur avec la méthode de factorisation
 */
void recommendations_factorisation(movies* movies_list);


/*
 * fonction permettant d'afficher la liste de recommandation (test)
 */
void print_reco(movies* m, recommendations_list l);


#endif //PROJECT_RECOMMENDATION_H
