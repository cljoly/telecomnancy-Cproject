#include "movies_list_loader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


movies* load_movies(WJElement elem, int movie_number){
    // création de la liste de film
    movies* movies_list=create_movies_list(movie_number);
    int i=0;
    movie* m;
    char nb[10]="";
    char path_b[8]="movies[";
    char path[100];
    char path1[100];
    char* type;
    while(i<movie_number) {
        m = create_movie();
        //préparation du path pour trouver le film
        sprintf(nb, "%d", i);
        strcpy(path, path_b);
        strcat(path, nb);
        strcpy(path1, path);
        //récupération des informations concernant le film
        //id
        m->id = WJEInt32(elem, strcat(path1, "].id"), WJE_GET, 0);
        strcpy(path1, path);
        //titre
        m->title = WJEString(elem, strcat(path1, "].title"), WJE_GET, "");
        strcpy(path1, path);
        //année
        m->year = WJEInt32(elem, strcat(path1, "].year"), WJE_GET, 0);
        strcpy(path1, path);
        //durée
        m->duration = WJEInt32(elem, strcat(path1, "].duration"), WJE_GET, 0);
        strcpy(path1, path);
        //réalisateur
        m->director = WJEString(elem, strcat(path1, "].director"), WJE_GET, "");
        strcpy(path1, path);
        //synopsis
        m->synopsis = WJEString(elem, strcat(path1, "].synopsis"), WJE_GET, "");
        strcpy(path1, path);
        //type
        type = WJEString(elem, strcat(path1, "].type"), WJE_GET, "");
        if (strcmp(type, "Movie") == 0)
            m->type = MOVIE;
        else if (strcmp(type, "Serie") == 0)
            m->type = SERIE;
        strcpy(path1, path);
        //genres
        m->genre=create_list_string();
        int c=0,stop=0;
        char* val;
        char path2[100];
        char path3[100];
        strcpy(path2,path1);
        strcat(path2,"].genres[");
        char nbc[10];
        while(!stop){
            sprintf(nbc,"%d]",c);
            strcpy(path3,path2);
            strcat(path3,nbc);
            val=WJEString(elem, path3, WJE_GET, "");
            if(strcmp(val,"")==0){
                stop=1;
            }else{
                m->genre=add_first_string(m->genre,val);
            };
            c++;
        }
        strcpy(path1,path);
        //acteurs
        m->actors=create_list_string();
        c=0;
        stop=0;
        strcpy(path2,path1);
        strcat(path2,"].actors[");
        while(!stop){
            sprintf(nbc,"%d]",c);
            strcpy(path3,path2);
            strcat(path3,nbc);
            val=WJEString(elem, path3, WJE_GET, "");
            if(strcmp(val,"")==0){
                stop=1;
            }else{
                m->actors=add_first_string(m->actors,val);
            };
            c++;
        }
        strcpy(path1,path);

        //ajout du film à la liste
        add_movie(movies_list, m, m->id);
        i++;
    }
    return movies_list;
}
