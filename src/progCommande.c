#include "commandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
  /* 
  La commande doit respecter le format suivant :
  ./progCommande [options] {nombre repetition} {delai} {ligne de commande a executer}
  */

 // Test du nombre d'argument
  if(argc<4) {
    perror("Nombre d'argument invalide \n Veuillez à ce que la synthaxe corresponde à : /progCommande [options] {nombre repetition} {delai} {ligne de commande a executer}");
    return 1;
  }

  int opt = 1;

  // Gerer les options
  while(argv[opt][0] == '-'){
    opt += 2;
  }

  // Passer la l'execution de la commande
  int nbr = atoi(argv[opt]);
  int timewait = atoi(argv[opt+1]);
  int taille = argc-(opt+2);

  char* ligne_de_commande[10]; 
  for(int i = 0; i < taille; i++){
    ligne_de_commande[i] = argv[opt+2+i];
  }
  executerCommandeBoucle(nbr,timewait,taille,ligne_de_commande);  

  return 0;
}
