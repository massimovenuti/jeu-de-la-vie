/**
 * \file io.c
 * \brief Gestion des entrées/sorties du jeu de la vie
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
			printf ("| %d ", ligne[i]);
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


void affiche_vieillissement() {
	if (vieillissement)
		printf("Vieillissement : activé");
	else 
		printf("Vieillissement : désactivé");
}


void affiche_calcul_voisinage() {
	if (compte_voisins_vivants == compte_voisins_vivants_cyclique) 
		printf("Voisinage cyclique : activé\n");
	else 
		printf("Voisinage cyclique : désactivé\n");
}


void affichage(grille *g, int temps) {
	affiche_temps(temps);
	affiche_calcul_voisinage();
	affiche_vieillissement();
	affiche_grille(*g);
}


void efface_grille (grille g){
    printf("\n\x1b[%dA\x1b[J",g.nbl*2 + 7);
}


void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	char extension[] = EXTENSION;
	int temps = TEMPS_INIT;

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				temps++;
				evolue(g,gc);
				efface_grille(*g);
				affichage(g, temps);
				break;
			}
			case 'n' : 
			{ // touche "n" pour changer de grille
				temps = 0;
				char nomFichier[TAILLE_MAX];
				char path[TAILLE_MAX] = PATH;

				efface_grille(*g);
				libere_grille(g);
				libere_grille(gc);

				printf("Veuillez saisir le nom d'une nouvelle grille : ");
				scanf("%s", nomFichier);
				while(getchar() != '\n'); 
				strcat(strcat(path, nomFichier), extension);

				init_grille_from_file(path,g);
				alloue_grille (g->nbl, g->nbc, gc);

				affichage(g, temps);
				break;
			}
			case 'c' :
			{ // touche "c" pour activer/désactiver le voisinage cyclique
				if (compte_voisins_vivants == compte_voisins_vivants_cyclique)
					compte_voisins_vivants = &compte_voisins_vivants_non_cyclique;
				else 
					compte_voisins_vivants = &compte_voisins_vivants_cyclique;
				break;
			}			
				
			case 'v' :
			{ // touche "v" pour activer/désactiver le vieillissement
				vieillissement = !vieillissement;
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
