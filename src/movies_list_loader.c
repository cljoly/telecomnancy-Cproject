#include "movies_list_loader.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


movies *load_movies(WJElement elem, int movie_number) {
    // création de la liste de film
    movies *movies_list = create_movies_list(movie_number);
    int i = 0;
    movie *m;
    char nb[10] = "";
    char path_b[8] = "movies[";
    char path[100];
    char path1[100];
    char *type;
    while (i < movie_number) {
        m = create_movie();
        // préparation du path pour trouver le film
        sprintf(nb, "%d", i);
        strcpy(path, path_b);
        strcat(path, nb);
        strcpy(path1, path);
        // récupération des informations concernant le film
        // id
        m->id = WJEInt32(elem, strcat(path1, "].id"), WJE_GET, 0);
        strcpy(path1, path);
        // titre
        m->title = WJEString(elem, strcat(path1, "].title"), WJE_GET, "");
        strcpy(path1, path);
        // année
        m->year = WJEInt32(elem, strcat(path1, "].year"), WJE_GET, 0);
        strcpy(path1, path);
        // durée
        m->duration = WJEInt32(elem, strcat(path1, "].duration"), WJE_GET, 0);
        strcpy(path1, path);
        // réalisateur
        m->director = WJEString(elem, strcat(path1, "].director"), WJE_GET, "");
        strcpy(path1, path);
        // synopsis
        m->synopsis = WJEString(elem, strcat(path1, "].synopsis"), WJE_GET, "");
        strcpy(path1, path);
        // type
        type = WJEString(elem, strcat(path1, "].type"), WJE_GET, "");
        if (strcmp(type, "Movie") == 0)
            m->type = MOVIE;
        else if (strcmp(type, "Serie") == 0)
            m->type = SERIE;
        strcpy(path1, path);
        // genres
        m->genre = create_list_string();
        int c = 0, stop = 0;
        char *val;
        char path2[100];
        char path3[100];
        strcpy(path2, path1);
        strcat(path2, "].genres[");
        char nbc[10];
        while (!stop) {
            sprintf(nbc, "%d]", c);
            strcpy(path3, path2);
            strcat(path3, nbc);
            val = WJEString(elem, path3, WJE_GET, "");
            if (strcmp(val, "") == 0) {
                stop = 1;
            } else {
                m->genre = add_first_string(m->genre, val);
            };
            c++;
        }
        strcpy(path1, path);
        // acteurs
        m->actors = create_list_string();
        c = 0;
        stop = 0;
        strcpy(path2, path1);
        strcat(path2, "].actors[");
        while (!stop) {
            sprintf(nbc, "%d]", c);
            strcpy(path3, path2);
            strcat(path3, nbc);
            val = WJEString(elem, path3, WJE_GET, "");
            if (strcmp(val, "") == 0) {
                stop = 1;
            } else {
                m->actors = add_first_string(m->actors, val);
            };
            c++;
        }
        strcpy(path1, path);

        // ajout du film à la liste
        add_movie(movies_list, m, m->id);
        i++;
    }
    return movies_list;
}


void save_grade(movies* movies_list) {
    WJElement doc = NULL;
    doc = WJEObject(NULL, NULL, WJE_NEW);
    WJEArray(doc, "movies", WJE_SET);
    int i = 0;
    char path_b[8] = "movies[";
    char path[100];
    char path1[100];
    char nb[10];
    for (i = 0; i < movies_list->max_length; i++) {
        strcpy(path, path_b);
        sprintf(nb, "%d]", i);
        strcat(path, nb);
        // création de l'objet film
        WJEObject(doc, path, WJE_NEW);
        strcpy(path1, path);
        // affectation de l'id
        strcat(path1, ".id");
        WJEInt64(doc, path1, WJE_SET, i);
        strcpy(path1, path);
        // affectation de l'id
        strcat(path1, ".title");
        WJEString(doc, path1, WJE_SET, movies_list->tab[i]->title);
        strcpy(path1, path);
        // affectation de l'id
        strcat(path1, ".grade");
        WJEInt64(doc, path1, WJE_SET, movies_list->tab[i]->grade);
        strcpy(path1, path);
    }
    //sauvegarde des recommandations
    if(movies_list->recommendations!=NULL) {
        WJEArray(doc, "recommendations", WJE_SET);
        strcpy(path_b, "recommendations[");
        movie *m;
        for (i = 0; i < NB_RECO; i++) {
            m = movies_list->tab[get_id(movies_list->recommendations, i)];
            strcpy(path, path_b);
            strcat(path, "$]");
            // création de l'objet film
            WJEObject(doc, path, WJE_NEW);
            strcpy(path1, path_b);
            // affectation de l'id
            strcat(path1, "-1].id");
            WJEInt64(doc, path1, WJE_SET, m->id);
            strcpy(path1, path_b);
            // affectation de l'id
            strcat(path1, "-1].title");
            WJEString(doc, path1, WJE_SET, m->title);
            strcpy(path1, path_b);
            // affectation de l'id
            strcat(path1, "-1].grade");
            WJEDouble(doc, path1, WJE_SET, get_grade_reco(movies_list->recommendations, i));
            strcpy(path1, path_b);
        }
    }

    //sauvegarde dans le fichier json
    char file_name[USERNAME_LENGTH + 11];
    strcpy(file_name, "users/");
    strcat(file_name, movies_list->user);
    strcat(file_name, ".json");
    FILE *f = fopen(file_name, "w+");
    if (f != NULL){
        WJEWriteFILE(doc, f);
        printf("==================================\n");
        printf("Sauvegarde Réussie\n");
    }
    else {
        printf("==================================\n");
        printf("Sauvegarde Impossible\n");
        //printf("%s\n",file_name);
        printf("==================================\n");
    }
    //WJEDump(doc);
    // ferme et libère la mémoire du document
    fclose(f);
    WJECloseDocument(doc);

}

void load_grade(movies* movies_list){
    char file_name[USERNAME_LENGTH + 11];
    strcpy(file_name, "users/");
    strcat(file_name, movies_list->user);
    strcat(file_name, ".json");
    FILE *f = fopen(file_name, "r");
    if (f != NULL){
        // préparation du reader afin de lire dans le fichier json
        WJReader doc = WJROpenFILEDocument(f, NULL, 0);
        WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
        int i = 0;
        char nb[10] = "";
        char path_b[8] = "movies[";
        char path[100];
        while (i < movies_list->max_length) {
            // préparation du path pour trouver le film
            sprintf(nb, "%d", i);
            strcpy(path, path_b);
            strcat(path, nb);
            strcat(path, "].grade");
            // récupération de la note utilisateur.
            int grade=WJEInt32(elem, path, WJE_GET, 0);
            if(grade==1||grade==2||grade==3||grade==4||grade==5)
                movies_list->tab[i]->grade = grade;

            i++;
        }
        WJECloseDocument(elem);
        WJRCloseDocument(doc);
        fclose(f);
    }
}

int isDir(struct dirent* ent) {
    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
        return 1;
    if ((strchr(ent->d_name, '.')) == NULL) /* Si le nom du fichier n'a pas de point (une extension). */
        return 1;
    else
        return 0;
}


gsl_matrix* load_matrix(movies* movies_list){
    //ouvertur du repertoire des profils utilisateurs
    DIR* dir = NULL;
    struct dirent* fr = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    dir = opendir("users/");
    int c=0;
    if (dir == NULL)
        exit(1);
    // nom du fichier de l'utilisateur
    char file_name[USERNAME_LENGTH + 5];
    strcpy(file_name, movies_list->user);
    strcat(file_name, ".json");
    //parcours du repertoire des utilisateurs pour connaitre le nombre d'utilisateurs
    while ((fr = readdir(dir)) != NULL) {
        if(!isDir(fr)&&strcmp(fr->d_name, file_name)) {
            c++;
        }
    }
    c++;
    //printf("%d\n",c);
    gsl_matrix* m= gsl_matrix_alloc(c, movies_list->max_length);

    //retour au début du répertoire
    rewinddir(dir);
    // chargement de la premier ligne de la matrice avec les notes de l'utilisateur courant
    int k=0;
    int g=0;
    for(k=0; k<movies_list->max_length; k++){
        g=movies_list->tab[k]->grade;
        if (!(g == 1 || g == 2 || g == 3 || g == 4 || g == 5))
            g=0;
        //affectation de la note dans la matrice
        gsl_matrix_set(m, 0, k, g);
    }
    // c commance à 1 car la ligne 0 correspond à l'utilisateur qui utilise l'application
    c=1;
    //parcours des fichiers utilisateurs
    while ((fr = readdir(dir)) != NULL) {
        if(!isDir(fr)&&strcmp(fr->d_name, file_name)){
            char file_name[USERNAME_LENGTH + 11];
            strcpy(file_name, "users/");
            strcat(file_name, fr->d_name);
            FILE *f = fopen(file_name, "r");
            if (f != NULL) {
                // préparation du reader afin de lire dans le fichier json
                WJReader doc = WJROpenFILEDocument(f, NULL, 0);
                WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
                int i = 0;
                char nb[10] = "";
                char path_b[8] = "movies[";
                char path[100];
                while (i < movies_list->max_length) {
                    // préparation du path pour trouver le film
                    sprintf(nb, "%d", i);
                    strcpy(path, path_b);
                    strcat(path, nb);
                    strcat(path, "].grade");
                    // récupération de la note utilisateur.
                    int grade = WJEInt32(elem, path, WJE_GET, 0);
                    if (!(grade == 1 || grade == 2 || grade == 3 || grade == 4 || grade == 5))
                        grade=0;
                    //affectation de la note dans la matrice
                    gsl_matrix_set(m, c, i, grade);
                    i++;
                }
                WJECloseDocument(elem);
                WJRCloseDocument(doc);
                fclose(f);
            }
            c++;
        }
    }

    if (closedir(dir) == -1)
        exit(-1);
    return m;
}

