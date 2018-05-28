#include "console_controler.h"
#include "console_display.h"
#include <stdio.h>
#include <stdlib.h>
#include "movies_list_loader.h"
#include "recommendation_list.h"
#include "recommendation.h"

void select_user(movies *movies_list) {
  char user[USERNAME_LENGTH];
  char c;
  // affichage du menu d'authentification
  print_select_user();
  // saisie du login de l'utilisateur
  int res = scanf("%s", user);
  while ((c = getchar()) != EOF && c != '\n')
    ;
  while (!res) {
    printf("Erreur login incorrect saisissez de nouveau votre login : \n");
    res = scanf("%s", user);
    while ((c = getchar()) != EOF && c != '\n')
      ;
  }
  movies_list->user = user;
  // chargement des données si utilisateur déjà existant
  load_grade(movies_list);
  // passe au menu utilisateur
  menu(movies_list);
}

void menu(movies *movies_list) {
  int cmd = 0;
  // booléen permattant de vérifier si la commande est correcte
  int b = 1;
  char c;
  // affichage du menu
  print_menu(movies_list->user);

  // saisie de la commande
  while (b) {
    b = 0;
    int res = scanf("%d", &cmd);
    while ((c = getchar()) != EOF && c != '\n')
      ;
    while (!res) {
      printf("Erreur commande inconnue, saisissez de nouveau le numéro "
             "associée la commande souhaitée : \n");
      res = scanf("%d", &cmd);
      while ((c = getchar()) != EOF && c != '\n')
        ;
    }
    // traitement en fonction de la commande
    switch (cmd) {
    case 1:
      // affichage de la liste de film pour les noter
      movies_choice(movies_list);
      break;
    case 2:
      //affichage de la liste de recommandation
      recommendations_factorisation(movies_list);
      save_grade(movies_list);
      recommendation_menu(movies_list);
      break;
    case 3:
      // sauvegarde des modifs
      save_grade(movies_list);
      menu(movies_list);
      break;
    case 4:
      // quitte l'application
      return;
    default:
      // commande incorrect
      b = 1;
      // while ((c = getchar()) != EOF && c != '\n');
      cmd = 0;
      printf("Erreur commande inconnue, saisissez de nouveau le numéro "
             "associée la commande souhaitée : \n");
    }
  }
}

void movies_choice(movies *movies_list) {
  int idm;
  // affichage de la liste de films
  print_movies_list(movies_list);
  printf("Veuillez saisir le numéro du film que vous souhaitez noter : \n");
  // saisie de la commande
  int res = scanf("%d", &idm);
  char c;
  while ((c = getchar()) != EOF && c != '\n')
    ;
  while (!res || idm >= movies_list->max_length || idm < 0) {
    printf("Erreur numéro incorrect, saisissez de nouveau le numéro associée "
           "la commande souhaitée : \n");
    res = scanf("%d", &idm);
    while ((c = getchar()) != EOF && c != '\n')
      ;
  }
  // traitement en fonction de la commande
  movie_grade(movies_list, movies_list->tab[(int)idm]);
}

void movie_grade(movies *movies_list, movie *m) {
  print_movie_details(m);
  printf("Veuillez saisir votre note de 1 à 5 (0 pour annuler): \n");
  int grade = 0;
  int res = scanf("%d", &grade);
  char c;
  while ((c = getchar()) != EOF && c != '\n')
    ;
  while (!res || grade > 5 || grade < 0) {
    printf("Erreur note incorrecte\n");
    res = scanf("%d", &grade);
    while ((c = getchar()) != EOF && c != '\n')
      ;
  }
  // traitement en fonction de la commande
  movies_list->tab[m->id]->grade = (int)grade;
  // retour au menu
  menu(movies_list);
}

void recommendation_menu(movies* movies_list){
  print_recommendations(movies_list);
  //print_reco(movies_list, movies_list->recommendations);
  // saisie de la commande
  int l=0;
  recommendations_list r=movies_list->recommendations;
  while (r!=NULL){
    l++;
    r=r->next;
  }
  int idm;
  int res = scanf("%d", &idm);
  char c;
  while ((c = getchar()) != EOF && c != '\n')
    ;
  while (!res || (idm >= NB_RECO || idm >= l) || idm < -1) {
    printf("Erreur numéro incorrect, saisissez de nouveau le numéro associée la commande souhaitée : \n");
    res = scanf("%d", &idm);
    while ((c = getchar()) != EOF && c != '\n')
      ;
  }
  // traitement en fonction de la commande
  if(idm==-1){
    menu(movies_list);
  }else{
    recommendation_details(movies_list,get_id(movies_list->recommendations,idm));
  }
}

void recommendation_details(movies* movies_list, int id){
  print_movie_details(movies_list->tab[id]);
  printf("0 retour au menu\n");
  printf("1 retour à la liste de recommandations\n");
  int idm;
  int res = scanf("%d", &idm);
  char c;
  while ((c = getchar()) != EOF && c != '\n');
  while (!res || (idm!=0 && idm!=1)) {
    printf("Erreur numéro incorrect, saisissez de nouveau le numéro associée la commande souhaitée : \n");
    res = scanf("%d", &idm);
    while ((c = getchar()) != EOF && c != '\n')
      ;
  }
  //traitement de la commande
  if(idm==0){
    menu(movies_list);
  }else{
    recommendation_menu(movies_list);
  }
}