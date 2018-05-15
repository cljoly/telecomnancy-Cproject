#include "console_display.h"
#include <stdio.h>
#include <stdlib.h>

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
  printf("Veuillez saisir votre note de 1 à 5 (0 pour annuler): \n");
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
  printf("Veuillez saisir le numéro du film que vous souhaitez noter : \n");
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
  printf("2 Consulter mes recommandations\n");
  printf("3 Sauvegarder les modifications\n");
  printf("4 Quitter\n");
}