==================================================================================================================
Projet implémentation de l'algorithme d'Aho-Corasick en langage C - Algorithmique avancée - M2.1 Bioinformatique
==================================================================================================================

Description du projet
-------------------------
L'algorithme d'Aho-Corasick sert pour la recherche de mots dans un texte, de motifs dans une séquence, etc. Le programme prend deux arguments en entrée : la liste des mots à rechercher (cf. section "Usage") ainsi que le texte dans lequel effectuer la recherche. La liste des mots est stockée dans un tableau avant de servir pour la construction d'un automate. Cet automate, permet de ne lire qu'une seule fois chaque lettre du texte. Des états suppléants permettent de se déplacer dans l'automate, en cherchant le plus long préfixe du mot lorsque le texte diverge de la branche sur laquelle il est. Le programme renvoie le nombre d'occurence totale ainsi que les états terminaux pour lesquels il existe une occurence.


Usage 
----------
./ac <fichier_mots> <fichier_texte>
Exemple : ./ac liste_mots.txt texte.txt

!!!!!!!!! Le fichier qui contient la liste de mots doit respecter les caractéristiques suivantes : chaque mot est séparé par un retour-chariot, également présent après le dernier mot !!!!!!!!!!!
Les mots a rechercher ne doivent contenir que des caractères alphanumériques (ainsi que des espaces). 


Description des fichiers 
-----------------------------
	- Makefile : permet la compilation des scripts .c, au nombre de 4. 

	- fichiers.c, fichiers.h : le fichiers.c contient une fonction qui permet de récupérer le contenu d'un fichier et de le stocker dans une chaîne. 

	- mots.c et mots.h : le mots.c contient 3 fonctions : 
		# nbreMots : compte le nombre de mots séparés par un retour chariot dans une chaîne de caractères. Renvoie un nombre entier. 
		# alphabet : établit l'alphabet à partir d'une chaîne de caractère. Renvoie un tableau de caractères. 
		# creerTableauMots : créer un tableau contenant un nombre de mots k

	- file.c et file.h : contient les fonctions d'utilisations de file ainsi que la description de la structure file: 
		# initialisation : initialise une file qui a pour attribut un pointeur sur l'adresse du premier maillon (la valeur de l'élément de la file est de type "int" mais elle aurait très bien pu être "etat" ici, puisque c'est ce qui est stocké dans la file. J'ai préféré rester générale pour une éventuelle réutilisation des fonctions.)
		# enfiler : ajoute un élément en queue de file
		# defiler : retire le premier élément entré dans la file
		# afficherFile : permet d'afficher les valeurs de chaque mailon de la file

	- ac.c et ac.h : contient de nombreuses fonctions pour l'implémentation spécifique de l'algorithme d'Aho-Corasick ainsi que les structures nécessaires. Ces fonctions sont triés en plusieurs catégories : 
		=======================
		Pré-pré-traitement
		=======================
		# nombreEtats : calcul le nombre maximal d'état de l'automate (état initial + somme du nombre de lettre de chaque mots, dans le cas où les mots à rechercher ne sont pas des préfixes les uns des autres)

		============================================
		Fonctions pour la création de l'automate 
		============================================
		# allouerAutomate : allocation d'espace mémoire pour la création d'automate
		# creerEstTerminal : créer un tableau qui recense les états et s'ils sont terminaux (1) ou non (0)
		# initAutomate : initialise un automate qui a pour attribut : la taille de l'alphabet, le nombre d'états (effectifs), l'état initial, le ou les états terminaux stockés dans un tableau, un tableau de pointeur vers des structures transitions ainsi qu'un tableau qui permet de stocker les états suppléants. 		
		# mettreTerminal : permet de définir un état comme terminal en changeant son statut dans le tableau
		# creerEstSuppleant : créer un tableau d'entiers permettant de stocker les états suppléants. 

		============================================
		Fonctions pour la création des transitions
		============================================
		# creerTransitions : créer un tableau de pointeur vers des structures transitions (autant de pointeurs qu'il n'y a d'états)
		# ajoutTransition : ajoute une structure transition qui a pour attribut : l'état source, la lettre associée, l'état de destination ainsi qu'un pointeur vers une structure transition suivante (liste chaînée)
		# estTransition : cherche dans le tableau de transitions si une transition est définie avec en argument l'état source et la lettre. Cette fonction réalise un parcours des listes chaînées. 
		# afficherTransitions : affiche les transitions du tableau transition. 

		==========================================================
		Fonctions pour l'étape de pré-traitement et de recherche
		==========================================================
		# preAc : créer l'arbre automate de trie, en entrant chaque mot à chercher dans l'automate et en cherchant leur état suppléant (un seul par état).  
		# entrer : fonction utilisée par la fonction preAc pour entrer les mots dans l'automate
		# completer : effectue la recherche des états suppléants
		# creerTableauOccurence : créer un tableau qui permet de resencer les occurences de chaque état 
		# ac : réalise la recherche
		# libererAutomate : libère la mémoire dynamiquement allouée pour l'automate


Difficultés rencontrés
-----------------------------
Nombreuses ! 
Une des premières difficultés a été de bien comprendre la structure de l'automate, et plus particulièrement celle de liste chaînée associé au tableau de transitions. Ensuite, j'ai eu des difficultés à comprendre l'algorithme de la fonction compléter. 
Je suis finalement venue à bout de ce projet après de nombreuses heures...