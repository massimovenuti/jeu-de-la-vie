/**
 * \file grille.h
 * \brief Fichier d'en-tête du fichier source grille.c
 * \author Massimo Venuti
 * \version 1.0
 *
 * Prototypes des fonctions et structure grille.
 *
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/**
 * \struct grille
 * 
 * Une grille est définie par un nombre de lignes, un nombre de colonnes et un tableau de tableaux de cellules.
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

/**
 * \fn static inline void set_vivante(int i, int j, grille g)
 * \brief Fonction rendant vivante la cellule [i,j] d'une grille.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème ligne de la grille
 * \param g Grille : grille en jeu.
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 * \fn static inline void set_morte(int i, int j, grille g)
 * \brief Fonction rendant morte la cellule [i,j] d'une grille.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème ligne de la grille
 * \param g Grille : grille en jeu.
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}


// teste si la cellule (i,j) de la grille g est vivante
/**
 * \fn static inline int est_vivante(int i, int j, grille g)
 * \brief Fonction testant si la cellule [i,j] d'une grille est vivante.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème ligne de la grille
 * \param g Grille : grille en jeu.
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] == 1;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

#endif
