typedef char* ELEMENT;

struct cellule {
    ELEMENT val;
    struct cellule * suiv;} ;

typedef struct cellule * Liste;

typedef enum typefilm{
    SERIE,
    FILM
}typefilm;

typedef struct film{
    int id;
    char* titre;
    int annee;
    char* realisateur;
    Liste acteurs;
    Liste genre;
    int duree;
    typefilm type;
    char* synopsis;
    int note;
}film;

typedef struct films{
    int tailleMax;
    int nbFilms;
    film** tab;
}films;

film* creerFilm();

void freeFilm(film* f);

films creerListeFilm(int N);

void freeListeFilm(films f);

film* getFilm(films f, int i);

void ajouterFilm(films listeFilm, film* f);







