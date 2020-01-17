target : progCommande \
		 	 	 clean

CC = gcc -Wall -Werror -W

progCommande : main.o commandes_c.o printlog_c.o
	$(CC) -o progCommande main.o commandes_c.o printlog_c.o

commandes_c.o : src/commandes/commandes_c.c src/libused.h src/logs/printlog_h.h
	$(CC) -c src/commandes/commandes_c.c

main.o : src/commandes/main.c src/commandes/commandes_h.h src/logs/printlog_h.h
	$(CC) -c src/commandes/main.c

printlog_c.o : src/logs/printlog_c.c src/logs/printlog_h.h
	$(CC) -c src/logs/printlog_c.c

clean:
	rm -f *.o
