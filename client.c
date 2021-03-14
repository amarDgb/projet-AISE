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

#include "fichier.h"



int main(void)
{
 #if defined (WIN32)
 WSADATA WSAData;
 int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
 #else
 int erreur = 0;
 #endif

 buffer *buff = malloc(1024*1024);

 SOCKET sock;
 SOCKADDR_IN sin;
 //char buffer[32] = "";

 /* Si les sockets Windows fonctionnent */
 if(!erreur)
 {
 /* Création de la socket */
 sock = socket(AF_INET, SOCK_STREAM, 0);

 /* Configuration de la connexion */
 sin.sin_addr.s_addr = inet_addr("127.0.0.1");
 sin.sin_family = AF_INET;
 sin.sin_port = htons(PORT);

 /* Si l'on a réussi à se connecter */
 if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
 {
 printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons
(sin.sin_port));

printf("PID \t PPID \t Etat \t  command \t\n\n");

 /* Si l'on reçoit des informations : on les affiche à l'écran */
 //a voire
 while(recv(sock, buff, sizeof(buff), 0) != SOCKET_ERROR){


   //printf("%d \t %d \t %c \t %s\n",buff->tid, buff->ppid, buff->stat, buff->cmd);
   printf("%-10d \t %-10d \n", buff->tid, buff->ppid);
   // int init_size = strlen(buffer);
   // char delim[] = ":";
   //
   // char *ptr = strtok(buffer, delim);
   //
   // while (ptr != NULL)
   // {
   //   printf("%s \t", ptr);
   //   ptr = strtok(NULL, delim);
   // }
   // printf("\n");
   //printf("Recu : %s\n", buffer);
}


 }
 /* sinon, on affiche "Impossible de se connecter" */
 // else
 // {
 // printf("Impossible de se connecter\n");
 // }

 /* On ferme la socket */
 closesocket(sock);

 #if defined (WIN32)
 WSACleanup();
 #endif
 }
 /* On attend que l'utilisateur tape sur une touche, puis on ferme */
 getchar();

 return EXIT_SUCCESS;
}
