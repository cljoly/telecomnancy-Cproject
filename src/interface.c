
#include <gtk/gtk.h>
#include "biblio_interface.h"
#include <string.h>


int main(int argc, char *argv [])
{
    GtkWidget *fenetre_principale = NULL;
    SGlobalData data;
    GError *error = NULL;
    gchar *filename = NULL;

    /* Initialisation de la bibliothèque Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale */
    data.builder = gtk_builder_new();

    /* Création du chemin complet pour accéder au fichier interface.glade. */
    /* g_build_filename(); construit le chemin complet en fonction du système */
    /* d'exploitation. ( / pour Linux et \ pour Windows) */
    filename =  g_build_filename ("interface.glade", NULL);

    /* Chargement du fichier interface.glade. */
    gtk_builder_add_from_file (data.builder, filename, &error);
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

    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "MainWindow"));

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    gtk_main();

    return 0;
}

void page_suivante(gpointer user_data, int page)
{ 
    SGlobalData *data = (SGlobalData*) user_data;
    GtkNotebook *notebook;

    notebook = GTK_NOTEBOOK(gtk_builder_get_object(data->builder, "Notebook"));
    gtk_notebook_set_current_page(notebook, page);
}

void vers_page_creation(GtkWidget* widget, gpointer user_data)
{
    page_suivante(user_data,1);
}

void vers_page_principale(GtkWidget* widget, gpointer user_data)
{
    page_suivante(user_data, 2);
}

void vers_page_accueil(GtkWidget* widget, gpointer user_data)
{
    page_suivante(user_data,0);
}

   
   
/* https://cps-static.rovicorp.com/2/Open/20th_Century_Fox_39/Program/125613/_9by13/_derived_jpg_q90_410x410_m0/Titanic-Poster3x4.jpg?partner=allrovi.com */ 
    
