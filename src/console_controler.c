#include "console_controler.h"
#include "console_display.h"
#include <stdlib.h>
#include <stdio.h>



void select_user(movies* movies_list){
    char user[USERNAME_LENGTH];
    char c;
    // affichage du menu d'authentification
    print_select_user();
    // saisie du login de l'utilisateur
    int res=scanf("%s", user);
    while((c = getchar())!=EOF && c!='\n');
    while(!res){
        printf("Erreur login incorrect saisissez de nouveau votre login : ");
        res=scanf("%s", user);
        while((c = getchar())!=EOF && c!='\n');
    }
    movies_list->user=user;
    //ouverture du fichier si utilisateur déjà existant

    //chargement des données


    //passe au menu utilisateur
    menu(movies_list);
}

void menu(movies* movies_list) {
    int cmd = 0;
    //booléen permattant de vérifier si la commande est correcte
    int b = 1;
    char c;
    // affichage du menu
    print_menu(movies_list->user);

    // saisie de la commande
    while(b) {
        b = 0;
        int res = scanf("%d", &cmd);
        while ((c = getchar()) != EOF && c != '\n');
        while (!res) {
            printf("Erreur commande inconnue, saisissez de nouveau le numéro associée la commande souhaitée : ");
            res = scanf("%d", &cmd);
            while ((c = getchar()) != EOF && c != '\n');
        }
        // traitement en fonction de la commande
        switch (cmd) {
            case 1:
                //affichage de la liste de film pour les noter
                movies_choice(movies_list);
                break;
            case 2:
                //affichage de la liste de recommandation
                menu(movies_list);
                break;
            case 3:
                //sauvegarde des modifs
                menu(movies_list);
                break;
            case 4:
                //quitte l'application
                return;
            default:
                //commande incorrect
                b = 1;
                //while ((c = getchar()) != EOF && c != '\n');
                cmd=0;
                printf("Erreur commande inconnue, saisissez de nouveau le numéro associée la commande souhaitée : ");
        }
    }



}

void movies_choice(movies* movies_list){
    int idm;
    // affichage de la liste de films
    print_movies_list(movies_list);
    // saisie de la commande
    int res = scanf("%d", &idm);
    char c;
    while ((c = getchar()) != EOF && c != '\n');
    while (!res || idm>=movies_list->max_length || idm<0) {
        printf("Erreur numéro incorrect, saisissez de nouveau le numéro associée la commande souhaitée : ");
        res = scanf("%d", &idm);
        while ((c = getchar()) != EOF && c != '\n');
    }
    // traitement en fonction de la commande
    movie_grade(movies_list, movies_list->tab[(int)idm]);
}

void movie_grade(movies* movies_list, movie* m){
    print_movie_details(m);
    int grade=0;
    int res = scanf("%d", &grade);
    char c;
    while ((c = getchar()) != EOF && c != '\n');
    while (!res || grade>5 || grade<0) {
        printf("Erreur note incorrecte\n");
        res = scanf("%d", &grade);
        while ((c = getchar()) != EOF && c != '\n');
    }
    // traitement en fonction de la commande
    movies_list->tab[m->id]->grade=(int)grade;
    //retour au menu
    menu(movies_list);

}