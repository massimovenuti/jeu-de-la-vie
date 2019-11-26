/**
 * \file io.c
 * \brief Gestion des entrées/sorties du jeu de la vie en mode Texte.
 * \author Massimo Venuti
 *
 * Affichage des grilles et des informations du jeu de la vie. Gestion des saisies du joueur.
 *
 */
#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}


void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) 
			printf ("|   "); 
		else if (ligne[i] > 0)
			if (vieillissement)
				printf ("| %d ", ligne[i]);
			else
				printf ("| + ");
		else
			printf ("| X ");
		
	printf("|\n");
	return;
}


void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}


void affiche_temps(int temps) {
	printf("Temps : %d\n", temps);
}


void affiche_oscillation(int periode) {
	(periode > 0) ? printf("Période : %d\n", periode) : printf("Période : 0\n");
}


void affiche_vieillissement() {
	(vieillissement)? printf("Vieillissement : ON")	: printf("Vieillissement : OFF");
}


void affiche_calcul_voisinage() {
	(compte_voisins_vivants == compte_voisins_vivants_cyclique) ? 
		printf("Voisinage cyclique : ON\n") : printf("Voisinage cyclique : OFF\n");
}


void affichage(grille *g, int temps, int periode) {
	affiche_temps(temps);
	affiche_oscillation(periode);
	affiche_calcul_voisinage();
	affiche_vieillissement();
	affiche_grille(*g);
}


void efface_grille (grille g){
    printf("\n\x1b[%dA\x1b[J",g.nbl*2 + 8);
}


void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int temps = TEMPS_INIT;
	int periode = PERIODE_INIT;

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case 'c' :
			{ // touche "c" pour activer/désactiver le voisinage cyclique
				toggle_compte_voisins_vivants();
				break;
			}			
			case 'v' :
			{ // touche "v" pour activer/désactiver le vieillissement
				toggle_vieillissement();
				break;
			}
			case '\n' : 
			{ // touche "entree" pour évoluer
				temps++;
				evolue(g,gc);
				efface_grille(*g);
				affichage(g, temps, periode);
				break;
			}
			case 'n' : 
			{ // touche "n" pour changer de grille
				char chemin_grille[TAILLE_MAX];
				temps = TEMPS_INIT;
				periode = 0;

				efface_grille(*g);
				libere_grille(g);
				libere_grille(gc);

				printf("Veuillez saisir le nom d'une nouvelle grille : ");
				scanf("%s", chemin_grille);
				while(getchar() != '\n'); 

				init_grille_from_file(chemin_grille,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affichage(g, temps, periode);
				break;
			}
			case 'o':
			{
				periode = periode_oscillation_delai(*g);
				break;
			}		
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;	
}
