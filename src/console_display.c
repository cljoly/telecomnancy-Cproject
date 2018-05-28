#include "console_display.h"
#include <stdio.h>
#include <stdlib.h>
#include "recommendation_list.h"

void print_movie_details(movie *m) {
  printf("\n");
  printf("==================================\n");
  printf("\n");
  printf("Titre : %s\n", m->title);
  printf("Année : %d\n", m->year);
  printf("Realisateur : %s\n", m->director);
  printf("Durée : %d\n", m->duration);

  switch (m->type) {
  case SERIE:
    printf("Type : Série\n");
    break;
  case MOVIE:
    printf("Type : Film\n");
    break;
  }

  printf("Genres : ");
  int i = 0;
  while (get_string(m->genre, i) != NULL && i < 10) {
    printf("%s ", get_string(m->genre, i));
    i++;
  }
  printf("\n");

  printf("Acteurs : ");
  i = 0;
  while (get_string(m->genre, i) != NULL && i < 10) {
    printf("%s, ", get_string(m->actors, i));
    i++;
  }
  printf("etc");
  printf("\n");

  printf("Synopsis : %s\n", m->synopsis);
  printf("\n");
}

void print_movies_list(movies *m) {
  printf("\n");
  printf("==================================\n");
  printf("\n");
  int i = 0;
  while (i < m->max_length) {
    char gradec[7];
    if (m->tab[i]->grade == 0)
      sprintf(gradec, "aucune");
    else
      sprintf(gradec, "%d", m->tab[i]->grade);
    printf("%d %s --- note : %s\n", i, m->tab[i]->title, gradec);
    i++;
  }
  printf("\n");
}

void print_select_user() {
  printf("\n");
  printf("==================================\n");
  printf("\n");
  printf("Veuillez saisir votre login\n");
}

void print_menu(char *username) {
  printf("\n");
  printf("==================================\n");
  printf("\n");
  printf("Bienvenue %s !\nSaisissez le numéro pour exécuter la commande "
         "associée\n",
         username);
  printf("\n");
  printf("1 Noter un film\n");
  printf("2 Consulter mes recommandations (sauvegarde automatique)\n");
  printf("3 Sauvegarder les modifications\n");
  printf("4 Quitter\n");
}

void print_recommendations(movies* m){
  printf("\n");
  printf("==================================\n");
  printf("\n");
  int i = 0;
  int id=get_id(m->recommendations,i);
  while (i < NB_RECO && id!=-1) {
    printf("%d %s\n", i, m->tab[id]->title);
    i++;
    id=get_id(m->recommendations, i);
  }
  printf("\n");
  printf("Veuillez saisir le numéro du film dont vous voulez connaitre les détails(-1 retour au menu) : \n");

}