/**
 * \file main.c
 * \brief Jeu de la vie
 * \author Massimo Venuti
 *
 * Programme de base du jeu de la vie mettant en scène une série de grilles initiales prédéfinies pouvant être séléctionnées par le joueur.
 *
 */
#include <stdio.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 * \fn int main (int argc, char ** argv)
 * \brief Entrée du programme
 *
 * \param argc Chaine de caractères : nom du programme.
 * \param argv Chaine de caractères : nom de la grille à charger.
 * \return 0 si aucune erreur.
 */
int main (int argc, char ** argv) {

	char path[TAILLE_MAX]=PATH;
	char extension[TAILLE_MAX]= EXTENSION;

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	strcat(strcat(path, argv[1]), extension);
	
	grille g, gc;
	init_grille_from_file(path,&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	affiche_grille(g);
	affichage(&g, TEMPS_INIT);

	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
