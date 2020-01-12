/**
 * @file      main.c
 * @author    Raphael Bauvin
 * @version   2.3
 * @date      30 Octobre 2019
 * @brief     Contient le main principale du programme ainsi que la gestion des
 * options
 *
 *
 */

#include "../logs/printlog_h.h"
#include "commandes_h.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * La commande doit respecter le format suivant :
 *./progCommande [options] {nombre repetition} {delai} {ligne de commande a
 *executer}
 *
 * Les options suivantes sont disponibles :
 *    -l ( ou -L ) pour activer les logs
 *    -h ( ou -H ) pour spécifier que le temps fournis est en heure
 *    -m ( ou -M ) pour spécifier que le temps fournis est en minute
 *    -p ( ou -P ) pour spécifier le chemin
 *
 * @author Raphael Bauvin / Johann
 * @param argc nombre d'argument
 * @param argv liste des arguments
 */
int main(int argc, char **argv) {

  // ------ Test du nombre d'argument
  if (argc < 4) {
    perror("Nombre d'argument invalide");
    print_help();
    return 3;
  }

  // ------ Gerer les options
  int opt = 0;     // nombre d'argument sur la ligne pris par les options
  char *path = ""; // - path
  int h = 1;       // - heure
  int m = 1;       // - minute

  for (int j = 1; j < argc; j++) {
    if (argv[j][0] == '-') {
      int idx = 1;

      while (argv[j][idx] != '\0') {
        // Converion du temps à attendre en heure
        if (argv[j][idx] == 'h' || argv[j][idx] == 'H') {
          if (m > 1) {
            perror("Le temps ne peut pas être spécifié en minute et en heure "
                   "en même temps\n");
            return 4;
          }
          h = 3600;
          opt++;
        }
        // Converion du temps à attendre en minute
        if (argv[j][idx] == 'm' || argv[j][idx] == 'M') {
          if (h > 1) {
            perror("Le temps ne peut pas être spécifié en minute et en heure "
                   "en même temps\n");
            return 4;
          }
          m = 60;
          opt++;
        }
        // Utilisation d'un chemin different pour l'execution du fichier
        if (argv[j][idx] == 'p' || argv[j][idx] == 'P') {
          path = argv[++j];
          opt += 2;
          if (!(strlen(path) > 0)) {
            perror("Le chemin n'a pas été spécifié\n");
            return 3;
          }
          idx += strlen(path);
        }
        // Utilisation des logs
        if (argv[j][idx] == 'l' || argv[j][idx] == 'L') {
          opt++;
          init_log(argv[0]);
        }
        idx++;
      }
    }
  }

  // ------ Passer la l'execution de la commande
  int nbr = atoi(argv[++opt]);                // Nombre de répétition
  int timewait = (atoi(argv[++opt]) * m) * h; // Temps entre chaque répétition
  if (nbr == 0 || timewait == 0) {
    perror("Nombre d'argument invalide");
    print_help();
    return 2;
  }

  // Récupération de la ligne de commande
  int taille = argc - (++opt);
  char *ligne_de_commande[10];
  for (int i = 0; i < taille; i++) {
    ligne_de_commande[i] = argv[opt + i];
  }

  // Création du processus qui va s'occuper de l'éxécution répété de la commande
  pid_t pid_fils = fork();
  if (pid_fils == -1) {
    perror("Erreur fork\n");
    exit(errno);
  }
  if (pid_fils == 0) {
    // printf("%d\n", nbr);
    // printf("%d\n", timewait);
    // printf("%d\n", taille);
    // printf("%s\n", ligne_de_commande[0]);
    // printf("%s\n", path);
    exe_cmd_ntimes(nbr, timewait, taille, ligne_de_commande, path);
  }

  // Fin du processus père
  return 0;
}
