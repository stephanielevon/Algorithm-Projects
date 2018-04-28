CC = gcc
OPT = -Wall -pedantic -std=c11
OBJ = triTas.o 
SRC = main
EXE = triTas

all: triTas
	$(CC) $(OPT) -o $(EXE) $(SRC).c $(OBJ)

triTas: triTas.c triTas.h
	$(CC) $(OPT) -c triTas.c

clean:
	rm -f *.o $(EXE)