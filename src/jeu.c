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


void toggle_compte_voisins_vivants() {
	if (compte_voisins_vivants == compte_voisins_vivants_cyclique)
		compte_voisins_vivants = &compte_voisins_vivants_non_cyclique;
	else 
		compte_voisins_vivants = &compte_voisins_vivants_cyclique;
}


void toggle_vieillissement() {
	vieillissement = !vieillissement;
}


int periode_oscillation_courante(grille g) {
	grille gtmp, gctmp;
	int periode;
	alloue_grille(g.nbl, g.nbc, &gtmp);
	alloue_grille(g.nbl, g.nbc, &gctmp);
	copie_grille(g, gtmp);

	if(grille_vide(g)) 
		return -1;

	for (periode = 0; periode < PERIODE_MAX; periode++) {
		evolue(&gtmp, &gctmp);
		if (sont_identiques(g,gtmp)) 
			break;
	}

	libere_grille(&gtmp);
	libere_grille(&gctmp);
	return (periode == PERIODE_MAX) ? -1 : periode+1;
}


int periode_oscillation_delai(grille g) {
	grille gtmp, gctmp;
	int periode = -1;
	alloue_grille(g.nbl, g.nbc, &gtmp);
	alloue_grille(g.nbl, g.nbc, &gctmp);
	copie_grille(g, gtmp);

	for (int i = 0; i < PERIODE_MAX && periode == -1; i++) {
		periode = periode_oscillation_courante(gtmp);
		evolue(&gtmp, &gctmp);
	}

	libere_grille(&gtmp);
	libere_grille(&gctmp);
	return periode;
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
			else if (age_cellule(i,j,*g)==0)
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
}
