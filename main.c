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

int main()
{

return 0;
}
