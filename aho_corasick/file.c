#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/***************************************
 *                                     *
 *             FONCTIONS               *  
 *                                     *
 **************************************/
 /******************************************************
 *     Fonctions pour les files                       *  
 *****************************************************/
/********* Fonction d'initialisation d'une file ***********/
 // Initialise le premier pointeur à NULL
File *initialisation(){
	File *file = malloc(sizeof(*file));
	file->premier = NULL;
	return file;
}

/********* Fonction d'enfilage ***********/
// Ajoute un état de destination à la fin de la file
void enfiler(File *file, int nvNombre) {
	Element *nouveau = malloc(sizeof(*nouveau));
	if (file == NULL || nouveau == NULL) {
		exit(EXIT_FAILURE);
	}
	nouveau->nombre = nvNombre;
	nouveau->suivant = NULL;
	// Deux cas : la file n'est pas vide, le nouvel état est ajouté à la fin 
	if (file->premier != NULL) { 
		Element *elementActuel = file->premier;
		while (elementActuel->suivant != NULL) {
			elementActuel = elementActuel->suivant;
		}
		elementActuel->suivant = nouveau;
	} else {  // La file est vide, notre état est le premier 
		file->premier = nouveau;
	}
}

/********* Fonction de défilage ***********/
// L'état entré le premier dans la file est retiré
int defiler(File *file) {
	if (file == NULL){
		exit(EXIT_FAILURE);
	}
	int nombreDefile = 0;
	// Vérification que la file n'est pas vide
	if (file->premier != NULL){
		Element *elementDefile = file->premier;
		nombreDefile = elementDefile->nombre;
		file->premier = elementDefile->suivant;
		free(elementDefile);
	}
	return nombreDefile;
}

/********* Fonction d'affichage de la file ***********/
void afficherFile(File *file){
	if (file == NULL){
		exit(EXIT_FAILURE);
	}
	Element *element = file->premier;
	while (element != NULL){
		printf(" %d - ", element->nombre);
		element = element->suivant;
	}
	printf("\n");
}

