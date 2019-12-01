/**
 * \file io.h
 * \brief Fichier d'en-tête du fichier source io.c
 * \author Massimo Venuti
 *
 *
 */
#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <string.h>
#include "grille.h"
#include "jeu.h"

#define TAILLE_MAX 200
#define PERIODE_INIT -1

extern int (*compte_voisins_vivants)(int, int, grille);

extern int vieillissement;


/**
 * \fn void affiche_trait (int c)
 * \brief Fonction d'affichage d'un trait horizontal en mode Texte.
 *
 * \param c Entier : nombre de colonnes de la grille.
 */
void affiche_trait (int c);


/**
 * \fn void affiche_ligne (int c, int* ligne)
 * \brief Fonction d'affichage d'une ligne de la grille en mode Texte.
 *
 * \param c Entier : nombre de colonnes de la grille.
 * \param ligne Tableau d'entiers : ligne de la grille.
 */
void affiche_ligne (int c, int* ligne);


/**
 * \fn void affiche_grille (grille g)
 * \brief Fonction d'affichage d'une grille en mode Texte.
 *
 * \param g Grille : grille à afficher.
 */
void affiche_grille (grille g);


/**
 * \fn void efface_grille (grille g)
 * \brief Fonction d'effacement d'une grille en mode Texte.
 *
 * \param g Grille : grille à effacer.
 */
void efface_grille (grille g);


/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \brief Fonction pour débuter le jeu en mode Texte.
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 */
void debut_jeu(grille *g, grille *gc);


/**
 * \fn void affiche_temps(int temps)
 * \brief Fonction d'affichage du temps d'évolution courant en mode Texte.
 *
 * \param temps Entier : temps d'évolution courant.
 */
void affiche_temps(int temps);


/**
 * \fn void affiche_oscillation(int periode)
 * \brief Fonction d'affichage de la période d'évolution d'une grille en mode Texte.
 *
 * \param periode Entier : période d'oscillation de la grille courante.
 */
void affiche_oscillation(int periode);


/**
 * \fn void affiche_vieillissement()
 * \brief Fonction d'affichage de l'état du vieillissement (ON/OFF) en mode Texte.
 */
void affiche_vieillissement();


/**
 * \fn void affiche_calcul_voisinage()
 * \brief Fonction d'affichage de l'état du voisinage cyclique (ON/OFF) en mode Texte.
 */
void affiche_calcul_voisinage();


/**
 * \fn void affichage(grille *g, int temps)
 * \brief Fonction d'affichage des informations (temps, vieillissement, cyclique, oscillation) en mode Texte.
 *
 * \param g Adresse de la grille en jeu.
 * \param temps Entier : temps d'évolution courant.
 * \param periode Entier : période d'oscillation de la grille g.
 */
void affichage(grille *g, int temps, int periode);

#endif
