/**
 * \file io.h
 * \brief Fichier d'en-tête du fichier source io.c
 * \author Massimo Venuti
 *
 *
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <string.h>
#include "grille.h"
#include "jeu.h"

#define TAILLE_MAX 200
#define PATH "grilles/"
#define EXTENSION ".txt"


/**
 * \brief Pointeur de fonction contenant l'adresse de la fonction de calcul du voisinage d'une cellule.
 */
extern int (*compte_voisins_vivants)(int, int, grille);

/**
 * \brief Valeur contenant 1 ou 0 selon si le vieillissement des cellules est activé ou non.
 */
extern int vieillissement;

/**
 * \fn void affiche_trait (int c)
 * \brief Fonction d'affichage d'un trait horizontal.
 *
 * \param c Entier : nombre de colonnes de la grille.
 */
void affiche_trait (int c);


/**
 * \fn void affiche_ligne (int c, int* ligne)
 * \brief Fonction d'affichage d'une ligne de la grille.
 *
 * \param c Entier : nombre de colonnes de la grille.
 * \param ligne Tableau d'entiers : ligne de la grille.
 */
void affiche_ligne (int c, int* ligne);


/**
 * \fn void affiche_grille (grille g)
 * \brief Fonction d'affichage d'une grille.
 *
 * \param g Grille : grille à afficher.
 */
void affiche_grille (grille g);


/**
 * \fn void efface_grille (grille g)
 * \brief Fonction d'effacement d'une grille.
 *
 * \param g Grille : grille à effacer.
 */
void efface_grille (grille g);


/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \brief Fonction pour débuter le jeu. Saisir la touche 'q' fait quitter le jeu, 'entrée' fait évoluer le jeu d'un pas temps, 'n' fait charger une nouvelle grille (ex : saisir grille1), 'c' fait activer/désactiver le voisinage cyclique, 'v' fait activer/désactiver le vieillissement des cellules.
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 */
void debut_jeu(grille *g, grille *gc);


/**
 * \fn void affiche_temps(int temps)
 * \brief Fonction d'affichage du temps d'évolution.
 *
 * \param temps Entier : temps d'évolution.
 */
void affiche_temps(int temps);


/**
 * \fn void affiche_vieillissement()
 * \brief Fonction d'affichage de l'état du vieillissement des cellules (activé ou non).
 */
void affiche_vieillissement();


/**
 * \fn void affiche_calcul_voisinage()
 * \brief Fonction d'affichage de l'état du voisinage cyclique (activé ou non).
 */
void affiche_calcul_voisinage();


/**
 * \fn void affichage(grille *g, int temps)
 * \brief Fonction d'affichage des informations (temps, état vieillissement des celulles, état voisinage cyclique).
 *
 * \param g Adresse de la grille en jeu.
 * \param temps Entier : temps d'évolution.
 */
void affichage(grille *g, int temps);


#endif
