target : progCommande \
		 options.exe \
		 clean

CC = gcc -Wall -Werror -W 

progCommande : progCommande.o commandes.o
	$(CC) -o progCommande progCommande.o commandes.o

progCommande.o : progCommande.c commandes.h
	$(CC) -c progCommande.c

options.exe : options.o
	$(CC) -o options.exe options.o
	
options.o : options.c
	$(CC) -c options.c

commandes.o : commandes.c
	$(CC) -c commandes.c

clean:
	rm -f *.o
