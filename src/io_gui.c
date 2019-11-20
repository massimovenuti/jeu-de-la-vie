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
	return (SIZEY - MARGE_HAUT - MARGE_B)/g.nbl;
}


void affiche_grille_GUI(grille g, cairo_surface_t *cs) {
	int i,j,x,y;
	int case_x = taille_case_x(g);
	int case_y = taille_case_y(g);
	char str_age[4];
	cairo_t *cr;
	cr=cairo_create(cs);

	// Fond 
	cairo_set_source_rgb(cr, 0.08, 0.08, 0.08);
	cairo_paint(cr);

	// Taille police
	cairo_set_font_size(cr, 15);
	
	// Affiche grille
	for(i=0, y=MARGE_HAUT ; i < g.nbl; i++, y+=case_y) {
		for(j=0, x=MARGE_G; j < g.nbc; j++, x+=case_x) {

			// Dessin du contour des cases
			cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
			cairo_move_to(cr, x, y);
			cairo_line_to(cr, x, y + case_y);
			cairo_move_to(cr, x, y);
			cairo_line_to(cr, x + case_x, y);
			cairo_move_to(cr, x, y + case_y);
			cairo_line_to(cr, x + case_x, y + case_y);
			cairo_move_to(cr, x + case_x, y);
			cairo_line_to(cr, x + case_x, y + case_y);
			cairo_set_line_width (cr, 2);
			cairo_stroke(cr);

			// Remplit la case 
			cairo_rectangle(cr, x, y, case_x, case_y);
			
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
	cairo_destroy(cr);
}


void affiche_informations_GUI(cairo_surface_t *cs, int temps) {
	char str[250];

	int info_x = (SIZEX - MARGE_D) + (2*MARGE_G);
	int info_y = MARGE_HAUT + 40;
	int esp = 35;
	cairo_t *cr;
	cr=cairo_create(cs);

	// Fond 2
	cairo_rectangle(cr, SIZEX - MARGE_D + MARGE_G, 0 , MARGE_D - MARGE_G, SIZEY);
	cairo_set_source_rgb(cr, .1, 0.1, 0.1);
	cairo_fill(cr);	
	// Titre "Jeu de la Vie"
	cairo_move_to(cr, info_x, info_y);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_font_size(cr, 40);
	sprintf(str, "Jeu de la Vie");
	cairo_show_text(cr, str);

	// Titre "Commandes"
	cairo_move_to(cr, info_x, info_y+2*esp);
	cairo_set_font_size(cr, 30);
	sprintf(str, "Commandes");
	cairo_show_text(cr, str);

	// Commandes
	cairo_set_font_size(cr, 20);
	cairo_move_to(cr, info_x, info_y+3*esp);
	sprintf(str, "- Clic-gauche : évoluer");
	cairo_show_text(cr, str);
	cairo_move_to(cr, info_x, info_y+4*esp);
	sprintf(str, "- Clic-droit : quitter");
	cairo_show_text(cr, str);
	cairo_move_to(cr, info_x, info_y+5*esp);
	sprintf(str, "- n : nouvelle grille");
	cairo_show_text(cr, str);
	cairo_move_to(cr, info_x, info_y+6*esp);
	sprintf(str, "- c : activer/désactiver bords cyclique");
	cairo_show_text(cr, str);
	cairo_move_to(cr, info_x, info_y+7*esp);
	sprintf(str, "- v : activer/désactiver vieillissement");
	cairo_show_text(cr, str);

	// Temps
	cairo_set_font_size(cr, 20);
	cairo_set_source_rgb(cr, 1., 0.6, 0.3);
	cairo_move_to(cr, info_x, info_y + 13*esp);
	sprintf(str, "%d", temps);
	cairo_show_text(cr, str);

	// Vieillissement
	cairo_move_to(cr, info_x + 5 * esp, info_y + 14*esp);
	(vieillissement) ? sprintf(str, "Vieillissement : ON") : sprintf(str, "Vieillissement : OFF");
	cairo_show_text(cr, str);

	// Voisinage
	cairo_move_to(cr, info_x, info_y + 14*esp);
	(compte_voisins_vivants == compte_voisins_vivants_cyclique) ? sprintf(str, "Cyclique : ON") : sprintf(str, "Cyclique : OFF");
	cairo_show_text(cr, str);	

	cairo_destroy(cr);
}


void debut_jeu_GUI(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy) {
	XEvent e;
	char extension[] = EXTENSION;
	int temps = TEMPS_INIT;
	XNextEvent(dpy, &e);

    while(e.xbutton.button != Button3) {

		if (e.xbutton.button == Button1) {
			temps++;
			evolue(g, gc);
		} 
		else if (e.xkey.keycode == 54) //54
			toggle_compte_voisins_vivants();

		else if (e.xkey.keycode == 55) 
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
		affiche_grille_GUI(*g, cs);
		affiche_informations_GUI(cs, temps);
		XNextEvent(dpy, &e);
		//fprintf(stdout, "%d\n", e.xbutton.button); 
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