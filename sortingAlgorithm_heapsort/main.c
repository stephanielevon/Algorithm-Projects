#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "triTas.h"

int main(int argc, char *argv[]){
	if (argc != 3) {
		printf("Mauvais nombre d'arguments :\n./triTas <fichier_test> <fichier_sortie>\n");
		return EXIT_FAILURE;
	}
	int tailleTableau = nbreEntiersDansFichier(argv[1]);
	//printf("%d\n", tailleTableau);

	int* tableauTas = creationTas(argv[1], tailleTableau);
	//afficher(tableauTas, tailleTableau);
	tableauTas = triTas(tableauTas, tailleTableau);
	//afficher(tableauTas, tailleTableau);
	fichierSortie(argv[2], tableauTas, tailleTableau);
	printf("%lu\n", clock());
    return EXIT_SUCCESS;
}
