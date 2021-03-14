# Indication :

Avant de compiler il faut installer :

Sur un système Ubuntu: 
	sudo apt-get update
	sudo apt-get install libproc-dev

Sur un système Manjaro: 
    sudo pacman -Syyu
    sudo pacman install procps-ng


Version Envoie Avec Fichier : 
 dans cette version on a fait communiquer un client avec un serveur, ce dernier genère des informations concernant les processus en cours
 d'éxécution et les stockes dans des fichiers et il les envoies au client pour les afficher dans sa machine.
la communication est faite avec les sockets.
  Compilation: executer : make

Version envoi avec structure :
 Compilation : gcc -o main main.c -lprocps
               gcc -o client client.c

 Execution : ./main
	     ./client

 L'envoie au niveau de cette étape se fait avec un buffer.
