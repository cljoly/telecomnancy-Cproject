#include "movie.h"
#include <stdlib.h>


movie* create_movie(){
    movie* m= malloc(sizeof(movie));
    m->grade=0;
    return m;
}

void destroy_movie(movie* m){
    if(m!=NULL) {
        destroy_string_list(m->genre);
        destroy_string_list(m->actors);
        free(m);
    }
}

movies* create_movies_list(int N){
    movies* m=malloc(sizeof(movies));
    m->tab=malloc(sizeof(movie*)*N);
    m->max_length=N;
    return m;
}

void destroy_movies_list(movies* m){
    if(m!=NULL) {
        int i;
        for (i = 0; i < m->max_length; i++) {
            destroy_movie(m->tab[i]);
        }
        free(m->tab);
        free(m);
    }
}

movie* get_movies(movies* m, int i){
    if(m==NULL)
        return NULL;
    if(i>=m->max_length)
        return NULL;
    return m->tab[i];
}

void add_movie(movies* movies_list, movie* m, int i){
    if(i<movies_list->max_length)
        movies_list->tab[i]=m;
}
