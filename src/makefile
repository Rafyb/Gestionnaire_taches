CC = gcc -Wall -Werror -W 

progCommande : progCommande.o
	$(CC) -o progCommande progCommande.o

progCommande.o : progCommande.c
	$(CC) -c progCommande.c


clean:
	rm -f *.o
