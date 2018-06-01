#ifndef PROJECT_INTERFACE_H
#define PROJECT_INTERFACE_H

#include <gtk/gtk.h>
#include"movie.h"
#include <wjelement.h>

typedef struct
{
	GtkBuilder *builder;
	gpointer user_data;
	gchar *identifiant;
	movies *m;
	char nom;
} SGlobalData;

typedef struct
{
	GtkBuilder *builder;
     char *nom;
     char *prenom;
	gchar *identifiant;
     char *mail;
    gboolean sexe;
     char *mdp;
     int robot;
    gpointer local_data;
} SLocalData;

typedef struct
{
	GtkBuilder *builder;
    gpointer *fichier_data;
    FILE *f;
    WJReader doc;
    WJElement elem;
} Fichier;

void page_suivante(gpointer user_data, int page);
void vers_page_creation(GtkWidget* widget, gpointer user_data);
void vers_page_principale(GtkWidget* widget, gpointer user_data);
void vers_page_accueil(GtkWidget* widget, gpointer user_data);
void vers_page_biblio(GtkWidget* widget, gpointer user_data);
void vers_page_film(GtkWidget* widget, gpointer user_data);
void vers_page_info(GtkWidget* widget, gpointer user_data);
void vote_nul(gpointer user_data, char *nom);
void vote_bien(gpointer user_data, char *nom);
void note0(GtkWidget *widget, gpointer user_data);
void note1(GtkWidget *widget, gpointer user_data);
void note2(GtkWidget *widget, gpointer user_data);
void note3(GtkWidget *widget, gpointer user_data);
void note4(GtkWidget *widget, gpointer user_data);
void note5(GtkWidget *widget, gpointer user_data);
void changer_note(GtkWidget *widget, gpointer user_data, int note);
void chargement_principale(GtkWidget* widget, gpointer user_data);
void chargement_biblio(GtkWidget* widget, gpointer user_data);
void chargement_fiche(GtkWidget* widget, gpointer user_data);
void chargement_fiche2(GtkWidget* widget, gpointer user_data);
//void changer_image_bib(gpointer user_data);
void test2(GtkWidget* widget, gpointer user_data);
//void test(GtkWidget* widget, gpointer user_data);
void nouveau_compte (GtkWidget* widget , gpointer user_data, gpointer local_data);
void connexion(GtkWidget* widget, gpointer user_data, gpointer local_data, gpointer fichier);
void quitter(GtkWidget *widget, gpointer user_data);


#endif //PROJECT_INTERFACE_H
