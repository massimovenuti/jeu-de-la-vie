/**
 * \file grille.c
 * \brief Gestion des grilles du jeu de la vie
 * \author Massimo Venuti
 * \version 1.0
 *
 * Création / destruction et accès aux fichiers externes des grilles du jeu de la vie.
 *
 */
#include "grille.h"


/**
 * \fn void alloue_grille (int l, int c, grille* g)
 * \brief Fonction d'allocation d'une grille de taille l*c, initialise toutes les cellules à mortes.
 *
 * \param l Entier : nombre de lignes.
 * \param c Entier : nombre de colonnes.
 * \param g Adresse de la grille à allouer.
 */
void alloue_grille (int l, int c, grille* g)
{
	int i;
	int j;
	g->nbl = l;
	g->nbc = c;

	g->cellules =  malloc(l * sizeof(*g->cellules));
    for (i = 0 ; i < l ; i++) {
        g->cellules[i] =  malloc(c * sizeof(**g->cellules));
	}

	for (i=0; i<l; i++) 
	{
		for (j=0; j<c; j++)
			set_morte(i, j, *g);
	}
}


/**
 * \fn void libere_grille (grille* g)
 * \brief Fonction de libération d'une grille.
 *
 * \param g Adresse de la grille à libérer.
 */
void libere_grille (grille* g)
{
	free(g->cellules);
}


/**
 * \fn void init_grille_from_file (char * filename, grille* g)
 * \brief Fonction d'allocation et d'initalisation d'une grille à partir d'un fichier.
 *
 * \param filename Chaine de caractères : nom du fichier dans lequel se trouve la configuration initiale de la grille.
 * \param g Adresse de la grille à initialiser.
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}


/**
 * \fn void copie_grille (grille gs, grille gd)
 * \brief Fonction de copie d'une grille (sans allocation).
 *
 * \param gs Grille : grille à copier (source).
 * \param gd Grille : grille à modifier (destination).
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

