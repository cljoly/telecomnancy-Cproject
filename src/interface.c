
#include <gtk/gtk.h>
#include "biblio_interface.c"
#include <string.h>
#include <stdlib.h>


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

void chargement_biblio(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	char nom[21];
	char im_nom[5];
	

	/* Mise en place des images du menu */
	filename1 = g_build_filename ("./ressources/op1.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op6"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op2.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op7"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op3.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op8"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op4.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op9"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op5.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op10"));
	gtk_image_set_from_file(image,filename1);
	
	filename1 = g_build_filename ("./ressources/accueil2.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "princ2"));
	gtk_image_set_from_file(image,filename1);
	
	for (int i=1; i<101; i++)
	{	
		sprintf(nom, "./ressources/%d.jpg", i);
		sprintf(im_nom, "h%d",i);
		filename1 =  g_build_filename (nom, NULL);
		image = GTK_IMAGE(gtk_builder_get_object(data->builder, im_nom));
		gtk_image_set_from_file(image,filename1);
	}
	
	g_free(filename1);
}
