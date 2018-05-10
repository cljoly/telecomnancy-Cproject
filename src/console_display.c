#include "console_display.h"
#include <stdlib.h>
#include <stdio.h>

void print_movie_details(movie* m){
    printf("Titre : %s\n",m->title);
    printf("Année : %d\n",m->year);
    printf("Realisateur : %s\n",m->director);
    printf("Durée : %d\n",m->duration);

    switch(m->type){
        case SERIE :
            printf("Type : Série\n");
            break;
        case MOVIE :
            printf("Type : Film\n");
            break;
    }


    printf("Genres : ");
    int i=0;
    while(get_string(m->genre,i)!=NULL && i<10){
        printf("%s ",get_string(m->genre,i));
        i++;
    }
    printf("\n");

    printf("Acteurs : ");
    i=0;
    while(get_string(m->genre,i)!=NULL && i<10){
        printf("%s, ",get_string(m->actors,i));
        i++;
    }
    printf("etc");
    printf("\n");

    printf("Synopsis : %s\n",m->synopsis);
}

void print_movies_list(movies* m){
    int i=0;
    while(i<m->max_length){
        printf("%d %s\n", i, m->tab[i]->title);
        i++;
    }
}