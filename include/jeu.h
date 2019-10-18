/**
 * \file jeu.h
 * \brief Fichier d'en-tête du fichier source jeu.c
 * \author Massimo Venuti
 * \version 1.0
 *
 * Prototypes des fonctions et fonction modulo.
 *
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#define VIEILLISSEMENT_INIT 1
#define TEMPS_INIT 1

/**
 * \fn static inline int modulo(int i, int m)
 * \brief Fonction modulo modifiée pour traiter correctement les bords d'une grille dans le calcul des voisins avec bords cycliques.
 *
 * \param l Entier : nombre de lignes.
 * \param c Entier : nombre de colonnes.
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
int compte_voisins_vivants_cyclique (int i, int j, grille g);

int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
void evolue (grille *g, grille *gc);

#endif
