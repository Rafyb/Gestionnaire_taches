CC = gcc -Wall -Werror -W 

progCommande : progCommande.o commandes.o
	$(CC) -o progCommande progCommande.o commandes.o

progCommande.o : progCommande.c commandes.h
	$(CC) -c progCommande.c

commandes.o : commandes.c
	$(CC) -c commandes.c


clean:
	rm -f *.o
