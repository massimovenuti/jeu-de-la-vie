/**
 * \file io.h
 * \brief Fichier d'en-tête du fichier source io.c
 * \author Massimo Venuti
 * \version 1.0
 *
 * Prototypes des fonctions.
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

extern calcul_voisins compte_voisins_vivants;
extern int vieillissement;

// affichage d'un trait horizontal
void affiche_trait (int c);

// affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
void affiche_grille (grille g);

// effacement d'une grille
void efface_grille (grille g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

void affiche_temps(int temps);

void affiche_vieillissement();

void affichage(grille *g, int temps);

void affiche_calcul_voisinage();


#endif
