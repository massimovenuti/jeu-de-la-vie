CC = gcc -g
CFLAGS = -W -Wall
CPPFLAGS = -Iinclude -I/usr/include/cairo
LDFLAGS =  -Llib -lcairo -lm -lX11 -ljeu

OPATH = obj/
BPATH = bin/
DPATH = doc/
LPATH = lib/
vpath %.o obj
vpath %.c src
vpath %.h include
vpath %.a lib

vpath main bin

OBJETS = $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o $(OPATH)io_gui.o
LIB = $(LPATH)libjeu.a

FCAIRO = 1

ifdef MODE
ifeq ($(MODE), TEXTE)
	FCAIRO=0
endif
endif


#-------------------------------------------------------------------------#

main : main.o io.o io_gui.o libjeu.a | $(BPATH) 
	$(CC) $(CFLAGS) -o $@ $(OBJETS) $(LDFLAGS)
	mv $@ $(BPATH)

main.o : main.c jeu.h io.h grille.h io_gui.h
jeu.o : jeu.c jeu.h
io.o : io.c io.h
io_gui.o : io_gui.c io_gui.h
grille.o : grille.c grille.h

%.o : | $(OPATH)
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -DCAIRO=$(FCAIRO)
	mv $@ $(OPATH)

libjeu.a : grille.o jeu.o | $(LPATH)
	ar -crv $@ $(OPATH)grille.o $(OPATH)jeu.o
	ranlib $@
	mv $@ $(LPATH)


#-------------------------------------------------------------------------#

$(BPATH):
	mkdir $@

$(DPATH):
	mkdir $@

$(OPATH):
	mkdir $@

$(LPATH):
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
