#include <stdio.h> //sprintf
#include <stdlib.h>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <string.h>  //strlen - strstr


typedef struct Element Element;
struct Element{
  char elem[10];
  Element *suivant;
};

typedef struct Liste Liste;
struct Liste{
  Element *premier;
}; //cette structure contient un pointeur vers le premier element de la liste
//pour trouver les element à venir il suffit d'utiliser le pointeur suivant

// 1- Initialisation de la Liste
Liste *initialisation(){
  Liste *liste = malloc(sizeof(liste)); //allocation de la structure de contrôle
                                        //taille à allouée est calculer automatiquement avec sizeof
  Element *element = malloc(sizeof(*element));//idem allocation de la mémoire pour le 1er Element
  if(liste == NULL || element == NULL){//On vérifie si les allocations dynamiques en fonctionner
    exit(EXIT_FAILURE); //En cas d'erreur en arrête le programme en faisant appel à exit
  }
  //Si tout c'est bien passer on définit les valeurs de notre premier élément
  strcat(element-> elem, "VmSize");//valeur du premier pointeur
  element->suivant = NULL;//le premier element est aussi le dernier pour le moment
  liste->premier = element;

  return liste;
};

// 2- Ajout d'un element à la Liste (au début)
void insertion(Liste *liste, char *nvElement){
  /*Creation du nouvel élément*/
  Element *nouveau = malloc(sizeof(*nouveau));
  if(liste == NULL || nouveau == NULL){//On vérifie si les allocations dynamiques en fonctionner
    exit(EXIT_FAILURE); //En cas d'erreur en arrête le programme en faisant appel à exit
  }
  strcat(nouveau->elem, nvElement);

  /*Insertion de l'élément au début de la liste*/
  nouveau->suivant = liste->premier;
  liste->premier = nouveau;
};

// 3- Suppression d'un element d'une Liste (premier element)

void suppression(Liste *liste){
  if(liste == NULL){
    exit(EXIT_FAILURE);
  }
  if(liste->premier != NULL){
    Element *aSupprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    free(aSupprimer);
  }
};

int main()
{

return 0;
}
