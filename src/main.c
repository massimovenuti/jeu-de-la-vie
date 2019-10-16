#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"

int main (int argc, char ** argv) {

	char path[]=PATH;
	char extension[]= EXTENSION;

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
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
