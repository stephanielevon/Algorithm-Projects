CC = gcc
OPT = -Wall -pedantic -std=c11
OBJ = mots.o fichiers.o file.o ac.o
SRC = main
EXE = ac

all: mots fichier file automates
	$(CC) $(OPT) -o $(EXE) $(SRC).c $(OBJ)

mots: mots.c mots.h
	$(CC) $(OPT) -c mots.c

fichier: fichiers.c fichiers.h
	$(CC) $(OPT) -c fichiers.c

file: file.c file.h
	$(CC) $(OPT) -c file.c

automates: ac.c ac.h
	$(CC) $(OPT) -c ac.c

clean:
	rm -f *.o $(EXE)