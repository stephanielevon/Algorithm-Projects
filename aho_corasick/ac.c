#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ac.h"
#include "file.h"

/***************************************
 *                                     *
 *             FONCTIONS               *  
 *                                     *
 **************************************/

/***************************************
 *        Pré-pré-traitement           *  
 **************************************/
/************** Calcul le nombre d'états maximal ***************************/
// Le nombre d'états maximal correspond à la somme du nombre de lettres de chaque mot ainsi que l'état initial q0
int nombreEtats(char** X, int k){ // Prend en paramètre le tableau de pointeur vers les mots et le nombre de mots
	int nbreEtat = 0;
	int i =1; // Prend en compte l'état initial
	for (i = 0 ; i < k ; i++) { // k : nombre de mots
		int tailleMot = strlen(X[i]); // X[i] : le ième mot du langage
		nbreEtat=nbreEtat+tailleMot;
	}
	return nbreEtat;
}

/******************************************************
 *     Fonctions pour la création de l'automate       *  
 *****************************************************/
 /********* Créér un automate ***********/
 // Alloue de la mémoire pour une structure automate
Automate allouerAutomate(){
	Automate a;
	a = (Automate)malloc(sizeof(struct automate)); // a est maintenant un pointeur
	return a;
}

/********* Initialise tous les états comme non terminaux ***********/
// Crée un tableau avec autant de case qu'il y a d'états. Si l'état est terminal, l'indice du tableau correspondant vaut 1, sinon 0
int* creerEstTerminal(int nbE) {
	int* tableauTerminal = (int*)malloc((nbE)*sizeof(int));
	int i = 0;
	for (i = 0 ; i < nbE ; i++) {
		tableauTerminal[i]=0;
	}
	return tableauTerminal;
}

/********* Initialise tous les états suppléant à zéro ***********/
// Crée un tableau avec l'état suppléant de chaque état de l'automate.
int* creerEstSuppleant(int nbE) {
	int* estSuppleant = (int*)malloc((nbE)*sizeof(int));
	int i = 0;
	for (i = 0 ; i < nbE ; i++) {
		estSuppleant[i]=0;
	}
	return estSuppleant;
}


/********* Initialise et retourne un automate ************************/
// L'automate est initialisé avec un seul état : l'état initial
Automate initAutomate(int tailleAlpha, int nbEtat, int EtatInit, Transition* tabT, char** X, int k) {  
	Automate A = allouerAutomate();
	A->tailleAlpha=tailleAlpha;
	A->nbEtats=nbEtat;
	A->EtatInit=EtatInit;
	A->EstTerminal=creerEstTerminal(nombreEtats(X,k));
	A->tabListeTrans=tabT;
	A->TabSuppleant=creerEstSuppleant(nombreEtats(X,k));
	return A;
}

/********* Définir la valeur 1 pour les états terminaux ***********/
void mettreTerminal(int* estT, etat e) { // On donne le numéro d'un état que l'on souhaite mettre en terminal
	estT[e]=1;
}


/******************************************************
 *     Fonctions pour la création des transitions     *  
 *****************************************************/
/********* Créer un tableau de transition initialisé à NULL ***********/
// Le tableau de transitions contient autant de case qu'il n'y a d'états. Chaque case pointe vers une tructure transition. 
Transition* creerTransitions(int nbE) {
	// Allouer l'espace qui va bien, tableau de pointeur sur des transitions
	Transition* t; 
	int i;
	t = (Transition*)malloc(nbE*sizeof(Transition));
	for (i = 0 ; i < nbE ; i++) {
		t[i] = NULL; // Initialise tous les pointeurs à NULL
	}
	return t; 
}

/********* Ajoute une transition à l'automate : état de départ, d'arrivé et lettre ***********/
// Une structure transition contient une liste chaînée de toutes les transitions qui ont la même source (ex : q0)
void ajoutTransition(Transition* tabT, etat source, etat dest, char a) { // Transition* tabT, 
	// Création d'une nouvelle transition
	Transition tr;
	tr = (Transition)malloc(sizeof(struct transition));
	tr->source=source;
	tr->destination=dest;
	tr->lettre=a;
	// La nouvelle transition est mise en tête de liste. Elle pointe vers l'ancienne tête de liste. 
	tr->suivant= tabT[source];
	// Puis la case du tableau de transition pointe vers la nouvelle transition
	tabT[source] = tr;
}

/********* Teste si une transition est définie ***********/
/* Recherche une lettre dans ma liste chaînée de transition et retourne l'état de destination s'il existe, -1 sinon */
int estTransition(Transition* tabT, etat source, char l){ 
	Transition t = tabT[source]; // NOUVEAU : évite d'écraser les transitions du tableau 
	while(t != NULL){
		if(t->lettre == l){
			return t->destination;
		} else {
			t=t->suivant;
		}
	} 
	return -1;
}

/********* Afficher le tableau des transitions ***********/
void afficherTransitions(Transition* tabT, int nbE) {
	printf("Etat source - Lettre - Destination \n");
	for (int i = 0 ; i < nbE ; i++){
		Transition t = tabT[i]; // !!!! Attention à ne pas modifier le tableau de transitions !!!!
		while(t != NULL){
			printf("%d   -   %c    -    %d    \n",t->source, t->lettre, t->destination);
			t = t->suivant; // Parcours la liste chaînée des transitions 
		} 
	}
}


/******************************************************
 *     Fonctions pour l'étape de pré-traitement       *  
 *****************************************************/
/**** Créer l'arbre automate ou arbre de trie ******/
Automate preAc(Transition* tabT, char** X, int k, char* alphabet, int nbE) {
	etat q0 = 0;
	// Création de l'automate
	Automate A = initAutomate(strlen(alphabet), 1, q0, tabT, X, k); // Le tableau estTerminale contient 24 cases initialisées à 0
	// Entrer chaque mot du langage dans l'automate
	for (int i = 0 ; i < k ; i++) {
		entrer(A, X[i], q0);
	}
	for (int i = 0 ; i < strlen(alphabet); i++){
		// Pour toutes les lettres de l'alphabet qui ne sont pas des premières de mots, créer un état de q0 vers q0 
		if (estTransition(A->tabListeTrans, q0, alphabet[i]) == -1){ 
			ajoutTransition(tabT, q0, q0, alphabet[i]);
		}
	}
	ajoutTransition(tabT, q0, q0, ' '); // Ajout d'une transition pour les espaces	 
	// Completer l'arbre automate avec des retours vers les plus longs prefixes
	completer(q0, A);
	return A;
}


/*************** Entre chaque mot dans l'arbre ***************/
void entrer(Automate A, char* x, int e) {
	int i = 0;
	int tailleMot = strlen(x);
	// Entre dans la première boucle si un préfixe du mot à entrer est déjà défini dans l'arbre
	while (i < tailleMot && estTransition(A->tabListeTrans, e, x[i]) != -1) {
		// "Aller" à cet état, le nouvel état est celui de destination 
		// On continue dans l'arbre jusqu'au plus grand préfixe du nouveau mot à entrer
		e = estTransition(A->tabListeTrans, e, x[i]);
		i++;
	}
	// Entre dans cette boucle pour créer de nouveaux états (automate ne contient nitialement qu'un seu état)
	while (i < tailleMot) {
		int s = A->nbEtats; // Création d'un état s
		A->nbEtats = s+1; // Agrandi le nombre d'états au fur et à mesure
		ajoutTransition(A->tabListeTrans, e, s, x[i]);
		e = s;
		i++;
	}
	mettreTerminal(A->EstTerminal, e); // A la fin du mot, mettre l'état en terminal dans le tableau estT
}


/*********** Compléter l'arbre automate ***********/
void completer(etat e, Automate A) { // Appelé avec l'état initial 
	File *f = initialisation(); // Création d'une file vide
	Transition* listeTransition = creerListeTransitions(e, A); // printf(" Ma liste de transition pour l'état %d est : \n", e);
	int i = 0;
	while (listeTransition[i] != NULL){
		etat p = listeTransition[i]->destination; // p : état de destination de la première transition de la liste
		enfiler(f, p); // Premier élement de la liste devient le premier élément de la file
		A->TabSuppleant[p]=e; // printf("La case %d du tableau de suppléance vaut : %d", p, e);
		i++;
	// afficherFile(f);
	}
	while (f->premier != NULL){
		Element *r = f->premier; // Récupère r, le premier élément de ma file, AVANT de défiler (r est un maillon : un nombre + un pointeur)
		Transition* listeTransition = creerListeTransitions(r->nombre, A); // Récupère les transitions partant du premier état de la file
		defiler(f); 
		int j = 0;
		while (listeTransition[j] != NULL) { // Pour chaque état de destination de ma liste, l'ajouter à la file
			int r = listeTransition[j]->source;
			char a = listeTransition[j]->lettre;
			etat p = listeTransition[j]->destination;
			enfiler(f,p);
			j++; 
			int s = A->TabSuppleant[r]; //s <-sup(r); état suppléant de l'état source
			while (estTransition(A->tabListeTrans, s, a) == -1) { // Parcours pour trouver le plus long suffixe
				s = A->TabSuppleant[s]; // s<-sup(s)
			}
			int sup = estTransition(A->tabListeTrans, s, a);
			A->TabSuppleant[p]=sup; //sup(p)<-transition(s,a);
			if (A->EstTerminal[sup] == 1){ // Si l'état suppléant est terminal alors l'état "père" le devient également
				mettreTerminal(A->EstTerminal,p);
			}
		}
	}
}

/****************** Créer une liste de transition **************************/
Transition* creerListeTransitions(etat e, Automate A){
	Transition* tableauListe = (Transition*)malloc((A->nbEtats)*sizeof(Transition));
	for (int i = 0 ; i < A->nbEtats ; i++) {
		tableauListe[i]= NULL;
	}
	Transition t = A->tabListeTrans[e]; // t est ma liste chaînée de transition pour l'état e
	// printf("\n Etat source : %d \n", t->source);
	int i = 0;
	while(t != NULL){ // Il existe une transition pour l'état concerné
		if(t->source != t->destination){ // Si la source est différente de la destination
			tableauListe[i] = t; // La ième case de la liste tableauListe pointe sur t 
			i++;
			t=t->suivant;
		} else {
			t=t->suivant;
		}
	}
	return tableauListe;
}


/****************** Affiche une liste de transition **************************/
void afficherListeTransitions(Transition* listeTransition, Automate A){
	printf("Etat source - Lettre - Destination \n");
	for (int i = 0 ; i < A->nbEtats ; i++){
		Transition t = listeTransition[i]; // !!!! Attention à ne pas modifier le tableau de transitions !!!!
		if (t != NULL){
			printf("%d   -   %c    -    %d     \n",t->source, t->lettre, t->destination);
		}
	}	
}

/******************************************************
 *     Fonctions pour la phase de recherche           *  
 *****************************************************/
/********* Créer un tableau d'occurence ***********/
// Crée un tableau avec pour chaque état son nombre d'occurence, initilisé à zéro
int* creerTableauOccurence(int nbE) {
	int* tabOccurence = (int*)malloc((nbE)*sizeof(int));
	int i = 0;
	for (i = 0 ; i < nbE ; i++) {
		tabOccurence[i]=0;
	}
	return tabOccurence;
}

/********* Aho-Corasick ***********/
int* ac(Automate A, char** X, int k, char* y, int n, char* alphabet) {
	int nbE = A->nbEtats;
	// afficherTransitions(A->tabListeTrans, A->nbEtats);
	int occ = 0;
	int e = A->EtatInit;
	int* tabOccurence = creerTableauOccurence(nbE);
	for (int j = 0 ; j < n ; j++) { // n : longueur de la chaine de texte, pour chaque lettre
		while (estTransition(A->tabListeTrans, e, y[j]) == -1) {
			e = A->TabSuppleant[e];
		}
		e = estTransition(A->tabListeTrans, e, y[j]);
		if (A->EstTerminal[e] != 0){
			occ++;
			tabOccurence[e]++;
		}
	}
	printf("Nombre d'occurence(s) : %d\n", occ);
	return tabOccurence;
}

/********* Libère la mémoire allouée pour l'automate ***********/
void libererAutomate(Automate A) {
	free(A->EstTerminal);
	free(A->TabSuppleant);
	free(A->tabListeTrans);
	free(A);
}
