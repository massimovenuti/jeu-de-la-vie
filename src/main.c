/**
 * \file main.c
 * \brief Jeu de la vie
 * \author Massimo Venuti
 *
 * Programme de base du jeu de la vie mettant en scène une série de grilles initiales prédéfinies pouvant être séléctionnées par le joueur.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "io_gui.h"
#include "grille.h"
#include "jeu.h"
#include "io.h"

/**
 * \fn int main (int argc, char ** argv)
 * \brief Entrée du programme - mode Texte.
 *
 * \param argc Chaine de caractères : nom du programme.
 * \param argv Chaine de caractères : nom de la grille à charger.
 * \return 0 si aucune erreur.
 */
int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}	

	// Initialise la grille
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	// Lancement du jeu
	if (CAIRO)
		affichage_GUI(&g, &gc);
	else {
		affichage(&g, TEMPS_INIT, PERIODE_INIT);
		debut_jeu(&g, &gc);
	}

	// Libère la grille
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}