/********************
 * Type Structure   *
 *******************/
typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};


typedef struct File File;
struct File {
    Element *premier;
};


/********************
 * Prototypes       *
 *******************/
/************  Prototypes pour la gestion de file ****************/
File *initialisation();
void enfiler(File* , int );
int defiler(File* );
void afficherFile(File* );