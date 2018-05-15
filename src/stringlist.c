#include "stringlist.h"
#include <stdlib.h>

string_list create_list_string() { return NULL; }

string_list add_first_string(string_list l, char *v) {
  // allocation en mémoire
  string_list p = (string_list)malloc(sizeof(struct cell));
  // test si le calloc est un echec
  if (p == NULL)
    return NULL;
  // remplissage de l'élément
  p->val = v;
  p->next = l;
  return p;
}

char *get_string(string_list l, int i) {
  if (l == NULL)
    return NULL;
  string_list p = l;
  // se met à la iéme position
  while (i > 0 && p->next != NULL) {
    i--;
    p = p->next;
  }
  // test si i > taille de la liste
  if (i > 0) {
    return NULL;
  } else {
    return p->val;
  }
}

int isempty_string_list(string_list l) { return !l; }

void destroy_string_list(string_list l) {
  string_list tmp = l;
  while (tmp != NULL) {
    string_list tmp1 = tmp->next;
    free(tmp);
    tmp = tmp1;
  }
}
