/**
 * \file io.c
 * \brief Gestion des entrées/sorties du jeu de la vie
 * \author Massimo Venuti
 * \version 1.0
 *
 * Affichage des grilles et gestion des saisies du joueur lors du jeu de la vie.
 *
 */
#include "io.h"


/**
 * \fn void affiche_trait (int c)
 * \brief Fonction d'affichage d'un trait horizontal.
 *
 * \param c Entier : nombre de colonnes de la grille.
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}


/**
 * \fn void affiche_ligne (int c, int* ligne)
 * \brief Fonction d'affichage d'une ligne de la grille.
 *
 * \param c Entier : nombre de colonnes de la grille.
 * \param ligne Tableau d'entiers : ligne de la grille.
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ", ligne[i]);
	printf("|\n");
	return;
}

/**
 * \fn void affiche_grille (grille g)
 * \brief Fonction d'affichage d'une grille.
 *
 * \param g Grille : grille à afficher.
 */
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
	efface_grille(*g);
	affiche_temps(temps);
	affiche_calcul_voisinage();
	affiche_vieillissement();
	affiche_grille(*g);
}

/**
 * \fn void efface_grille (grille g)
 * \brief Fonction d'effacement d'une grille.
 *
 * \param g Grille : grille à effacer.
 */
void efface_grille (grille g){
    printf("\n\x1b[%dA\x1b[J",g.nbl*2 + 100);
}

/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \brief Fonction pour débuter le jeu. Saisir la touche q permet de quitter le jeu, entrée permet de faire évoluer le jeu d'un temps, n permet d'entrée une nouvelle grille (ex : grille1).
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 */
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
				affichage(g, temps);
				break;
			}
			case 'n' : 
			{ // touche "n" pour changer de grille
				temps = 0;
				char nomFichier[TAILLE_MAX];
				char path[TAILLE_MAX] = PATH;

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
					compte_voisins_vivants = compte_voisins_vivants_non_cyclique;
				else 
					compte_voisins_vivants = compte_voisins_vivants_cyclique;
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
