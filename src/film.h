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

typedef enum typefilm{
  SERIE,
  FILM
}typefilm;

typedef char* ELEMENT;

struct cellule {
   ELEMENT val;
   struct cellule * suiv;} ;

typedef struct cellule * Liste;
