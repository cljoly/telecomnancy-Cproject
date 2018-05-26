#include <gtk/gtk.h>
#include"biblio_interface.h"

/*-----------------------------------------------------------------------------*/
/* FONCTIONS DE CHANGEMENT DE PAGE*/
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



void vers_page_film(GtkWidget* widget, gpointer user_data)
{
    page_suivante(user_data, 1);
}

void vers_page_biblio(GtkWidget* widget, gpointer user_data)
{
    page_suivante(user_data, 3);
}

void vers_page_info(GtkWidget* widget, gpointer user_data)
{
	page_suivante(user_data, 4);
}

/*-----------------------------------------------------------------------------*/
/* FONCTIONS POUR NOTER LES FILMS */

void vote_nul(gpointer user_data, char *nom)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename;
	GtkImage *image;
	
	filename = g_build_filename ("./ressources/nvote.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, nom));
	gtk_image_set_from_file(image,filename);
	g_free(filename);
}

void vote_bien(gpointer user_data, char *nom)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename;
	GtkImage *image;
	
	filename = g_build_filename ("./ressources/bvote.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, nom));
	gtk_image_set_from_file(image,filename);
	g_free(filename);
}

void note1(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");

	vote_nul(user_data, "image2");
	vote_nul(user_data, "image3");
	vote_nul(user_data, "image4");
	vote_nul(user_data,"image5");
}

void note2(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data,"image1");	
	vote_bien(user_data,"image2");
	
	vote_nul(user_data, "image3");
	vote_nul(user_data,"image4");
	vote_nul(user_data,"image5");
}

void note3(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");
	vote_bien(user_data, "image2");
	vote_bien(user_data, "image3");
	
	vote_nul(user_data, "image4");
	vote_nul(user_data, "image5");
}

void note4(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");
	vote_bien(user_data, "image2");
	vote_bien(user_data, "image3");
	vote_bien(user_data, "image4");
	
	vote_nul(user_data, "image5");
}

void note5(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");
	vote_bien(user_data,"image2");
	vote_bien(user_data,"image3");
	vote_bien(user_data, "image4");
	vote_bien(user_data, "image5");
}
/*--------------------------------------------------------------------------*/
/* CHARGEMENT DES PAGES */



void chargement_principale(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	
	/* Mise en place des images du menu */
	filename1 = g_build_filename ("./ressources/op1.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op1"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op2.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op2"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op3.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op3"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op4.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op4"));
	gtk_image_set_from_file(image,filename1);
	filename1 = g_build_filename ("./ressources/op5.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "op5"));
	gtk_image_set_from_file(image,filename1);
	
	filename1 = g_build_filename ("./ressources/accueil2.png", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "princ1"));
	gtk_image_set_from_file(image,filename1);
	
	g_free(filename1);
}

void chargement_fiche(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	char nom[21] ;
	int titre = 100;
	
	sprintf(nom, "./ressources/%d.jpg", titre);

	
	filename1 =  g_build_filename (nom, NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "im_fiche"));
	gtk_image_set_from_file(image,filename1);
	
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
	
	/* Mise en place de l'image du film */


	
	g_free(filename1);
}




/*--------------------------------------------------------------------------*/
/* FONCTIONS IMAGE */
void changer_image(gpointer user_data) 
{
	SGlobalData *data = (SGlobalData*) user_data;
	GtkImage *image;

    gchar *filename;

        char cle3[3];

        strcat(cle3,"h");
        //sprintf(cle3, "%d", 1);
        strcat(cle3,"1"); 
		
        printf( "%s", cle3);
        filename = g_build_filename ("./ressources/titanic.jpg", NULL);
		image = GTK_IMAGE(gtk_builder_get_object(data->builder, cle3));
		gtk_image_set_from_file(image,filename);
		strcpy(cle3,"h2");
		printf( "%s", cle3);
		        filename = g_build_filename ("./ressources/test.png", NULL);
		image = GTK_IMAGE(gtk_builder_get_object(data->builder, cle3));
		gtk_image_set_from_file(image,filename);
    g_free(filename);
}



void test2(GtkWidget* widget, gpointer user_data)
{
    SGlobalData *data = (SGlobalData*) user_data;
	GtkImage *image;
    gchar *filename;
	char cle3[3];
	
	strcat(cle3,"h");
	//sprintf(cle3, "%d", 1);
	strcat(cle3,"1"); 
	filename = g_build_filename ("./ressources/titanic.jpg", NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, cle3));
	gtk_image_set_from_file(image,filename);

    g_free(filename);
}
void test(GtkWidget* widget, gpointer user_data)
{
    changer_image(user_data);
}

   
   
/* https://cps-static.rovicorp.com/2/Open/20th_Century_Fox_39/Program/125613/_9by13/_derived_jpg_q90_410x410_m0/Titanic-Poster3x4.jpg?partner=allrovi.com */ 
    
/*--------------------------------------------------------------------------*/
/* Initialisation des structures */

    
/*--------------------------------------------------------------------------*/
/*FONCTIONS DE CREATION DE COMPTE*/

void *nouveau_compte (GtkWidget* widget , gpointer user_data, gpointer local_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	SLocalData *local = (SLocalData*) local_data;
	GtkEntry *entree;
	GtkToggleButton *button;
	GtkWidget *msg;
	const char *mdp2;
	gboolean robot;
	int erreur = 0;
    
	entree = GTK_ENTRY(gtk_builder_get_object(data->builder,"nom"));
	if (gtk_entry_get_text_length(entree) == 0)
	{
		erreur=1;
	}
	else
	{
		local->nom = gtk_entry_get_text(entree);
		entree = GTK_ENTRY(gtk_builder_get_object(data->builder,"prenom"));
		if (gtk_entry_get_text_length(entree) == 0)
		{
			erreur=1;
		}
		else
		{
			local->prenom = gtk_entry_get_text(entree);
			entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "identifiant"));
			if (gtk_entry_get_text_length(entree) == 0)
			{
				erreur=1;
			}
			else
			{
				local->identifiant = gtk_entry_get_text(entree);
				entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "mail"));
			
				if (gtk_entry_get_text_length(entree) == 0)
				{
					erreur=1;
				}
				else
				{
					local->mail = gtk_entry_get_text(entree);
					entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "mdp"));
					if (gtk_entry_get_text_length(entree) == 0)
					{
						erreur=1;
					}
					else
					{
						local->mdp = gtk_entry_get_text(entree);
						entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "mdp2"));
						mdp2 = gtk_entry_get_text(entree);
						if (strcmp(local->mdp, mdp2))
						{
							erreur=1;
						}
						else
						{
							button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data->builder,"homme"));
							local->sexe = gtk_toggle_button_get_active(button);
							button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data->builder,"femme"));
							/* 1 pour homme 0 pour femme */
							if ( local->sexe == gtk_toggle_button_get_active(button))
							{
								erreur=1;;
							}
							else
							{
								button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data->builder,"robot"));
								robot = gtk_toggle_button_get_active(button);
								if (!robot)
								{
									//local.robot =1;
									erreur=1;
								}
							}
						}
					}
				}
			}
		}
	}
	if (erreur)
	{
		strcpy(local->identifiant, "null");
		strcpy(local->mdp, "null");
		erreur =0;
		msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
		gtk_widget_show(msg);
	}
	else
	{
		page_suivante(user_data, 0);
	}
	return local;
	
}
/*-----------------------------------------------------------------------------*/
/* FONCTIONS CONNEXION */

void connexion(GtkWidget* widget, gpointer user_data, gpointer local_data)
{
//	SGlobalData *data = (SGlobalData*) user_data;
//	SLocalData *local = (SLocalData*) local_data;
//	char *entree1;
//	GtkEntry *entree;
	

//	if (local->robot==0)
//	{
//		entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "connexion_id"));
//		entree1 = gtk_entry_get_text(entree);
//		if (strcmp(local->identifiant, entree1)==0)
//		{
//			entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "connexion_mdp"));
//			entree1 = gtk_entry_get_text(entree);
//			if(strcmp(local->mdp,entree1)==0)
//			{
				page_suivante(user_data, 2);
//			}
//		}
//	}
}

