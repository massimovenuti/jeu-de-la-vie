CC = gcc -g
CFLAGS = -W -Wall
IFLAGS = -I include

OPATH = obj/
BPATH = bin/
DPATH = doc/
vpath %.o obj
vpath %.c src
vpath %.h include
vpath main bin

OBJETS = $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o

#-------------------------------------------------------------------------#

main : main.o jeu.o io.o grille.o | $(BPATH)
	$(CC) $(CFLAGS) -o $@ $(OBJETS)
	mv $@ $(BPATH)

main.o : main.c jeu.h io.h grille.h
jeu.o : jeu.c jeu.h
io.o : io.c io.h
grille.o : grille.c grille.h

%.o : | $(OPATH)
	$(CC) $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

#-------------------------------------------------------------------------#

$(BPATH) :
	mkdir $@

$(DPATH) :
	mkdir $@

$(OPATH) :
	mkdir $@

#-------------------------------------------------------------------------#

doc : | $(DPATH)
	doxygen
	mv html/ $(DPATH)
	mv latex/ $(DPATH)


clean :
	rm $(OPATH)* $(BPATH)*

dist :
	tar -c --xz Doxyfile makefile include/ src/ -f VenutiMassimo-GoL-v2.2.2.tar.xz 
