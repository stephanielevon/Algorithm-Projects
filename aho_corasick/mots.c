#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mots.h"
#include "ac.h"


/***************************************
 *                                     *
 *             FONCTIONS               *  
 *                                     *
 **************************************/
/**************** Définir l'alphabet à partir d'une chaine de carctère *************/
char* alphabet(char* chaine_mots){
	char* alphabet = (char*)malloc(100 * sizeof(char)); // Alloue de la mémoire pour l'alphabet (100 elements dans l'alphabet)
	int p = 0;
	for (int i = 0 ; i < strlen(chaine_mots) ; i++) {
		if (isalpha(chaine_mots[i])){//!= ' ' && chaine_mots[i] != '\n' && chaine_mots[i] != '\0'){
			//printf("Caractère alphanumérique : %c\n", chaine_mots[i]);
			char* estRecense = NULL;
			estRecense = strchr(alphabet,chaine_mots[i]);
			if (estRecense == NULL){ // Si on a pas trouvé la lettre dans l'alphabet
				alphabet[p] = chaine_mots[i];
				p++; 
				//printf("%d\n", p);
			}
		}
	}
	alphabet[p] = '\0';
	//printf("Taille de l'alphabet : %d", strlen(alphabet));
	alphabet = (char*)realloc(alphabet,(p)*sizeof(char));
	//printf("%s\n", alphabet);
	return alphabet;
}


/**************** Récupèrer le nombre de mots d'une liste où chaque mot est séparé par un retour à la ligne *************/
int nbreMots(char* chaine_mots){
	int k=0;
	for (int i=0;i<strlen(chaine_mots);i++){
		if (chaine_mots[i]=='\n'){ // Incrémente un compteur à chaque retour-chariot
			k++;
		}
	}
	// printf("Nombre de mots = %d\n", k);
	return k;	
}

/****** Récupère les mots dans un tableau de (pointeur vers des) mots ******/
char** creerTableauMots(char* chaine_mots, int k){ // Autant de pointeur qu'il n'y a de mots
	// Créer un tableau de pointeur vers des mots
	char** tableau_mots = (char**)malloc(k * sizeof(char*)); // Alloue de l'espace pour un tableau qui stocke les pointeur sur les mots
	//Création du tableau pour le premier mot
	int j = 0; // Position dans le tableau de pointeur
	int p = 0; // Position dans le mot
	/* Création de la structure : je créer un tableau pour stocker le premier mot. 
	Je parcours ma chaine de mots et j'ajoute chaque lettre à mon tableau. A chaque saut de ligne je crée un nouveau tableau 
	dans lequel je stocke mon nouveau mot. */
	tableau_mots[j] = (char*)malloc(30*sizeof(char)); // Réserve de la mémoire pour un mot de 30 lettres (1er mot)
	for (int i=0;i<strlen(chaine_mots);i++){ 
    	if (chaine_mots[i] != '\n'){
    		tableau_mots[j][p] = chaine_mots[i];
    		p++; // Se place à la case suivante dans le tableau de mot
    	} else { // Si c'est un \n, Création du tableau pour le kième mot
    		tableau_mots[j] = (char*)realloc(tableau_mots[j],(p + 1)*sizeof(char)); // Ré-alloue la mémoire pour la taille réelle du mot
    		tableau_mots[j][p] = '\0'; // Indique la fin du mot
    		j++; // Se place à la case suivante dans le tableau de pointeur
    		p = 0; // Ré-initialise la position dans le mot
    		tableau_mots[j] = (char*)malloc(30*sizeof(char)); // Réserve de la mémoire pour un mot de 30 lettres 
    	}
	}
	return tableau_mots;
}

