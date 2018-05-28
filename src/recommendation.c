#include "recommendation.h"
#include "factorisation.h"
#include "movies_list_loader.h"
#include <gsl/gsl_matrix.h>
#include "tools.h"

void recommendations_factorisation(movies* movies_list){
    //efface recommandation précédentes
    destroy_recommendations_list(movies_list->recommendations);
    movies_list->recommendations=NULL;
    //remplissage de la matrice de note
    gsl_matrix* R=load_matrix(movies_list);
    //préparation de la structure pour la factorisation
    rdm_init();
    factorisation_mat* fm=initialize_mat(3, R);
    // factorisation
    factor(fm, factorisation_alpha, factorisation_beta);
    //produit P*Q
    gsl_matrix* R_approx = gsl_matrix_alloc(R->size1, R->size2);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, fm->P, fm->Q, 0, R_approx);
    //extraction des recommandations
    int i=0;
    for(i=0;i<movies_list->max_length;i++){
        if(movies_list->tab[i]->grade==0){
            double g=gsl_matrix_get(R_approx,0,i);
            //ajout du film a la bonne position en fonction de sa note potentiel
            movies_list->recommendations=add_recommendations(movies_list->recommendations,i,g);
        }
    }
    print_matrix(fm->R);
    //libération de la mémoire
    //gsl_matrix_free(R);
    gsl_matrix_free(fm->R);
    gsl_matrix_free(fm->P);
    gsl_matrix_free(fm->Q);
    gsl_matrix_free(R_approx);
    free(fm);
    rdm_free();

}

void print_reco(movies* m, recommendations_list l){
    printf("\n");
    printf("==================================\n");
    printf("\n");
    int i = 0;
    int id=get_id(l,i);
    while (id!=-1) {
        printf("%d %s -- %f\n", i, m->tab[id]->title, get_grade_reco(l,i));
        i++;
        id=get_id(l, i);
    }
    printf("\n");

}
