Projet Tri par tas en langage C - Algorithmique avancée - M2.1 Bioinformatique
====================================================================================

Description du projet
-------------------------
L'objectif de ce projet est de coder le tri par tas en langage C. Le programme réalisé prend en paramètre le nom d'un fichier d'éntrée contenant un entier par ligne. Le deuxième argument qui est pris est le nom du fichier de sortie dans lequel se trouve un tableau avec les entiers triés dans l'ordre croissant. Deux étapes sont nécessaires pour la réalisation du tri par tas. Dans un premier temps, la liste d'entier doit être formatée sous forme de tas. Avec une représentation en arbre binaire complet partiellement ordonné cela signifie que chaque enfant est plus petit que son parent (s'il s'agit d'un arbre contenant l'élément maximal au sommet de l'arbre). Dans un second temps, le tas est trié par suppression successive de la racine et du ré-ordonancement de l'arbre. 


Description des fichiers 
-----------------------------
	- Makefile : permet la compilation du fichier .c
	- triTas.c, triTas.h : le fichier .c contient les fonctions suivantes
		~ nbreEntiersDansFichier - Fonction de calcul du nombre d'entiers dans le fichier a trier passé en paramètre
		~ creationTas - Fonction qui récupère les entiers du fichier passé en paramètre et les ajoute un à un au tas
		~ fichierSortie - Fonction d'écriture d'un tableau dans un fichier de sortie
		~ afficher - Fonction d'affichage d'un tableau (utilisée pour débugger le triTas.c)
		~ echanger - Fonction d'échange entre deux nombres dans un tableau
		~ ajouter - Fonction d'ajout de l'élément "x" suivi du réagencement du tableau jusqu'à ce qu'il redevienne partiellement ordonné  et forme un tas
		~ supprimer - Fonction de suppression de la racine dans le tas
		~ triTas - Fonction triTas qui réalise le tri d'un nombre d'entier formaté en tas
		Le fichier triTas.h contient les prototypes des fonctions énumérées ci-dessus. 


Usage 
----------
./triTas <nom_fichier_entree> <nom_fichier_sortie>
Exemple : ./triTas fichier_test/25_entiers.txt 25_entiers_tries.txt

OU

python randomTri.py (cf. explication ci-dessous)


Génération de fichier tests
-------------------------------------
!!!!!!!!!!!! Nécessite la librairie python "random" !!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!! Nécessite la librairie R "ggplot2" !!!!!!!!!!!!!!!!!!!

Scripts associés : 
	~ randomTri.py
	~ stat.r

Le programme de tri par tas a été testé avec différents fichiers tests, contenant un nombre variable d'entier, triés ou non dans l'ordre (croissant ou décroissant). Afin d'évaluer la rapidité de l'algorithme codé et dans le but de s'abstraire des biais introduits par les fichiers tests, un script python a été réalisé et permet de générer 1 000 tableaux de 50,100,250,500 et 1 000 entiers. Ces entiers sont compris entre 1 et 10 000. Des tableaux d'entiers triés dans l'ordre croissant et décroissant sont également générés. Chaque tableau est stocké dans un fichier temporaire avant d'être trié par le script de tri par tas. Le temps d'exécution est stocké de manière permanente dans un fichier à partir duquel un diagramme à moustache peut être réalisé en R (script R lancé à aprtir du script python). 

Si le correcteur ne souhaite pas utiliser le script randomTri.py, il peut trouver d'autres exemple de fichiers tests dans le répertoire "fichier_tests".


Evaluation de la rapidité de l'algorithme
---------------------------------------------------
Le fichier "stat.pdf" montre les boxplots pour différentes tailles de tableau, et pour des tableaux d'entiers triés ou non. Pour des tableaux allant jusqu'à 250 entiers, leur ordre dans le tableau d'entrée influence peu le temps d'exécution du programme de tri par tas (de l'ordre de 250 à 400ms). Pour des valeurs supérieures à 500 entiers, on observe qu'un tableau d'entrée avec des données dans un ordre décroissant prend plus de temps à être trié. 


Difficultés rencontrés
-----------------------------
Une des difficultés rencontrés a été de faire la distinction entre les indices du tableau dans le script.c et la taille du tableau (pas d'élément à l'indice 0). Une autre difficulté a été de générer un grand nombre de tableau pour s'affranchir des biais liés au tableau d'entrée pour évaluer l'impact des fichiers d'entrées (ordre croissant, décroissant ou random). 


Amélioration possible
----------------------------
Il pourrait être interessant de proposer à l'utilisateur de trier le tas suivant l'ordre croissant ou décroissant.
Les fonctions usuelles telles que "nombreEntierDansFichier", "fichierSortie" ou encore "afficher" pourrait être séparée du reste du code pour pouvoir être facilement réutilisées lors d'un prochain projet. 
Il existe d'autre part un algorithme permettant de prendre en compte un tableau déjà trié et optimise le tri par tas, il s'agit de l'algorithme de Smoothsort. 
