/**
 * \file io_gui.h
 * \brief Fichier d'en-tête du fichier source io_gui.c
 * \author Massimo Venuti
 *
 *
 */
#ifndef __IO_GUI_H__
#define __IO_GUI_H__
#define TAILLE_MAX 200

#define SIZEX 1300
#define SIZEY 650

#define MARGE_H 50
#define MARGE_G 50
#define MARGE_B 50
#define MARGE_D 500

#define INFO_X ((SIZEX - MARGE_D) + (MARGE_G))
#define INFO_Y (MARGE_H + 40)
#define INTERLIGNE 35

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "grille.h"
#include "jeu.h"


/**
 * \brief Pointeur de fonction contenant l'adresse de la fonction de calcul du voisinage d'une cellule.
 */
extern int (*compte_voisins_vivants)(int, int, grille);

/**
 * \brief Valeur contenant 1 ou 0 selon si le vieillissement des cellules est activé ou non.
 */
extern int vieillissement;

int taille_case_x(grille g);

int taille_case_y(grille g);


/**
 * \fn void affiche_grille_GUI(grille g)
 * \brief Fonction d'affichage d'une grille en mode Graphique.
 *
 * \param g Grille : grille à afficher.
 */
void affiche_grille_GUI (grille g, cairo_surface_t *cs);

void affiche_informations_GUI(cairo_surface_t *cs, int temps);


/**
 * \fn void affichage_GUI(grille g)
 * \brief Fonction d'affichage d'une partie en mode Graphique.
 *
 * \param g Grille : grille à afficher.
 */
void affichage_GUI (grille *g, grille *gc);

char* nouvelle_grille_GUI(cairo_surface_t *cs, Display *dpy);

/**
 * \fn void debut_jeu(grille *g, grille *gc)
 * \brief Fonction pour débuter le jeu en mode Graphique.
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 */
void debut_jeu_GUI(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy);

#endif