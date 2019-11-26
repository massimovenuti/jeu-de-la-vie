/**
 * \file io_gui.c
 * \brief Gestion des entrées/sorties du jeu de la vie en mode Graphique
 * \author Massimo Venuti
 *
 * Affichage des grilles et des informations du jeu de la vie. Gestion des saisies du joueur.
 *
 */
#include "io_gui.h"

int taille_case_x(grille g) {
	return (SIZEX - MARGE_G - MARGE_D)/g.nbc;
}


int taille_case_y(grille g) {
	return (SIZEY - MARGE_H - MARGE_B)/g.nbl;
}


void affiche_grille_GUI(grille g, cairo_surface_t *cs) {
	int i,j,x,y;
	int case_x = taille_case_x(g);
	int case_y = taille_case_y(g);
	char str_age[5];
	cairo_t *cr;
	cr=cairo_create(cs);

	// Fond 
	cairo_set_source_rgb(cr, 0.12, 0.12, 0.12);
	cairo_paint(cr);

	// Taille police
	cairo_set_font_size(cr, 20);
	
	// Affiche grille
	for(i=0, y=MARGE_H ; i < g.nbl; i++, y+=case_y) {
		for(j=0, x=MARGE_G; j < g.nbc; j++, x+=case_x) {

			cairo_rectangle(cr, x, y, case_x-5, case_y-5);
			
			if (est_vivante(i,j,g)) {
				cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
				cairo_fill(cr);
				if (vieillissement) {
					cairo_set_source_rgb(cr, 1.0, 0.6, 0.3);
					cairo_move_to(cr, x + case_x/2 - 7, y + case_y/2 + 6);
					sprintf(str_age, "%d", g.cellules[i][j]);
					cairo_show_text(cr, str_age);
				}
			}
			else if (!est_viable(i,j,g)) {
				cairo_set_source_rgb(cr, 1., 0.6, 0.3);
				cairo_fill(cr);	
			}
			else {
				cairo_set_source_rgb(cr, .0, 0.0, 0.0);
				cairo_fill(cr);	
			}
		}
	}
	cairo_destroy(cr);
}


void affiche_informations_GUI(cairo_surface_t *cs, int temps, int periode) {
	char str[10];
	char str_tps[20] = "Temps : ";
	char str_osc[20] = "Période : ";
	cairo_t *cr;
	cr=cairo_create(cs);	

	// Titre "Jeu de la Vie"
	cairo_move_to(cr, INFO_X, INFO_Y);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_font_size(cr, 40);
	cairo_show_text(cr, "Jeu de la Vie");

	// Titre "Commandes"
	cairo_move_to(cr, INFO_X, INFO_Y+3*INTERLIGNE);
	cairo_set_font_size(cr, 30);
	cairo_show_text(cr, "Commandes");

	// Commandes
	cairo_set_font_size(cr, 20);
	cairo_move_to(cr, INFO_X, INFO_Y+5*INTERLIGNE);
	cairo_show_text(cr, "- clic-gauche : évoluer");
	cairo_move_to(cr, INFO_X, INFO_Y+6*INTERLIGNE);
	cairo_show_text(cr, "- clic-droit : quitter");
	cairo_move_to(cr, INFO_X, INFO_Y+7*INTERLIGNE);
	cairo_show_text(cr, "- n : nouvelle grille");
	cairo_move_to(cr, INFO_X, INFO_Y+8*INTERLIGNE);
	cairo_show_text(cr, "- c : activer/désactiver bords cyclique");
	cairo_move_to(cr, INFO_X, INFO_Y+9*INTERLIGNE);
	cairo_show_text(cr, "- v : activer/désactiver vieillissement");
	cairo_move_to(cr, INFO_X, INFO_Y+10*INTERLIGNE);
	cairo_show_text(cr, "- o : calcul période d'oscillation");

	// Temps
	cairo_set_font_size(cr, 20);
	cairo_set_source_rgb(cr, 1., 0.6, 0.3);
	cairo_move_to(cr, INFO_X, INFO_Y + 13*INTERLIGNE);
	sprintf(str, "%d", temps);
	strcat(str_tps, str);
	cairo_show_text(cr, str_tps);
	
	// Voisinage
	cairo_move_to(cr, INFO_X, INFO_Y + 14*INTERLIGNE);
	(compte_voisins_vivants == compte_voisins_vivants_cyclique) ? cairo_show_text(cr, "Cyclique : ON") : cairo_show_text(cr, "Cyclique : OFF");

	// Vieillissement
	cairo_move_to(cr, INFO_X + 5 * INTERLIGNE, INFO_Y + 14*INTERLIGNE);
	(vieillissement) ? cairo_show_text(cr, "Vieillissement : ON") : cairo_show_text(cr, "Vieillissement : OFF");

	// Oscillation
	cairo_move_to(cr, INFO_X + 5 * INTERLIGNE, INFO_Y + 13*INTERLIGNE);
	cairo_set_source_rgb(cr, 1, 0, 0);
	if (periode > 0) {
		sprintf(str, "%d", periode);
		strcat(str_osc, str);
		cairo_show_text(cr, str_osc);
	}

	cairo_destroy(cr);
}


char* nouvelle_grille_GUI(cairo_surface_t *cs, Display *dpy) {
	cairo_t *cr;
	cr=cairo_create(cs);
	XEvent e;
	KeySym k;
	char* str = malloc(TAILLE_MAX*sizeof(char));
	strcpy(str, "");

	// Fond 2
	cairo_rectangle(cr, SIZEX - MARGE_D + MARGE_G, 2 * MARGE_H , MARGE_D - MARGE_G, SIZEY - MARGE_H);
	cairo_set_source_rgb(cr, .12, 0.12, 0.12);
	cairo_fill(cr);		

	// Titre "Nouvelle grille"
	cairo_set_font_size(cr, 30);
	cairo_set_source_rgb(cr, 1.0, 0.6, 0.3);
	cairo_move_to(cr, INFO_X, INFO_Y + 3 * INTERLIGNE);
	cairo_show_text(cr, "Nouvelle grille");

	// Zone de texte
	cairo_rectangle(cr, SIZEX - MARGE_D + MARGE_G, 2 * MARGE_H + 4 *INTERLIGNE + 5 , MARGE_D - 2 *MARGE_G, INTERLIGNE+5);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_fill(cr);

	// Saisie de la nouvelle grille
	cairo_move_to(cr, SIZEX - MARGE_D + MARGE_G, 2 * MARGE_H + 5 *INTERLIGNE);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_font_size(cr, 25);
	while(1) {
		XNextEvent(dpy, &e);
		if(e.xkey.keycode == 36) { 										// '\n'
			break;
		}
		else if(e.xbutton.button == Button3) {							// clic-droit
			break;
		}
		else if ((e.xkey.keycode > 23 && e.xkey.keycode < 34)
					|| (e.xkey.keycode > 37 && e.xkey.keycode < 48)
					|| (e.xkey.keycode > 51 && e.xkey.keycode < 58)) { 	// lettre entre a et z
			k = XKeycodeToKeysym(dpy,e.xkey.keycode,0);
			strcat(str, XKeysymToString(k));
			cairo_show_text(cr,  XKeysymToString(k));
		}
		else { 															// chiffres, '/', '.' ou supp 
			switch(e.xkey.keycode) {
				case 10: {
					strcat(str, "1");
					cairo_show_text(cr, "1");
					break;
				}
				case 11: {
					strcat(str, "2");
					cairo_show_text(cr, "2");
					break;
				}
				case 12:{
					strcat(str, "3");
					cairo_show_text(cr, "3");
					break;
				}
				case 13: {
					strcat(str, "4");
					cairo_show_text(cr, "4");
					break;
				}
				case 14: {
					strcat(str, "5");
					cairo_show_text(cr, "5");
					break;
				}
				case 15: {
					strcat(str, "6");
					cairo_show_text(cr, "6");
					break;
				}
				case 16: {
					strcat(str, "7");
					cairo_show_text(cr, "7");
					break;
				}
				case 17: {
					strcat(str, "8");
					cairo_show_text(cr, "8");
					break;	
				}
				case 18: {
					strcat(str, "9");
					cairo_show_text(cr, "9");
					break;
				}
				case 19: {
					strcat(str, "0");
					cairo_show_text(cr, "0");
					break;
				}
				case 59 : {
					strcat(str, ".");
					cairo_show_text(cr, ".");
					break;					
				}
				case 60 : {
					strcat(str, "/");
					cairo_show_text(cr, "/");
					break;					
				}
				case 22 : {
					return nouvelle_grille_GUI(cs, dpy);
				}
				default:
					break;
			}
		}
	}
	cairo_destroy(cr);
	return str;
}


void debut_jeu_GUI(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy) {
	XEvent e;
	int temps = TEMPS_INIT;
	int periode = -1;
    while(1) {	
		XNextEvent(dpy, &e);
		fprintf(stdout, "%d\n", e.xbutton.button);

		if (e.type == ButtonPress) {
			if (e.xbutton.button == Button1) {
				temps++;
				evolue(g, gc);
			}
			else if(e.xbutton.button == Button3)
				break;
		}
		else if(e.type == KeyPress) {
			switch(e.xkey.keycode) {
				case 54:
				{ // c
					toggle_compte_voisins_vivants();
					break;
				}
				case 55:
				{ // v
					toggle_vieillissement();
					break;
				}
				case 57: 
				{ // n
					temps = TEMPS_INIT;
					periode = -1;
					char * chemin_grille;
					libere_grille(g);
					libere_grille(gc);
					chemin_grille = nouvelle_grille_GUI(cs, dpy);
					init_grille_from_file(chemin_grille,g);
					alloue_grille (g->nbl, g->nbc, gc);
					break;
				}
				case 32:
				{ // o
					periode = periode_oscillation_delai(*g);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		affiche_grille_GUI(*g, cs);
		affiche_informations_GUI(cs, temps, periode);
	}
}


void affichage_GUI(grille *g, grille *gc) {
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie");
	XSelectInput(dpy, win, KeyPressMask| ExposureMask | ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	debut_jeu_GUI(g,gc,cs,dpy);

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
}