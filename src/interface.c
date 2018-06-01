#include"console_display.h"
#include "movies_list_loader.h"
#include "recommendation_list.h"
#include"stringlist.h"
#include "movie.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "biblio_interface.h"
#include <wjelement.h>


#define MOVIE_NB 2
/*--------------------------------------------------------------------------*/
/* FONCTION MAIN*/
int main(int argc, char *argv [])
{
    GtkWidget *fenetre_principale = NULL;
    SGlobalData data;
    SLocalData local;
    Fichier fichier;
    GError *error = NULL;
    gchar *filename = NULL;
	GtkImage *image;
    gchar *filename1;

    /* Initialisation de la bibliothèque Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    data.builder = gtk_builder_new();
    local.builder = gtk_builder_new();
    fichier.builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier interface.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("interface.glade", NULL);

    /* Chargement du fichier interface.glade. */
    gtk_builder_add_from_file (data.builder, filename, &error);
    gtk_builder_add_from_file (local.builder,filename, &error);
    gtk_builder_add_from_file (fichier.builder,filename, &error);
	


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
    gtk_builder_connect_signals(fichier.builder, &local);
	
    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "MainWindow"));
    
	/* Mise en place des images page 0 et 1*/
	filename1 = g_build_filename ("./ressources/accueil.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data.builder, "im_accueil"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/enregistrer.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data.builder, "im_enregistrer"));
	gtk_image_set_from_file(image,filename1);

	//data.m = load_movies(elem, 100);
	
    g_free(filename1);

	fichier.f = fopen("films.json", "r");
     
     // préparation du reader afin de lire dans le fichier json
    fichier.doc = WJROpenFILEDocument(fichier.f, NULL, 0);
    fichier.elem = WJEOpenDocument(fichier.doc, NULL, NULL, NULL);
    data.m = load_movies(fichier.elem, MOVIE_NB);

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);


    gtk_main();

	// libéré l'espace mémoire de la liste de film
	destroy_movies_list(data.m);
	// fermeture de l'élément de la librairie jwelement + libération en mémoire
	WJECloseDocument(fichier.elem);
	WJRCloseDocument(fichier.doc);
	// fermeture du fichier
	fclose(fichier.f);

    return 0;
}


