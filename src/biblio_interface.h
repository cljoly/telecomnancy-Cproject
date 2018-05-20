#ifndef PROJECT_INTERFACE_H
#define PROJECT_INTERFACE_H

#include <gtk/gtk.h>
     
typedef struct
{
	GtkBuilder *builder;
	gpointer user_data;
} SGlobalData;

void page_suivante(gpointer user_data, int page);

void vers_page_creation(GtkWidget* widget, gpointer user_data);

void vers_page_principale(GtkWidget* widget, gpointer user_data);

void vers_page_accueil(GtkWidget* widget, gpointer user_data);

#endif //PROJECT_INTERFACE_H
