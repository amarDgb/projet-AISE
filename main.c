#include <stdio.h>
#include <string.h>
#include <proc/readproc.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char** argv)
{
 // fillarg used for cmdline
 // fillstat used for cmd
 PROCTAB* proc = openproc(PROC_FILLARG | PROC_FILLSTAT);

 proc_t proc_info;

 // zero out the allocated proc_info memory
 memset(&proc_info, 0, sizeof(proc_info));
printf("PID \t PPID       Etat \t  command \t\n\n");
 while (readproc(proc, &proc_info) != NULL) {
  printf("%-10d %-10d", proc_info.tid, proc_info.ppid);


  printf("    %c \t", proc_info.state);

  if (proc_info.cmdline != NULL) {
   // print full cmd line if available
   printf("%s\n", *proc_info.cmdline);
  } else {
   // if no cmd line use executable filename
   printf("[%s]\n", proc_info.cmd);
  }

}


 closeproc(proc);

 return 0;
}

//#include <stdio.h> //sprintf
//#include <stdlib.h>
//#include <dirent.h>
//#include <fnmatch.h>
//#include <sys/types.h>
//#include <string.h>  //strlen - strstr

//#define BUFSZ 1024

//typedef struct Element Element;
//struct Element{
//  char elem[10];
//  Element *suivant;
//};
//
//typedef struct Liste Liste;
//struct Liste{
//  Element *premier;
//}; //cette structure contient un pointeur vers le premier element de la liste
//pour trouver les element à venir il suffit d'utiliser le pointeur suivant
//
// 1- Initialisation de la Liste
//Liste *initialisation(){
//  Liste *liste = malloc(sizeof(liste)); //allocation de la structure de contrôle
//                                        //taille à allouée est calculer automatiquement avec sizeof
//  Element *element = malloc(sizeof(*element));//idem allocation de la mémoire pour le 1er Element
//  if(liste == NULL || element == NULL){//On vérifie si les allocations dynamiques en fonctionner
//    exit(EXIT_FAILURE); //En cas d'erreur en arrête le programme en faisant appel à exit
//  }
//  //Si tout c'est bien passer on définit les valeurs de notre premier élément
//  strcat(element-> elem, "VmSize");//valeur du premier pointeur
//  element->suivant = NULL;//le premier element est aussi le dernier pour le moment
//  liste->premier = element;
//
//  return liste;
//};
//
// 2- Ajout d'un element à la Liste (au début)
//void insertion(Liste *liste, char *nvElement){
//  /*Creation du nouvel élément*/
//  Element *nouveau = malloc(sizeof(*nouveau));
//  if(liste == NULL || nouveau == NULL){//On vérifie si les allocations dynamiques en fonctionner
//    exit(EXIT_FAILURE); //En cas d'erreur en arrête le programme en faisant appel à exit
//  }
//  strcat(nouveau->elem, nvElement);
//
//  /*Insertion de l'élément au début de la liste*/
//  nouveau->suivant = liste->premier;
//  liste->premier = nouveau;
//};
//
//// 3- Suppression d'un element d'une Liste (premier element)
//
//void suppression(Liste *liste){
//  if(liste == NULL){
//    exit(EXIT_FAILURE);
//  }
//  if(liste->premier != NULL){
//    Element *aSupprimer = liste->premier;
//    liste->premier = liste->premier->suivant;
//    free(aSupprimer);
//  }
//};
//
// 4- Afficher la liste chaîner
//void afficherListe(Liste *liste){
//  if(liste == NULL){
//    exit(EXIT_FAILURE);
//  }
//  Element *actuel = liste->premier;
//  while(actuel != NULL){
//   printf("%s ->", actuel->elem);
//    actuel = actuel->suivant;
//  }
//  printf("NULL\n");
//};
//
//void processdir(const struct dirent *piddir, Liste *liste){
//    char path[BUFSZ];
//    char line[BUFSZ];
//    char line2[BUFSZ];
//    char *memstr;
//    char *memstr2;
//    FILE *pidmemfile;
//
//    if(liste == NULL){
//      exit(EXIT_FAILURE);
//    }
//    Element *actuel = liste->premier;
//    while(actuel != NULL){
//      // printf("%s ->", actuel->elem);  ------Test
//      int offset = strlen(actuel->elem);
//      char vmPeak[10]="";
//      strcat(vmPeak,actuel->elem);
//      actuel = actuel->suivant;
//      char vmSize[10]="";
//      strcat(vmSize,actuel->elem);
//      //printf("%s\n",vmPeak);  ------Test
//
//      //printf("%s ->", actuel->elem);   ------Test
//      int  offset2 = strlen(actuel->elem);
//
//
//      //strlen : calcul la longeur en nombre de caractère (ne prend pas en compte \0)
//      /* Construct full path of the file containt memory-info if this PID */
//      snprintf(path, BUFSZ, "/proc/%s/status", piddir->d_name);
//      /*
//        path -> tampon
//        size = BUFSZ -> nombre maximum d'octets qui seront écrit dans le tampon
//        /proc/%s/status = format -> chaine qui contient un format
//        piddir->d_name nom du répertoire
//      */
//
//      /* ouverture du fichier */
//      pidmemfile = fopen(path, "r"); //Rq: j'ai enlever rt -> r
//
//      /* Read line-by-line until we found the line we want */
//          while (1) {
//
//                int ret = fgets(line, BUFSZ, pidmemfile);
//                int ret2 = fgets(line2, BUFSZ, pidmemfile);
//                if(ret == NULL){
//                  if(feof(pidmemfile)){
//                    break;
//                  }else{
//                    perror("fgets");
//                    return 1;
//                  }
//                }
//
//              memstr = strstr(line,vmPeak);
//
//              memstr2 = strstr(line2,vmSize);
//              //printf("%s %s", memstr, memstr2);   //-----Test
//
//              //strstr : recherche la première occurence d'une sous-chaine dans une chaine principale et
//              //renvoi un pointeur visant la première occurence  si trouvé sinon renvoi NULL
//
//              if (memstr != NULL){  /* Found our line */
//                  memstr += offset;
//                  memstr2 += offset2;
//                  while ((*memstr == ' ' || *memstr == '\t') && (*memstr2 == ' ' || *memstr2 == '\t')) {
//                      if ((*memstr == '\0') && (*memstr2 == '\0')) {
//                          fprintf(stderr, "unexpected error in %s.\n", path);
//                          exit(1);
//                      }
//                      ++memstr;
//                      ++memstr2;
//                  }
//                  printf("PID %s: %s \t %s", piddir->d_name, memstr, memstr2);
//                  break;
//             }
//          }
//
//          actuel = actuel->suivant;
//
//    }
//
//fclose(pidmemfile);
//}
//
//int main()
//{
//
//  Liste *maListe = initialisation();
//  insertion(maListe, "VmPeak");
//  //afficherListe(maListe);
//
//  DIR *procdir;
//     struct dirent *procentry;
//
//     procdir = opendir("/proc");
//     if (procdir == NULL) {
//         perror("Could not open directory /proc");
//         return 1;
//     }
//
//     for(;;) {
//         procentry = readdir(procdir);
//         if (procentry == NULL) {
//             break;
//        }
//          // * if the name of an entry in /proc has only digits, then
//          // * it is a subdirectory containg info about a process,
//          // * while the name itself is the PID of the process.
//
//         if (!fnmatch("[1-9]*", procentry->d_name, 0)) {
//             processdir(procentry,maListe);
//         }
//     }
//
//return 0;
//}
