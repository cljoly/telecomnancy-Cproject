#include "movies_list_loader.h"
#include <wjelement.h>
#include <stdlib.h>
#include <stdio.h>
#include "console_display.h"

#define MOVIE_NB 2

int main(){


    // ouverture du fichier json
    FILE* f=fopen("films.json","r");
    //test si l'ouverture est un succès
    if(f==NULL) {
        printf("impossible d'ouvrir le fichier");
        return 1;
    }
    //préparation du reader afin de lire dans le fichier json
    WJReader doc = WJROpenFILEDocument(f, NULL, 0);
    WJElement elem= WJEOpenDocument(doc, NULL, NULL, NULL);
    //charge la liste de film
    movies* m=load_movies(elem, MOVIE_NB);



    //tests
    print_movie_details(m->tab[0]);
    printf("------------------------\n");
    print_movie_details(m->tab[1]);
    printf("------------------------\n");
    print_movies_list(m);




    // libéré l'espace mémoire de la liste de film
    destroy_movies_list(m);
    //fermeture de l'élément de la librairie jwelement + libération en mémoire
    WJECloseDocument(elem);
    WJRCloseDocument(doc);
    //fermeture du fichier
    fclose(f);

}
