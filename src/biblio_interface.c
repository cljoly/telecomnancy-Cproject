#include <gtk/gtk.h>
#include"biblio_interface.h"
#include"console_display.h"
#include "movies_list_loader.h"
#include "recommendation_list.h"
#include "movie.h"
#include"stringlist.h"
#include"recommendation.h"
#include <wjelement.h>


#define MOVIE_NB 100
char *nom_utilisateur;
int liste_reco[10];
int indice_film;
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
void note0(GtkWidget *widget, gpointer user_data)
{
    vote_nul(user_data, "image1");
    vote_nul(user_data, "image2");
	vote_nul(user_data, "image3");
	vote_nul(user_data, "image4");
	vote_nul(user_data,"image5");
}

void note1(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");

	vote_nul(user_data, "image2");
	vote_nul(user_data, "image3");
	vote_nul(user_data, "image4");
	vote_nul(user_data,"image5");
	changer_note(widget, user_data,1);
}

void note2(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data,"image1");	
	vote_bien(user_data,"image2");
	
	vote_nul(user_data, "image3");
	vote_nul(user_data,"image4");
	vote_nul(user_data,"image5");
	changer_note(widget, user_data,2);
}

void note3(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");
	vote_bien(user_data, "image2");
	vote_bien(user_data, "image3");
	
	vote_nul(user_data, "image4");
	vote_nul(user_data, "image5");
	changer_note(widget, user_data,3);
}

void note4(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");
	vote_bien(user_data, "image2");
	vote_bien(user_data, "image3");
	vote_bien(user_data, "image4");
	
	vote_nul(user_data, "image5");
	changer_note(widget, user_data,4);
}

void note5(GtkWidget *widget, gpointer user_data)
{
	vote_bien(user_data, "image1");
	vote_bien(user_data,"image2");
	vote_bien(user_data,"image3");
	vote_bien(user_data, "image4");
	vote_bien(user_data, "image5");
	changer_note(widget, user_data,5);
}

void changer_note(GtkWidget *widget, gpointer user_data, int note)
{
	FILE *f = fopen("films.json", "r");

     // préparation du reader afin de lire dans le fichier json
    WJReader doc = WJROpenFILEDocument(f, NULL, 0);
    WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
    movies *m = load_movies(elem, MOVIE_NB);
    m->user = nom_utilisateur;
    load_grade(m);
    m->tab[indice_film]->grade = (int) note;

    save_grade(m);
    // libéré l'espace mémoire de la liste de film
	destroy_movies_list(m);
	// fermeture de l'élément de la librairie jwelement + libération en mémoire
	WJECloseDocument(elem);
	WJRCloseDocument(doc);
	// fermeture du fichier
	fclose(f);
}
/*--------------------------------------------------------------------------*/
/* CHARGEMENT DES PAGES */

void chargement_fiche(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	GtkButton *button;
	char nom[21];
	char try[16];
	GtkLabel *texte;
    char title[100];
    char syno[500];
    char pb1[10];
	char pb2[10];
	char pb3[10];
	int number;
	int identifiant;
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

	}
	
      // préparation du reader afin de lire dans le fichier json
	WJReader doc = WJROpenFILEDocument(f, NULL, 0);
	WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
	movies *m = load_movies(elem, 100);

	/* Récuperation de l'indice du film voulu */
	button = GTK_BUTTON(widget);
	strcat(try,gtk_button_get_label (button));
	sscanf(try, "%s %s %s %d", pb1, pb2, pb3, &number);
	indice_film = number-1;
	m->user = nom_utilisateur;
    load_grade(m);
	/* Mise de la fiche du film */
	sprintf(nom, "./ressources/%i.jpg",number);
	filename1 =  g_build_filename (nom, NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "im_fiche"));
	gtk_image_set_from_file(image,filename1);
    number = number-1;
	/*Titre du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"titre_fiche"));
	strcpy(title,(m->tab[number])->title);
	gtk_label_set_text(texte, title);
	/*Type du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"type_fiche"));
	switch ((m->tab[number])->type) {
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
	sprintf(title, "%d", (m->tab[number])->duration);
	gtk_label_set_text(texte, title);
	/* Année du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"annee_fiche"));
	sprintf(title, "%d", (m->tab[number])->year);
	gtk_label_set_text(texte,title);
	/*Genre du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"genre_fiche"));
	int i = 0;
	strcpy(title,"");
	while (get_string((m->tab[number])->genre, i) != NULL && i < 10) {
		if (i!=0) {
			strcat(title, ", ");
		}
    	strcat(title,get_string((m->tab[number])->genre, i));
		i++;
  }
	gtk_label_set_text(texte, title);
	/* Realisateur du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"realisateur_fiche"));
	strcpy(title,(m->tab[number])->director);
	gtk_label_set_text(texte,title);
	/* Acteurs du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"acteurs_fiche"));
	i = 0;
	strcpy(title,"");
	while (get_string((m->tab[number])->actors, i) != NULL && i < 10) {
		if (i!=0) {
			strcat(title, ", ");
		}
		strcat(title, get_string((m->tab[number])->actors, i));
		i++;
	}
	gtk_label_set_text(texte, title);
	/* Description du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"description_fiche"));
	strcpy(syno,(m->tab[number])->synopsis);
	gtk_label_set_text(texte,syno);

	/* Note */
	
	if ((m->tab[number])->grade == 5) {note5(widget, user_data);}
	else if ((m->tab[number])->grade == 4) {note4(widget, user_data);}
	else if ((m->tab[number])->grade == 3) {note3(widget, user_data);}
	else if ((m->tab[number])->grade == 2) {note2(widget, user_data);}
	else if ((m->tab[number])->grade == 1) {note1(widget, user_data);}
	else {note0(widget, user_data);}
	destroy_movies_list(m);
      // fermeture de l'élément de la librairie jwelement + libération en mémoire
	WJECloseDocument(elem);
	WJRCloseDocument(doc);
      // fermeture du fichier
	fclose(f);

	g_free(filename1);
}

void chargement_fiche2(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	GtkButton *button;
	char nom[21];
	char try[16];
	GtkLabel *texte;
    char title[100];
    char syno[500];
    char pb1[10];
	char pb2[10];
	char pb3[10];
	int number;
	int identifiant;
	
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

	}
	
      // préparation du reader afin de lire dans le fichier json
	WJReader doc = WJROpenFILEDocument(f, NULL, 0);
	WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
	movies *m = load_movies(elem, 100);

 
	/* Récuperation de l'indice du film voulu */
	button = GTK_BUTTON(widget);
	strcat(try,gtk_button_get_label (button));
	sscanf(try, "%s %s %s %d", pb1, pb2, pb3, &number);
	
	m->user = nom_utilisateur;
    load_grade(m);
	/* Chargement des images */

	identifiant = liste_reco[number-1];
	indice_film = identifiant;
	/* Mise de la fiche du film */
	
	sprintf(nom, "./ressources/%i.jpg",identifiant+1);
	filename1 =  g_build_filename (nom, NULL);
	image = GTK_IMAGE(gtk_builder_get_object(data->builder, "im_fiche"));
	gtk_image_set_from_file(image,filename1);

	/*Titre du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"titre_fiche"));
	strcpy(title,(m->tab[identifiant])->title);
	gtk_label_set_text(texte, title);
	/*Type du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"type_fiche"));
	switch ((m->tab[identifiant])->type) {
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
	sprintf(title, "%d", (m->tab[identifiant])->duration);
	gtk_label_set_text(texte, title);
	/* Année du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"annee_fiche"));
	sprintf(title, "%d", (m->tab[identifiant])->year);
	gtk_label_set_text(texte,title);
	/*Genre du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"genre_fiche"));
	int i = 0;
	strcpy(title,"");
	while (get_string((m->tab[identifiant])->genre, i) != NULL && i < 10) {
		if (i!=0) {
			strcat(title, ", ");
		}
    	strcat(title,get_string((m->tab[identifiant])->genre, i));
		i++;
  }
	gtk_label_set_text(texte, title);
	/* Realisateur du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"realisateur_fiche"));
	strcpy(title,(m->tab[identifiant])->director);
	gtk_label_set_text(texte,title);
	/* Acteurs du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"acteurs_fiche"));
	i = 0;
	strcpy(title,"");
	while (get_string((m->tab[identifiant])->actors, i) != NULL && i < 10) {
		if (i!=0) {
			strcat(title, ", ");
		}
		strcat(title, get_string((m->tab[identifiant])->actors, i));
		i++;
	}
	gtk_label_set_text(texte, title);
	/* Description du film */
	texte = GTK_LABEL(gtk_builder_get_object(data->builder,"description_fiche"));
	strcpy(syno,(m->tab[identifiant])->synopsis);
	gtk_label_set_text(texte,syno);

	/* Note */
	if ((m->tab[identifiant])->grade == 5) {note5(widget, user_data);}
	else if ((m->tab[identifiant])->grade == 4) {note4(widget, user_data);}
	else if ((m->tab[identifiant])->grade == 3) {note3(widget, user_data);}
	else if ((m->tab[identifiant])->grade == 2) {note2(widget, user_data);}
	else if ((m->tab[identifiant])->grade == 1) {note1(widget, user_data);}
	else {note0(widget, user_data);}
	destroy_movies_list(m);
      // fermeture de l'élément de la librairie jwelement + libération en mémoire
	WJECloseDocument(elem);
	WJRCloseDocument(doc);
      // fermeture du fichier
	fclose(f);

	g_free(filename1);
}


void chargement_principale2(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	int number;
	char nom[25];
	char im_nom[10];

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
		
	FILE *f = fopen("films.json", "r");
	// test si l'ouverture est un succès
	if (f == NULL) 
	{
		printf("impossible d'ouvrir le fichier");
		return 1;
	 }
	// préparation du reader afin de lire dans le fichier json
	WJReader doc = WJROpenFILEDocument(f, NULL, 0);
	WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
	// charge la liste de film
	movies *m = load_movies(elem, MOVIE_NB);

	m->user = nom_utilisateur;
	load_grade(m);
	//movies *mov = data->m;
	recommendations_factorisation(m);
	save_grade(m);
	/* Chargement des images */
	for (int i=0; i<10; i++)
	{	
		number = get_id(m->recommendations,i);
		liste_reco[i]=number;
		sprintf(nom, "./ressources/%d.jpg", number+1);
		sprintf(im_nom, "rec%d",i+1);
		filename1 =  g_build_filename (nom, NULL);
		image = GTK_IMAGE(gtk_builder_get_object(data->builder, im_nom));
		gtk_image_set_from_file(image,filename1);
	}
	// libéré l'espace mémoire de la liste de film
	destroy_movies_list(m);
	// fermeture de l'élément de la librairie jwelement + libération en mémoire
	 WJECloseDocument(elem);
	WJRCloseDocument(doc);

	fclose(f);
	g_free(filename1);
}

void chargement_principale(GtkWidget* widget, gpointer user_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	gchar *filename1;
	GtkImage *image;
	int number;
	char nom[21];
	char im_nom[5];

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

    
/*--------------------------------------------------------------------------*/
/*FONCTIONS DE CREATION DE COMPTE*/

int nouveau_compte (GtkWidget* widget , gpointer user_data, gpointer local_data)
{
	SGlobalData *data = (SGlobalData*) user_data;
	SLocalData *local = (SLocalData*) local_data;
	GtkEntry *entree;
	GtkToggleButton *button;
	GtkWidget *msg;
	const char *mdp2;
	gboolean robot=0;

	entree = GTK_ENTRY(gtk_builder_get_object(data->builder,"nom"));
	if (gtk_entry_get_text_length(entree) == 0)
	{
		msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
		gtk_widget_show(msg);
		return 1;
	}
	else
	{
		//local->nom = gtk_entry_get_text(entree);
		entree = GTK_ENTRY(gtk_builder_get_object(data->builder,"prenom"));
		if (gtk_entry_get_text_length(entree) == 0)
		{
			printf("1");
			msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
			gtk_widget_show(msg);
			return 1;;
		}
		else
		{
			//local->prenom = gtk_entry_get_text(entree);
			entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "identifiant"));
			if (gtk_entry_get_text_length(entree) == 0)
			{
				printf("2");
				msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
				gtk_widget_show(msg);
				return 1;
			}
			else
			{
				//local->identifiant = gtk_entry_get_text(entree);
				entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "mail"));
			
				if (gtk_entry_get_text_length(entree) == 0)
				{
					printf("3");
					msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
					gtk_widget_show(msg);
					return 1;
				}
				else
				{
					//local->mail = gtk_entry_get_text(entree);
					entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "mdp"));
					if (gtk_entry_get_text_length(entree) == 0)
					{
						printf("4");
						msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
						gtk_widget_show(msg);
						return 1;
					}
					else
					{
						local->mdp = gtk_entry_get_text(entree);
						entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "mdp2"));
						mdp2 = gtk_entry_get_text(entree);
						if (strcmp(local->mdp, mdp2)!=0)
						{
							printf("5");
							msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
							gtk_widget_show(msg);
							return 1;
						}
						else
						{
							button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data->builder,"homme"));
							//local->sexe = gtk_toggle_button_get_active(button);
							button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data->builder,"femme"));
							/* 1 pour homme 0 pour femme */
							if ( local->sexe == gtk_toggle_button_get_active(button))
							{
							printf("6");
								msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
								gtk_widget_show(msg);
								return 1;
							}
							else
							{
								button = GTK_TOGGLE_BUTTON(gtk_builder_get_object(data->builder,"robot"));
								robot = gtk_toggle_button_get_active(button);
								if (!robot)
								{
								printf("7");
									msg = GTK_WIDGET(gtk_builder_get_object(data->builder, "enr_erreur"));
									gtk_widget_show(msg);;
									return 1;
								}
							}
						}
					}
				}
			}
		}
	}

	entree = GTK_ENTRY(gtk_builder_get_object(data->builder, "identifiant"));
	nom_utilisateur= gtk_entry_get_text(entree);
	
	chargement_principale2(widget, user_data); 
	page_suivante(user_data, 2);
	return 0;
	
}

SGlobalData *create_data()
{
  SGlobalData *data = malloc(sizeof(SGlobalData));
  return data;
}

SLocalData *create_local()
{
	SLocalData *local =  malloc(sizeof(SLocalData));
    return local;
}



/*-----------------------------------------------------------------------------*/
/* FONCTIONS CONNEXION */
//gchar *user;
int connexion(GtkWidget* widget, gpointer user_data)
{	
    SGlobalData *data =  create_data();
	data = (SGlobalData*) user_data;
    const gchar *user;
	GtkEntry *entree;
	gchar *filename1;
	GtkImage *image;
	int number;
	char nom[27];
	char im_nom[8];
	entree=GTK_ENTRY(gtk_builder_get_object(data->builder,"connexion"));
	
	if (gtk_entry_get_text_length(entree) == 0)
	{
	}
	else
	{	
		user = gtk_entry_get_text(entree);
		data->identifiant = user;
		(data->m)->user=user;
		
		
	FILE *f = fopen("films.json", "r");
	// test si l'ouverture est un succès
	if (f == NULL) 
	{
		printf("impossible d'ouvrir le fichier");
		return 1;
	 }
	// préparation du reader afin de lire dans le fichier json
	WJReader doc = WJROpenFILEDocument(f, NULL, 0);
	WJElement elem = WJEOpenDocument(doc, NULL, NULL, NULL);
	// charge la liste de film
	movies *m = load_movies(elem, MOVIE_NB);

	m->user = user;
	load_grade(m);
	nom_utilisateur = user;		
	//movies *mov = data->m;
	recommendations_factorisation(m);
	save_grade(m);
	/* Chargement des images */
	for (int i=0; i<10; i++)
	{	
		number = get_id(m->recommendations,i);
		liste_reco[i]=number;
		sprintf(nom, "./ressources/%d.jpg", number+1);
		sprintf(im_nom, "rec%d",i+1);
		filename1 =  g_build_filename (nom, NULL);
		image = GTK_IMAGE(gtk_builder_get_object(data->builder, im_nom));
		gtk_image_set_from_file(image,filename1);
	}
	// libéré l'espace mémoire de la liste de film
	destroy_movies_list(m);
	// fermeture de l'élément de la librairie jwelement + libération en mémoire
	 WJECloseDocument(elem);
	WJRCloseDocument(doc);
		page_suivante(user_data, 2);
	}
	return 0;
	
}

void quitter(GtkWidget *widget, gpointer user_data)
{
    gtk_main_quit();
}

