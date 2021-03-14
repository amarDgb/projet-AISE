#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SIZE 1024

void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-] Erreur d envoyer le fichier.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
char *args[] = {"cat", "reponse.txt",NULL};
  int sockfd;
  int caractereActuel = 0;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "test.txt";
  char *filename1 = "reponse.txt";
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Erreur dans socket");
    exit(1);
  }
  printf("[+]Serveur socket est bien cree.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Erreur dans socket");
    exit(1);
  }
 printf("[+]Connecté au Serveur.\n");

  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Erreur dans la lecture du fichier.");
    exit(1);
  }

  send_file(fp, sockfd);
  printf("[+]fichier bien transmit.\n");

  printf("[+] fin de la connexion.\n");
  close(sockfd);



execv("/bin/cat", args);
  /* fp = fopen(filename1, "r");
   if (fp != NULL)
   {
   do
        {
            caractereActuel = fgetc(fp); 
            printf("%c", caractereActuel); 
        } while (caractereActuel != EOF); 
 
        fclose(fp);

   }
   
*/
  return 0;
}