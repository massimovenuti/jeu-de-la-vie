.PHONY: all doc clean

CC = gcc -g
CFLAGS = -W -Wall
IFLAGS = -I include
OPATH = obj
OBJETS = $(OPATH)/main.o $(OPATH)/jeu.o $(OPATH)/io.o $(OPATH)/grille.o

vpath %.o obj
vpath %.c src
vpath %.h include
vpath main bin

main : main.o jeu.o io.o grille.o
	$(CC) $(CFLAGS) -o $@ $(OBJETS)
	mv $@ bin/

main.o : main.c jeu.h io.h grille.h
jeu.o : jeu.c jeu.h
io.o : io.c io.h
grille.o : grille.c grille.h

%.o : 
	$(CC) $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)/

$(OPATH)/ :
	mkdir $@

doc :
	doxygen

clean :
	rm $(OPATH)/* bin/*

dist :
	tar -c --xz Doxyfile makefile src/ -f archive.tar.xz  
