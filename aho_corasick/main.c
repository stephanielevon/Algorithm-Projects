#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mots.h"
#include "ac.h"
#include "fichiers.h"
#include "file.h"

int main(int argc, char **argv){
	// 1 - Récupération de la liste de mots et du texte (ainsi que leur taille), construction de l'alphabet
	char* chaine_mots = getFile(argv[1]); 
	char* chaine_texte = getFile(argv[2]);
	int k = nbreMots(chaine_mots); 
	int n = strlen(chaine_texte);
	char* alph = alphabet(chaine_texte); 
	// 2 - Créer la structure qui contiendra l'ensemble des mots (tableau de k pointeur avec k : le nombre de mots du langage)
	char** tableau_mots = creerTableauMots(chaine_mots, k); 
	// 3 - Récupère les informatiosn pour créer l'automate (nombre d'états maximal, création du tableau de transition)
	int nbreEtats = nombreEtats(tableau_mots, k);
	Transition* tabT = creerTransitions(nbreEtats);
	// 4 - Pré-traitement, renvoie un arbre automate
	Automate A = preAc(tabT, tableau_mots, k, alph, nbreEtats); // 6-Appel de la fonction preAc
	// 5 - Recherche, renvoie un tableau d'occurence
	printf("==============================================");
	printf("\nLa liste des mots à chercher est : \n%s", chaine_mots);
	printf("==============================================\n");
	printf("Le texte de recherche est : \n%s \n", chaine_texte);
	printf("==============================================\nRésultats : \n");
	int* tableauOccurence = ac(A, tableau_mots, k, chaine_texte, n, alph);
	for (int i=0 ; i < nbreEtats ; i++){
		if (tableauOccurence[i] != 0){
			printf("\tEtat %d : %d occurence(s)\n", i, tableauOccurence[i]);
		}
	}
	printf("==============================================\n");
	// 6 - LIbération de la mémoire allouée
	free(tableauOccurence);
	free(chaine_texte);
	free(chaine_mots);
	free(alph);
	free(tableau_mots);
	libererAutomate(A);
	return EXIT_SUCCESS;
}
