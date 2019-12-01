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
#define PERIODE_MAX 50

/**
 * \fn static inline int modulo(int i, int m)
 * \brief Fonction modulo modifiée.
 *
 * \param i Entier : premier opérande.
 * \param m Entier : second opérande.
 * \return Entier : résultat du modulo modifié (i+m)%m.
 */
static inline int modulo(int i, int m) {return (i+m)%m;}


/**
 * \fn int compte_voisins_vivants_cyclique (int i, int j, grille g)
 * \brief Fonction renvoyant le nombre de voisins vivants d'une cellule [i,j] - les bords sont cycliques.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème colonne de la grille.
 * \param g Grille : grille en jeu.
 * \return Entier : nombre de voisins vivants de la cellule.
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g);


/**
 * \fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g)
 * \brief Fonction renvoyant le nombre de voisins vivants d'une cellule [i,j] - les bords ne sont pas cycliques.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème colonne de la grille.
 * \param g Grille : grille en jeu.
 * \return Entier : nombre de voisins vivants de la cellule. 
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);


/**
 * \fn void toggle_compte_voisins_vivants()
 * \brief Fonction activant/désactivant le mode cyclique.
 */
void toggle_compte_voisins_vivants();


/**
 * \fn void toggle_vieillissement()
 * \brief Fonction activant/désactivant le vieillissement.
 */
void toggle_vieillissement();


/**
 * \fn int periode_oscillation_courante(grille g)
 * \brief Fonction renvoyant la période d'oscillation d'une grille dans son état courant.
 *
 * \param g Grille : grille en jeu.
 * \return Entier : période d'oscillation, 0 si elle n'existe pas. 
 */
int periode_oscillation_courante(grille g);


/**
 * \fn int periode_oscillation_delai(grille g)
 * \brief Fonction renvoyant la période d'oscillation d'une grille en considérant un éventuel délai.
 *
 * \param g Grille : grille en jeu.
 * \return Entier : période d'oscillation, 0 si elle n'existe pas. 
 */
int periode_oscillation_delai(grille g);


/**
 * \fn void evolue (grille *g, grille *gc)
 * \brief Fonction faisant évoluer une grille d'un pas de temps.
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 */
void evolue (grille *g, grille *gc);

#endif
