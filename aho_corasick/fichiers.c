#include <stdio.h>
#include <stdlib.h>

/********** Fonction de lecture de fichier ***********/
char* getFile(char* f) { //Paramètre d'entrée : pointeur vers le nom du fichier 
  FILE *fichier;//Pointeur retourne vers un fichier

  if ((fichier = fopen(f, "r")) == NULL) { //Fichier donné en paramètre n'existe pas ou n'est pas accessible ou on a pas les droit ="r", renvoie NULL
    fprintf(stderr, "Impossible d'ouvrir le fichier %s\n", f); //fprintf = file printf, écrit sur une autres sortie que la sortie standard, stderr pour l'erreur
    exit(EXIT_FAILURE); // Arrêt avec une erreur
  }
  fseek(fichier, 0, SEEK_END); // Seek=atteindre. Le pointeur se déplace à la fin du fichier (se déplacer de 0 octets, on s eplace à la fin du fichier)
  long taille = ftell(fichier); // Prend le pointeur et lui demande où il se situe à la fin du fichier. Valeur retournée de type "long"
  rewind(fichier); // Reviens au début
 
  char* chaine = (char*)malloc(taille*sizeof(char)); // Alloue de la mémoire pour la chaine de caractère entière présente ds le fichier
  if (chaine == NULL) { // Si renvoie qlq chose qui ent nulle, pb d'alloc mémoire
    fprintf(stderr, "Problème allocation mémoire...\n");
    exit(EXIT_FAILURE);
  }
  fread(chaine , taille, 1, fichier); // Où mettre le contenu du fichier, taille du bloc à lire (taille du fichier), combien de fois, où le lire. 
  // Renvoie un entier : nbre d'octets réussi à lire
  fclose(fichier);

  return chaine;
}
