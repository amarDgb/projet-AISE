#if defined (WIN32)
 #include <winsock2.h>
 typedef int socklen_t;
#elif defined (linux)
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <unistd.h>
 #define INVALID_SOCKET -1
 #define SOCKET_ERROR -1
 #define closesocket(s) close(s)
 typedef int SOCKET;
 typedef struct sockaddr_in SOCKADDR_IN;
 typedef struct sockaddr SOCKADDR;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT 1024

#include <stdio.h>
#include <string.h>
#include <proc/readproc.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h> //sleep
#include <signal.h>
#include <fcntl.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "fichier.h"

void jsonout (int pid, int ppid,long priority, long nice, unsigned long vm_size,char state){

    /* open file for writing */
    FILE *fd = fopen("info.json","a+");

    if(fd == NULL){
      perror("fopen");
    }


    fprintf (fd, "{\n \t\"%ld\" : {\n",pid);    /* print header to file */

    fprintf (fd, "\t \t\"Ppid\" : \" %ld \",\n",ppid);
    //fprintf (fd, "\t \t\"User\" : \" %ld \",\n",user);


    fprintf (fd, "\t \t\"Priority\" : \" %ld \" \n",priority);
    fprintf (fd, "\t \t\"Nice\" : \" %ld \" \n",nice);
    fprintf (fd, "\t \t\"Vm_size\" : \" %lu \" \n",vm_size);

    fprintf (fd, "\t \t\"State\" : \" %c \" \n",state);
    //fprintf (fd, "\t \t\"COM\" : \" %u \" \n",com);

    fprintf (fd, "\t \t }\n}\n\n");     /* print closing tag */

    fclose (fd);
}

int main(int argc, char** argv)
{

#if defined (WIN32)
 WSADATA WSAData;
 int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
 #else
 int erreur = 0;
 #endif


 // fillarg used for cmdline
 // fillstat used for cmd
 while(1){

 buffer *buff = malloc(1024*1024);

 SOCKET sock;
 SOCKADDR_IN sin;
 SOCKET csock;
 SOCKADDR_IN csin;

 //char *buffer = malloc(1024*1024);


 socklen_t recsize = sizeof(csin);
 int sock_err;

 /* Si les sockets Windows fonctionnent */
 if(!erreur)
 {
 sock = socket(AF_INET, SOCK_STREAM, 0);

 /* Si la socket est valide */
 if(sock != INVALID_SOCKET)
 {
 printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

 /* Configuration */
 sin.sin_addr.s_addr = htonl(INADDR_ANY); /* Adresse IP automati
que */
 sin.sin_family = AF_INET; /* Protocole familial (IP) */
 sin.sin_port = htons(PORT); /* Listage du port */
 sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
 /* Si la socket fonctionne */
 if(sock_err != SOCKET_ERROR)
 {
 /* Démarrage du listage (mode server) */
 sock_err = listen(sock, 5);
 printf("Listage du port %d...\n", PORT);

 /* Si la socket fonctionne */
 if(sock_err != SOCKET_ERROR)
 {
 /* Attente pendant laquelle le client se connecte */
 printf("Patientez pendant que le client se connecte sur le port %d...\
n", PORT);

 csock = accept(sock, (SOCKADDR*)&csin, &recsize);
 printf("Un client se connecte avec la socket %d de %s:%d\n", csock
, inet_ntoa(csin.sin_addr), htons(csin.sin_port));




buff->last = 0;

 PROCTAB* proc = openproc(PROC_FILLARG | PROC_FILLSTAT | PROC_FILLMEM | PROC_FILLSTATUS | PROC_FILLUSR);

 proc_t proc_info;

 // zero out the allocated proc_info memory
 memset(&proc_info, 0, sizeof(proc_info));
printf("PID \t PPID \t USER \t PR \t NI \t VIRT \t Etat \t\n\n");
 while (readproc(proc, &proc_info) != NULL) {

 buff->tid = proc_info.tid;
 buff->ppid = proc_info.ppid;
 //strcat(buff->euser, proc_info.euser);
 buff->priority = proc_info.priority;
 buff->nice = proc_info.nice;
 buff->vm_size = proc_info.vm_size;
  
printf("%-10d \t %-10d \t %s \t %ld \t  %ld \t %lu  \t %c \t", proc_info.tid, proc_info.ppid,proc_info.euser, proc_info.priority,proc_info.nice, proc_info.vm_size, proc_info.state);
if (proc_info.cmdline != NULL) {
 // print full cmd line if available
 printf("%s\n", *proc_info.cmdline);
 jsonout(proc_info.tid, proc_info.ppid, proc_info.priority,proc_info.nice, proc_info.vm_size, proc_info.state);
 //strcat(buff->cmd, proc_info.cmdline);
 //sprintf(buff->cmd, "%s", proc_info.cmdline);
} else {
 // if no cmd line use executable filename
 printf("[%s]\n", proc_info.cmd);
 jsonout(proc_info.tid, proc_info.ppid, proc_info.priority,proc_info.nice, proc_info.vm_size, proc_info.state);
 //strcat(buff->cmd, proc_info.cmd);
}

 sock_err = send(csock, buff, sizeof(buff), 0);

}


 closeproc(proc);
shutdown(csock, 2);
 }
 }

 /* Fermeture de la socket */
 printf("Fermeture de la socket...\n");
 closesocket(sock);
 printf("Fermeture du serveur terminee\n");
}



 #if defined (WIN32)
 WSACleanup();
 #endif
 }

 /* On attend que l'utilisateur tape sur une touche, puis on ferme */
 getchar();
 sleep(3);
}
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
