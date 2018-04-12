#ifndef SRC_STRINGLIST_H
#define SRC_STRINGLIST_H

#endif //SRC_CHARLIST_H

/*
 * structure représentant un élément d'une liste chainée
 */
struct cell {
    char* val; //valeur de l'élément
    struct cell* next; //pointeur vers l'élément suivant
};

/*
 * définition du type liste
 */
typedef struct cell* string_list;

/*
 * fontion permettant de créer une liste vide
 */
string_list create_list_string();

/*
 * fonction permettant d'ajouter un nouvel élément en tête de liste
 */
string_list add_first_string(string_list l, char* v);

/*
 * fonction permettant de récupérer la valuer d'un élément de la liste en lui donnant son indice
 */
char* get_string(string_list l, int i);

/*
 * fonction permettant de test si la liste est vide
 */
int isempty_string_list(string_list l);

/*
 * fonction pemrettant de libérer en mémoire l'espace d'une liste
 */
void destroy_string_list(string_list l);

