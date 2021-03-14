#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "reponse.txt";
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Erreur dans socket");
    exit(1);
  }
  printf("[+]Serveur socket est bien cree.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Erreur dans Bind");
    exit(1);
  }
  printf("[+]Bind réussi.\n");

  if(listen(sockfd, 10) == 0){
 printf("[+]Ecoute....\n");
 }else{
 perror("[-]Erreur dans l' Ecoute");
    exit(1);
 }

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  printf("[+] les donnees crees dans le fichier.\n");

  return 0;
}