#include "movies_list_loader.h"
#include <wjelement.h>
#include <stdlib.h>
#include <stdio.h>

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
    printf("id 0 : %d\n",m->tab[0]->id);
    printf("titre 0 : %s\n",m->tab[0]->title);
    printf("realisateur 0 : %s\n",m->tab[0]->director);
    printf("type 0 : %d\n",m->tab[0]->type);

    printf("id 1 : %d\n",m->tab[1]->id);
    printf("titre 1 : %s\n",m->tab[1]->title);
    printf("année 1 : %d\n",m->tab[1]->year);
    printf("realisateur 1 : %s\n",m->tab[1]->director);
    printf("durée 1 : %d\n",m->tab[1]->duration);
    printf("synopsis 1 : %s\n",m->tab[1]->synopsis);
    printf("type 1 : %d\n",m->tab[1]->type);
    printf("genre 1.0 : %s\n",get_string(m->tab[1]->genre,0));
    printf("genre 1.1 : %s\n",get_string(m->tab[1]->genre,1));
    printf("genre 1.2 : %s\n",get_string(m->tab[1]->genre,2));

    printf("acteur 1.0 : %s\n",get_string(m->tab[1]->actors,0));
    printf("acteur 1.1 : %s\n",get_string(m->tab[1]->actors,1));
    printf("acteur 1.2 : %s\n",get_string(m->tab[1]->actors,2));

    printf("test film null : %p\n",get_movies(m,2));



    // libéré l'espace mémoire de la liste de film
    destroy_movies_list(m);
    //fermeture de l'élément de la librairie jwelement + libération en mémoire
    WJECloseDocument(elem);
    WJRCloseDocument(doc);
    //fermeture du fichier
    fclose(f);

}