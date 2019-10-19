/**
 * \file grille.c
 * \brief Gestion des grilles du jeu de la vie
 * \author Massimo Venuti
 *
 * Création / destruction et accès aux fichiers externes des grilles du jeu de la vie.
 *
 */
#include "grille.h"

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


void libere_grille (grille* g)
{
	free(g->cellules);
}


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


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

