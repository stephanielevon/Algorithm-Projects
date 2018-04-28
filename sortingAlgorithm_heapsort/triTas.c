#include <stdio.h>
#include <stdlib.h>
#include "triTas.h"

/***************************************
 *                                     *
 *             FONCTIONS               *  
 *                                     *
 **************************************/

 /***********************************************************************************
 * Fonction de calcul du nombre d'entiers dans le fichier a trier passé en paramètre
 ***********************************************************************************/
int nbreEntiersDansFichier(char* nomFichier){
	FILE* fichier = NULL; 
	// Ouverture du fichier en mode "lecture"
    fichier = fopen(nomFichier, "r");
    // Si le fichier a pu être ouvert, exécuter le code sinon afficher un message d'erreur
    if (fichier != NULL){
    	int nbreEntier = 0;
	    char buff[255]; // Alloue de la mémoire pour une chaine de 255 caractères (on ne connait pas le nombre de caractère de la ligne)
        while (fgets(buff, 255, (FILE*)fichier) != NULL){ // Tant qu'il y a des caractères à lire dans le fichier 
            if (buff[0] != '\n'){ // Si le premier caractère n'est pas un saut de ligne = si la ligne n'est pas vide
                nbreEntier++; // Incrémentation du nombre d'entier
            } 
        }
    	fclose(fichier);
    	return nbreEntier;
    } else {
    	printf("Imposible d'ouvrir le fichier %s\n", nomFichier);
    	return -1;
    }
}


/***************************************************************************************************
 * Fonction qui récupère les entiers du fichier passé en paramètre et les ajoute un à un au tas
***************************************************************************************************/
int* creationTas(char *nomFichier, int tailleTableau){
	FILE* fichier = NULL; 
	// Ouvertue du fichier pour lecture
    fichier = fopen(nomFichier, "r");
    tailleTableau = nbreEntiersDansFichier(nomFichier);
    // Si le fichier a pu être ouvert en mode lecture 
    if (fichier != NULL){
        int i = 0;
        int* tableauEntier = (int*)malloc(tailleTableau*sizeof(int));
        fichier = fopen(nomFichier, "r");
	    char buff[255];
        while (fgets(buff, 255, (FILE*)fichier) != NULL){ // Tant qu'il y a des caractères à lire dans le fichier 
            if (buff[0] != '\n'){ // Si le premier caractère n'est pas un saut de ligne = si la ligne n'est pas vide
               	// Stocke chaque entier dans la variable "x" après l'avoir converti depuis une chaine de caractère en entier
            	int x = atoi(buff);
            	// Ajoute le nouvel entier au tas en respectant la condition : partiellement ordonné
            	tableauEntier = ajouter(tableauEntier, i, x);
            	i++;
            }
        }
	    return tableauEntier;
    } else {
    	// Affiche un message d'ereur si le fichier n'a pas pu être ouvert
    	printf("Imposible d'ouvrir le fichier %s\n", nomFichier);
    	return NULL; // Car on retourne un pointeur 
    }
}

 /***************************************************************************************************
 * Fonction d'écriture d'un tableau dans un fichier de sortie
 ***************************************************************************************************/
void fichierSortie(char* fichierSor, int* tableau,int tailleTableau){
	FILE* fichier = NULL;
	// Ouverture du fichier pour écriture
	fichier = fopen(fichierSor, "w");
	if (fichier != NULL){
		int i = 1;
		for (i = 1 ; i <= tailleTableau ; i++){
			fprintf(fichier, "%d\n", tableau[i]);
		}
		fclose(fichier);
	} else {
		printf("Imposible de générer le fichier de sortie %s\n", fichierSor);
	}
}

/**************************************
 * Fonction d'affichage d'un tableau
**************************************/
void afficher(int *T, int tailleTableau){
	printf("----------------------------------------------------\n |");
	for (int i = 1 ; i <= tailleTableau ; i++) {
		printf(" %d |", T[i]);
	}
	printf("\n-----------------------------------------------------\n");
}


/**************************************************************************************************************
 * Fonction d'échange entre deux nombres dans un tableau (i et k sont les indices des nombres à échanger)
 *************************************************************************************************************/
void echanger(int *T, int i, int k){
	int tmp = T[i];
	T[i] = T[k];
	T[k] = tmp;
	return;
}

/*********************************************************************************************************************
 * Fonction d'ajout de l'élément "x" suivi du réagencement du tableau jusqu'à ce qu'il redevienne partiellement ordonné 
 et forme un tas (on part des feuilles pour remonter à la racine)
 ********************************************************************************************************************/
int* ajouter(int *T, int tailleTableau, int x){
	int j;
	tailleTableau = tailleTableau + 1;
	j = tailleTableau;
	T[tailleTableau] = x; // Ajout du nouvel élément en fin de tas (en position de dernière feuille)
	while ((j > 1) && (T[j] > T[j/2])){ // Jusqu'à ce que l'on arrive à la racine (cas d'indice 1) et que le fils est supérieur à son père
		echanger(T, j, j/2); // Echange des deux éléments du tableau
		j = j/2; // Permet de remonter dans l'arbre et réalise la même évaluation pour le noeud supérieur
	}
	return T;
}

/*********************************************************************************************************************
 * Fonction de suppression de la racine dans le tas (ou stockage à la place de la dernière feuille)
 ********************************************************************************************************************/
void supprimer(int *T, int tailleTableau){
	int i;
	int j = 1;
	echanger(T, 1, tailleTableau); // La racine prend la valeur de la dernière feuille
	//T[1] = T[tailleTableau]; 
	tailleTableau = tailleTableau - 1;
	while (j <= (tailleTableau/2)){ 
		/* 
		* 1ère étape : "j" étant le père, recherche du fils le plus grand. Affectation de l'indice de ce dernier à la valeur "i"
		*/
		// S'il n'y a pas de fils droit ou que le fils gauche est supérieur au fils droit
		if (((2*j) == tailleTableau) || (T[2*j] > T[2*j+1])){ 
			i = 2*j; // Indice du fils gauche affecté à "i"
		} else {
			// Sinon : le fils droit est supérieur au fils gauche
			i = 2*j+1; // Indice du fils droit affecté à "i"
		}
		/* 
		* 2ème étape : comparaison de la racine avec son fils le plus grand
		*/
		if (T[j] < T[i]){ // Si le père est inférieur à son plus grand fils, il y a échange
			echanger(T, j, i);
			j = i;
		} else {
			break; // Sortir de la fonction supprimer
		}
	}
	return;
}



/******************************************************************************
 * Fonction triTas qui réalise le tri d'un nombre d'entier formaté en tas
******************************************************************************/
int* triTas(int* T, int tailleTableau){
	int k = tailleTableau;
	while (k > 1){
		supprimer(T, k);
		k = k - 1;
	}
	return T;
}
