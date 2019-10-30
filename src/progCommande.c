#include "commandes.h"
#include "printlog.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 
La commande doit respecter le format suivant :
./progCommande [options] {nombre repetition} {delai} {ligne de commande a executer}
*/
int main(int argc, char** argv)
{

 // ------ Test du nombre d'argument
  if(argc<4) {
    perror("Nombre d'argument invalide \n Veuillez à ce que la synthaxe corresponde à : progCommande {options} [nombre repetition] [delai] [ligne de commande a executer]");
    return 1;
  }


  // ------ Gerer les options
  // nombre d'argument pris par les options
  int opt = 0;

  // liste des differentes options possible
  int l = 0; // - log
  int p = 0; // - path
  
  for (int j=1; j< argc; j++) {
			if (argv[j][0]=='-'){
				int idx = 1;
				while (argv[j][idx]!='\0'){
					if (argv[j][idx]=='l' || argv[j][idx]=='L') l = j;
          if (argv[j][idx]=='p' || argv[j][idx]=='P') p = j;
					idx++;
				}
		  }
	}

  if(l>0){
    //options[opt] = "l";
    opt++;
    init_log();
    if(is_init())ecris_log(-1);
  }
  if(p>0){
    opt+=2;
    if (argv[p +1][0]=='-') {
					if(is_init()){
            ecris_log(2);
					  ecris_log(1);
          }
          perror("Le chemin n'a pas été spécifié\n");
          return 3;
    }
  }
  opt++;
  // ------ Passer la l'execution de la commande
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
