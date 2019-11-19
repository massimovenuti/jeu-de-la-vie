/**
 * \file jeu.h
 * \brief Fichier d'en-tête du fichier source jeu.c
 * \author Massimo Venuti
 *
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


/**
 * \fn int compte_voisins_vivants_cyclique (int i, int j, grille g)
 * \brief Fonction comptant le nombre de voisins vivants d'une cellule [i,j] : les bords sont cycliques.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème colonne de la grille.
 * \param g Grille : grille en jeu.
 * \return Entier : nombre de voisins vivants d'une cellule 
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);


/**
 * \fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g)
 * \brief Fonction comptant le nombre de voisins vivants d'une cellule [i,j] : les bords ne sont pas cycliques.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème colonne de la grille.
 * \param g Grille : grille en jeu.
 * \return Entier : nombre de voisins vivants d'une cellule 
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);


void toggle_compte_voisins_vivants();


void toggle_vieillissement();


/**
 * \fn void evolue (grille *g, grille *gc)
 * \brief Fonction faisant évoluer la grille d'un pas de temps.
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 */
void evolue (grille *g, grille *gc);

#endif
