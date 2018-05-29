#include"console_display.h"
#include "movies_list_loader.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "biblio_interface.c"
#include <wjelement.h>


#define MOVIE_NB 2
/*--------------------------------------------------------------------------*/
/* FONCTION MAIN*/
int main(int argc, char *argv [])
{
    GtkWidget *fenetre_principale = NULL;
    SGlobalData data;
    SLocalData local;
    GError *error = NULL;
    gchar *filename = NULL;
	GtkImage *image;
    gchar *filename1;

    /* Initialisation de la bibliothèque Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    data.builder = gtk_builder_new();
    local.builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier interface.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("interface.glade", NULL);

    /* Chargement du fichier interface.glade. */
    gtk_builder_add_from_file (data.builder, filename, &error);
    gtk_builder_add_from_file (local.builder,filename, &error);


    g_free (filename);
    if (error)
    {
        gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }
    

     /* Affectation des signaux de l'interface aux différents CallBacks. */
    gtk_builder_connect_signals (data.builder, &data);
    gtk_builder_connect_signals(local.builder, &local);

	
    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "MainWindow"));
    
	/* Mise en place des images page 0 et 1*/
	filename1 = g_build_filename ("./ressources/accueil.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data.builder, "im_accueil"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/enregistrer.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data.builder, "im_enregistrer"));
	gtk_image_set_from_file(image,filename1);

    g_free(filename1);


    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);


    gtk_main();

    return 0;
}

void chargement_fiche(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	GtkButton *button;
	char nom[21] ;
	GtkLabel *texte;
    const gchar *txt = "je suis un film";
    char title[100];
    char syno[500];
    int nb;
	/* Mise en place des images du menu */
	filename1 = g_build_filename ("./ressources/op1.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op11"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op2.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op12"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op3.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op13"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op4.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op14"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op5.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op15"));
	gtk_image_set_from_file(image,filename1);
	
	filename1 = g_build_filename ("./ressources/accueil2.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "princ3"));
	gtk_image_set_from_file(image,filename1);
	
      // ouverture du fichier json
	FILE *f = fopen("films.json", "r");
      // test si l'ouverture est un succès
	if (f == NULL) {
        printf("impossible d'ouvrir le fichier");
		return 1;
	}
	
      // préparation du reader afin de lire dans le fichier json
	WJReader doc = WJROpenFILEDocument(f, NULL, 0);
	WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
	movies *m = load_movies(elem, 100);

	/* Récuperation de l'indice du film voulu */
	button = GTK_BUTTON(widget);
	strcat(title,gtk_button_get_label (button));
	memset(title,"",14);
	nb = atoi(title);
	/* Mise de la fiche du film */
	sprintf(nom, "./ressources/%i.jpg",(nb+1));
	filename1 =  g_build_filename (nom, NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "im_fiche"));
	gtk_image_set_from_file(image,filename1);

	/*Titre du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"titre_fiche"));
	strcpy(title,(m->tab[nb])->title);
	gtk_label_set_text(texte, title);
	/*Type du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"type_fiche"));
	switch ((m->tab[nb])->type) {
	case SERIE:
		strcpy(title,"Série");
		break;
	case MOVIE:
		strcpy(title,"Film");
		break;
	}
	gtk_label_set_text(texte,title);
	/* Durée du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"duree_fiche"));
	sprintf(title, "%d", (m->tab[nb])->duration);
	gtk_label_set_text(texte, title);
	/* Année du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"annee_fiche"));
	sprintf(title, "%d", (m->tab[nb])->year);
	gtk_label_set_text(texte,title);
	/*Genre du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"genre_fiche"));
	int i = 0;
	strcpy(title,"");
	while (get_string((m->tab[nb])->genre, i) != NULL && i < 10) {
		if (i!=0) {
			strcat(title, ", ");
		}
    	strcat(title,get_string((m->tab[nb])->genre, i));
		i++;
  }
	gtk_label_set_text(texte, title);
	/* Realisateur du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"realisateur_fiche"));
	strcpy(title,(m->tab[nb])->director);
	gtk_label_set_text(texte,title);
	/* Acteurs du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"acteurs_fiche"));
	i = 0;
	strcpy(title,"");
	while (get_string((m->tab[nb])->actors, i) != NULL && i < 10) {
		if (i!=0) {
			strcat(title, ", ");
		}
		strcat(title, get_string((m->tab[nb])->actors, i));
		i++;
	}
	gtk_label_set_text(texte, title);
	/* Description du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"description_fiche"));
	strcpy(syno,(m->tab[nb])->synopsis);
	gtk_label_set_text(texte,syno);

	/* Note */
	if ((m->tab[nb])->grade == 5) {note5(widget, user_data);}
	else if ((m->tab[nb])->grade == 4) {note4(widget, user_data);}
	else if ((m->tab[nb])->grade == 3) {note3(widget, user_data);}
	else if ((m->tab[nb])->grade == 2) {note2(widget, user_data);}
	else if ((m->tab[nb])->grade == 1) {note1(widget, user_data);}
	else {note0(widget, user_data);}
	destroy_movies_list(m);
      // fermeture de l'élément de la librairie jwelement + libération en mémoire
	WJECloseDocument(elem);
	WJRCloseDocument(doc);
      // fermeture du fichier
	fclose(f);

	g_free(filename1);
}

