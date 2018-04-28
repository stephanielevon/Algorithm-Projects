/********************
 * Type Structure   *
 *******************/
typedef int etat;

struct transition {
		etat source;
		char lettre;
		etat destination;
		struct transition* suivant; // Liste chaînée de transition pour un état source
};
typedef struct transition* Transition;

struct automate {
		int tailleAlpha;
		int nbEtats;
		etat EtatInit;
		int* EstTerminal;
		Transition* tabListeTrans; // Tableau de pointeur vers des structures transitions
		int* TabSuppleant;
};
typedef struct automate* Automate;

/********************
 * Prototypes       *
 *******************/
/************  Prototypes de pré-pré-traitement ******************/
// Calcul le nombre d'état maximal
int nombreEtats(char**, int k); 

/************  Prototypes pour la création de l'automate *********/
Automate allouerAutomate();
int* creerEstTerminal(int);
Automate initAutomate(int , int , int , Transition* , char** , int );
void mettreTerminal(int* , etat);
int* creerEstSuppleant(int );

/************  Prototypes pour la création des transitions *******/
Transition* creerTransitions(int);
void ajoutTransition(Transition* ,etat , etat, char);
int estTransition(Transition* , etat , char );
void afficherTransitions(Transition* t, int nbE);

/************  Prototypes pour l'étape de pré-traitement *********/
Automate preAc(Transition* , char** , int , char* , int );
void entrer(Automate, char*, int );
void completer(etat , Automate );
Transition* creerListeTransitions(etat , Automate );
void afficherListeTransitions(Transition* , Automate );

/************  Prototypes pour la phase de recherche *********/
int* creerTableauOccurence(int );
int* ac(Automate , char** , int , char* , int , char* );

/************  Prototypes pour la libération de la mémoire *********/
void libererAutomate(Automate );
