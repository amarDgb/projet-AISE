CC = gcc

all: proc serveur client exeproc exeserveur 

proc: proc.c
	$(CC) -o proc.exe proc.c -lprocps


exeproc:
	./proc.exe

exeserveur:
	./serveur.exe

	
	
serveur: serveur.c 
	$(CC) -o serveur.exe serveur.c

client: client.c 
	$(CC) -o client.exe client.c 



clean:
	rm -f *.o client serveur proc
	
.PHONY: clean
