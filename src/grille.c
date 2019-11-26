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

	int i,j,n,l,c,vivantes=0,nonViables=0;
	
	fscanf(pfile, "%d %d", &l, &c);

	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", &vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d %d", &i, &j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", &nonViables);
	for (n=0; n< nonViables; ++n){
		fscanf(pfile, "%d %d", &i, &j);
		set_nonViable(i,j,*g);
	}

	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}


int sont_identiques(grille g1, grille g2) {
	int i,j;
	int test = ((g1.nbl == g2.nbl) && (g1.nbc == g2.nbc)) ? 1 : 0;
	
	for (i = 0; i<g1.nbl && test != 0; i++) {
		for (j = 0; j<g1.nbc; j++) {
			if (est_vivante(i,j,g1) != est_vivante(i,j,g2)) {
				test = 0;
				break;
			}
		}
	}
	return test;
}


int grille_vide(grille g) {
	int i,j;
	int test = 1;
	for (i = 0; i<g.nbl && test != 0; i++) {
		for (j = 0; j<g.nbc; j++) {
			if (est_vivante(i,j,g)) {
				test = 0;
				break;
			}
		}
	}
	return test;		
}