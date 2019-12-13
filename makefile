target : progCommande \
		 	 	 clean

CC = gcc -Wall -Werror -W

progCommande : main.o commandes_c.o printlog_c.o
	$(CC) -o progCommande main.o commandes_c.o printlog_c.o

commandes_c.o : src/commandes/commandes_c.c src/commandes/commandes_h.h
	$(CC) -c src/commandes/commandes_c.c

main.o : src/commandes/main.c
	$(CC) -c src/commandes/main.c

#options.exe : options.o
#	$(CC) -o options.exe options.o

#options.o : options.c
#	$(CC) -c options.c

printlog_c.o : src/logs/printlog_c.c src/logs/printlog_h.h
	$(CC) -c src/logs/printlog_c.c

clean:
	rm -f *.o
