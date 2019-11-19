CC = gcc -g
CFLAGS = -W -Wall
CPPFLAGS = -Iinclude -I/usr/include/cairo
LDFLAGS = -lcairo -lm -lX11

OPATH = obj/
BPATH = bin/
DPATH = doc/
vpath %.o obj
vpath %.c src
vpath %.h include
vpath main bin

OBJETS = $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o $(OPATH)io_gui.o

FCAIRO = 1

ifdef MODE
ifeq ($(MODE), TEXTE)
	FCAIRO=0
endif
endif


#-------------------------------------------------------------------------#

main : main.o jeu.o io.o io_gui.o grille.o | $(BPATH)
	$(CC) $(CFLAGS) -o $@ $(OBJETS) $(LDFLAGS)
	mv $@ $(BPATH)

main.o : main.c jeu.h io.h grille.h
jeu.o : jeu.c jeu.h
io.o : io.c io.h
io_gui.o : io_gui.c io_gui.h
grille.o : grille.c grille.h

%.o : | $(OPATH)
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -DCAIRO=$(FCAIRO)
	mv $@ $(OPATH)

#-------------------------------------------------------------------------#

$(BPATH) :
	mkdir $@

$(DPATH) :
	mkdir $@

$(OPATH) :
	mkdir $@

#-------------------------------------------------------------------------#

doxygen : | $(DPATH)
	doxygen
	mv html/ $(DPATH)
	mv latex/ $(DPATH)


clean :
	rm $(OPATH)* $(BPATH)*

dist :
	tar -c --xz Doxyfile makefile include/ src/ -f VenutiMassimo-GoL-v2.2.2.tar.xz 
