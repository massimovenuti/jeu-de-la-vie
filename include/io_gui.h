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

extern int (*compte_voisins_vivants)(int, int, grille);

extern int vieillissement;


/**
 * \fn int taille_case_x(grille g)
 * \brief Fonction renvoyant la taile des cases d'une grille selon x pour s'adapter à l'affichage.
 *
 * \param g Grille : grille en jeu.
 * \return Entier : taille selon x des cases de la grille g.
 */
int taille_case_x(grille g);


/**
 * \fn int taille_case_y(grille g);
 * \brief Fonction renvoyant la taile des cases d'une grille selon y pour s'adapter à l'affichage.
 *
 * \param g Grille : grille en jeu.
 * \return Entier : taille selon y des cases de la grille g.
 */
int taille_case_y(grille g);


/**
 * \fn void affiche_grille_GUI (grille g, cairo_surface_t *cs)
 * \brief Fonction d'affichage d'une grille en mode Graphique.
 *
 * \param g Grille : grille à afficher.
 * \param cs Adresse de la surface cairo courante.
 */
void affiche_grille_GUI (grille g, cairo_surface_t *cs);


/**
 * \fn void affiche_informations_GUI(cairo_surface_t *cs, int temps, int periode)
 * \brief Fonction d'affichage des informations (temps, oscillation, vieillissement, cyclique) en mode Graphique.
 *
 * \param cs Adresse de la surface cairo courante.
 * \param temps Entier : temps d'évolution courant.
 * \param periode Entier : période d'oscillation de la grille en jeu.
 */
void affiche_informations_GUI(cairo_surface_t *cs, int temps, int periode);


/**
 * \fn void affichage_GUI (grille *g, grille *gc)
 * \brief Fonction d'affichage d'une partie en mode Graphique.
 *
 * \param g Adresse de la grille en jeu.
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 */
void affichage_GUI (grille *g, grille *gc);


/**
 * \fn void debut_jeu_GUI(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy)
 * \brief Fonction pour débuter le jeu en mode Graphique.
 *
 * \param gc Adresse de la grille servant de copie temporaire pour le programme.
 * \param g Adresse de la grille en jeu.
 * \param cs Adresse de la surface cairo courante.
 * \param dpy Adresse du display courant.
 */
void debut_jeu_GUI(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy);

#endif