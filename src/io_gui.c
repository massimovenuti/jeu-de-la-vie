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
	return (SIZEX-2*MARGE_COTE)/g.nbc;
}

int taille_case_y(grille g) {
	return (SIZEY-MARGE_HAUT-MARGE_COTE)/g.nbl;
}


void affiche_grille_GUI(grille g, cairo_surface_t *cs, int temps) {
	int i,j,x,y;
	int case_x = taille_case_x(g);
	int case_y = taille_case_y(g);
	char str_age[4];
	char str_temps[250];
	char str_vieillissement[250];
	char str_voisinage[250];
	cairo_t *cr;
	cr=cairo_create(cs);

	// Fond 
	cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
	cairo_paint(cr);

	// Taille police
	cairo_set_font_size(cr, 13);
	
	// Affiche grille
	for(i=0, y=MARGE_HAUT ; i < g.nbl; i++, y+=case_y) {
		for(j=0, x=MARGE_COTE; j < g.nbc; j++, x+=case_x) {

			cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
			// Dessin du contour des cases
			cairo_move_to(cr, x, y);
			cairo_line_to(cr, x, y + case_y);
    
			cairo_move_to(cr, x, y);
			cairo_line_to(cr, x + case_x, y);

			cairo_move_to(cr, x, y + case_y);
			cairo_line_to(cr, x + case_x, y + case_y);

			cairo_move_to(cr, x + case_x, y);
			cairo_line_to(cr, x + case_x, y + case_y);

			cairo_set_line_width (cr, 1);
			cairo_stroke(cr);

			cairo_rectangle(cr, x, y, case_x, case_y);

			// Remplit la case avec les bonnes informations
			if (est_vivante(i,j,g)) {
				cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
				cairo_fill(cr);

				if (vieillissement) {
					cairo_set_source_rgb(cr, 1.0, 0.6, 0.3);
					cairo_move_to(cr, x + case_x/2, y + case_y/2);
					sprintf(str_age, "%d", g.cellules[i][j]);
					cairo_show_text(cr, str_age);
				}
			}
			else if (!est_viable(i,j,g)) {
				cairo_set_source_rgb(cr, 1., 0.6, 0.3);
				cairo_fill(cr);	
			}
		}
	}


	// Affichage des informations (temps, voisinage, vieillissement)
	cairo_set_font_size(cr, 20);
	cairo_set_source_rgb(cr, 11., 0.6, 0.3);

	// Temps
	cairo_move_to(cr, MARGE_COTE, MARGE_HAUT-30);
	sprintf(str_temps, "%d", temps);
	cairo_show_text(cr, str_temps);

	// Vieillissement
	cairo_move_to(cr, MARGE_COTE+150, MARGE_HAUT-30);
	(vieillissement) ? sprintf(str_vieillissement, "Vieillissement : activé") : sprintf(str_vieillissement, "Vieillissement : désactivé");
	cairo_show_text(cr, str_vieillissement);

	// Voisinage
	cairo_move_to(cr, MARGE_COTE+450, MARGE_HAUT-30);
	if (compte_voisins_vivants == compte_voisins_vivants_cyclique) 
		sprintf(str_voisinage, "Voisinage cyclique : activé");
	else 
		sprintf(str_voisinage, "Voisinage cyclique : désactivé");
	cairo_show_text(cr, str_voisinage);

	cairo_destroy(cr);
}


void debut_jeu_GUI(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy, XEvent e) {
	char extension[] = EXTENSION;
	int temps = TEMPS_INIT;
    while(1) {

		XNextEvent(dpy, &e);
		if(e.type==ButtonPress) {
			if (e.xbutton.button == Button1) {
				temps++;
				evolue(g, gc);
			}

			else if (e.xbutton.button == Button3)
				break;
		}

		else if (e.type==KeyPress) {
			if (e.xkey.keycode == 54)               // 54 = c
                toggle_compte_voisins_vivants();

			else if (e.xkey.keycode == 55)          // 55 = v
				toggle_vieillissement();

			else if (e.xkey.keycode == 57) {        // 57 = n
				char nomFichier[TAILLE_MAX];
				char path[TAILLE_MAX] = PATH;

				libere_grille(g);
				libere_grille(gc);

				printf("Veuillez saisir le nom d'une nouvelle grille : ");
				scanf("%s", nomFichier);
				while(getchar() != '\n'); 
				strcat(strcat(path, nomFichier), extension);

				temps = 0;
				init_grille_from_file(path,g);
				alloue_grille (g->nbl, g->nbc, gc);

                cairo_xlib_surface_set_size(cs, SIZEX, SIZEY);
			}
		}
		affiche_grille_GUI(*g, cs, temps);
	}
}


void affichage_GUI(grille *g, grille *gc) {
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
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
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	debut_jeu_GUI(g,gc,cs,dpy,e);

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
}