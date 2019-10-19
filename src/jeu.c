/**
 * \file jeu.c
 * \brief Evolutions du jeu de la vie
 * \author Massimo Venuti
 *
 * 
 */
#include "jeu.h"

int (*compte_voisins_vivants)(int, int, grille) = &compte_voisins_vivants_cyclique;
int vieillissement = VIEILLISSEMENT_INIT;


int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	return v; 
}


int compte_voisins_vivants_non_cyclique (int i, int j, grille g){
	int v = 0;
	if (i > 0 && j > 0)
		if(est_vivante(i - 1, j - 1, g)) v++;
	if (i > 0)
		if(est_vivante(i - 1, j, g)>0) v++;
	if (i > 0 && j + 1 < g.nbc)
		if(est_vivante(i - 1, j + 1, g)) v++;
	if (j > 0)
		if(est_vivante(i, j - 1, g)) v++;
	if (j + 1 < g.nbc)
		if(est_vivante(i, j + 1, g)) v++;
	if (i + 1 < g.nbl && j > 0)
		if(est_vivante(i + 1, j - 1, g)) v++;
	if (i + 1 < g.nbl)
		if(est_vivante(i + 1, j, g)) v++;
	if (i + 1 < g.nbl && j + 1 < g.nbc)
		if(est_vivante(i + 1, j + 1, g)) v++;
	return v;
}


void vieillit (int i, int j, grille g) {
	g.cellules[i][j]++;
}


int age_cellule (int i, int j, grille g) {
	return g.cellules[i][j];
}


void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (*compte_voisins_vivants) (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if (v!=2 && v!= 3) 
					set_morte(i,j,*g);
				else if (vieillissement && age_cellule(i,j,*g)>=8)
					set_morte(i,j,*g);
				else
					vieillit(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
