target : progCommande \
		 options.exe \
		 clean

CC = gcc -Wall -Werror -W 

progCommande : progCommande.o
	$(CC) -o progCommande progCommande.o

progCommande.o : progCommande.c
	$(CC) -c progCommande.c

options.exe : options.o
	gcc -o options.exe options.o
	
options.o : options.c
	gcc -c options.c

clean:
	rm -f *.o
