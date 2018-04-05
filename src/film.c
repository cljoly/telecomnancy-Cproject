#include "film.h"
#include <stdlib.h>

film* creerFilm(){
    return malloc(sizeof(film));
}

void freeFilm(film* f){
    if(f!=NULL)
        free(f);
}

films creerListeFilm(int taille){
    films f;
    f.tab=malloc(sizeof(film*)*taille);
    f.tailleMax=taille;
    f.nbFilms=0;
    return f;
}

void freeListeFilm(films f){
    int i;
    for(i=0;i<f.nbFilms;i++){
        freeFilm(f.tab[i]);
    }
    free(f.tab);
}

film* getFilm(films f, int i){
    return f.tab[i];
}

void ajouterFilm(films listeFilm, film* f){
    if(f!=NULL&&listeFilm.nbFilms<listeFilm.tailleMax){
        listeFilm.tab[listeFilm.nbFilms]=f;
        listeFilm.nbFilms++;
    }
}

int main(){

}