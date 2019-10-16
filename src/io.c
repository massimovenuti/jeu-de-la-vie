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
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
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

/**
 * \fn void efface_grille (grille g)
 * \brief Fonction d'effacement d'une grille.
 *
 * \param g Grille : grille à effacer.
 */
void efface_grille (grille g){
    printf("\n\x1b[%dA\x1b[J",g.nbl*2 + 5); 
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

	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' : 
			{
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
				affiche_grille(*g);

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
