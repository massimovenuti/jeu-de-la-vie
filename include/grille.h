/**
 * \file grille.h
 * \brief Fichier d'en-tête du fichier source grille.c
 * \author Massimo Venuti
 *
 *
 */
#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/**
 * \struct grille
 * Une grille est définie par un nombre de lignes, un nombre de colonnes et un tableau de tableaux de cellules.
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;


/**
 * \fn void alloue_grille (int l, int c, grille* g)
 * \brief Fonction d'allocation d'une grille de taille l*c, initialise toutes les cellules à mortes.
 *
 * \param l Entier : nombre de lignes.
 * \param c Entier : nombre de colonnes.
 * \param g Adresse de la grille à allouer.
 */
void alloue_grille (int l, int c, grille* g);


/**
 * \fn void libere_grille (grille* g)
 * \brief Fonction de libération d'une grille.
 *
 * \param g Adresse de la grille à libérer.
 */
void libere_grille (grille* g);


/**
 * \fn void init_grille_from_file (char * filename, grille* g)
 * \brief Fonction d'allocation et d'initalisation d'une grille à partir d'un fichier.
 *
 * \param filename Chaine de caractères : nom du fichier dans lequel se trouve la configuration initiale de la grille.
 * \param g Adresse de la grille à initialiser.
 */
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

/**
 * \fn static inline void set_nonViable(int i, int j, grille g)
 * \brief Fonction rendant non viable la cellule [i,j] d'une grille.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème ligne de la grille
 * \param g Grille : grille en jeu.
 */
static inline void set_nonViable(int i, int j, grille g){g.cellules[i][j] = -1;}

/**
 * \fn static inline int est_vivante(int i, int j, grille g)
 * \brief Fonction testant si la cellule [i,j] d'une grille est vivante.
 *
 * \param i Entier : i-ème ligne de la grille.
 * \param j Entier : j-ème ligne de la grille
 * \param g Grille : grille en jeu.
 */
static inline int est_vivante(int i, int j, grille g) {return g.cellules[i][j] > 0;}

static inline int est_viable(int i, int j, grille g) {return g.cellules[i][j] != -1;}


/**
 * \fn void copie_grille (grille gs, grille gd)
 * \brief Fonction de copie d'une grille (sans allocation).
 *
 * \param gs Grille : grille à copier (source).
 * \param gd Grille : grille à modifier (destination).
 */
void copie_grille (grille gs, grille gd);

#endif
