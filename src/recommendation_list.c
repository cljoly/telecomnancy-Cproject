#include "recommendation_list.h"

recommendations_list create_list_recommendations(){
    return NULL;
}

recommendations_list add_recommendations(recommendations_list l, int id, double grade){
    recommendations_list p=l;
    //création et ajout du premier élément de la liste
    if(l==NULL){
        recommendations_list l1=(recommendations_list)malloc(sizeof(struct recommendations_cell));
        l1->next=NULL;
        l1->id=id;
        l1->grade=grade;
        return l1;
    }
    // ajout en tête de liste
    if(l->grade<grade){
        recommendations_list l1=(recommendations_list)malloc(sizeof(struct recommendations_cell));
        l1->next=l;
        l1->id=id;
        l1->grade=grade;
        return l1;
    }
    while(p->next!=NULL){
        if((p->next)->grade<=grade){
            //ajout en milieu de liste
            recommendations_list l1=(recommendations_list)malloc(sizeof(struct recommendations_cell));
            l1->next=p->next;
            l1->id=id;
            l1->grade=grade;
            p->next=l1;
            return l;
        }
        p=p->next;
    }
    //ajout en fin de liste
    recommendations_list l1=(recommendations_list)malloc(sizeof(struct recommendations_cell));
    l1->next=NULL;
    l1->id=id;
    l1->grade=grade;
    p->next=l1;
    return l;
}

int get_id(recommendations_list l, int i){
    if (l == NULL)
        return -1;
    recommendations_list p = l;
    // se met à la iéme position
    while (i > 0 && p->next != NULL) {
        i--;
        p = p->next;
    }
    // test si i > taille de la liste
    if (i > 0) {
        return -1;
    } else {
        return p->id;
    }
}

double get_grade_reco(recommendations_list l, int i){
    if (l == NULL)
        return -1;
    recommendations_list p = l;
    // se met à la iéme position
    while (i > 0 && p->next != NULL) {
        i--;
        p = p->next;
    }
    // test si i > taille de la liste
    if (i > 0) {
        return -1;
    } else {
        return p->grade;
    }
}


int isempty_recommendations_list(recommendations_list l){
    return (l==NULL);
}

void destroy_recommendations_list(recommendations_list l){
    recommendations_list tmp = l;
    while (tmp != NULL) {
        recommendations_list tmp1 = tmp->next;
        free(tmp);
        tmp = tmp1;
    }
}

