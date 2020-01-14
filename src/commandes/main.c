/**
 * @file      commandes_c.c
 * @author    Raphael Bauvin, Johann De Almeida
 * @version   14012020
 * @date      30 Octobre 2019
 *
 * @brief     Définit les fonctions utiles a l'execution de commande.
 *
 */
#include "../libused.h"

/**
 * La commande doit respecter le format suivant :
 * ./progCommande [options] {nombre repetition} {delai} {ligne de commande a
 * executer}
 *
 * Les options suivantes sont disponibles :
 *    -l ( ou -L ) pour activer les logs
 *    -h ( ou -H ) pour spécifier que le temps fournis est en heure
 *    -m ( ou -M ) pour spécifier que le temps fournis est en minute
 *    -p ( ou -P ) pour spécifier le chemin
 *    -d ( ou -D ) pour que la première se fasse en différé
 *
 * @brief La fonction main commence par traité les options, puis récupère dans
 * des variables les informations sur le lancement de la commande et enfin fait
 * éxécuter la suite du programme par un processus fils
 *
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
  T_Options options;
  options.path = "";
  options.h = 1;
  options.m = 1;
  options.l = 1;
  options.d = 1;
  // opt : nombre d'argument sur la ligne pris par les options
  int opt = gerer_options(argc, argv, &options);
  if (opt < 0)
    return 4;

  // ------ Passer la l'execution de la commande
  // Nombre de répétition
  int nbr = atoi(argv[++opt]);
  // Temps entre chaque répétition
  int timewait = (atoi(argv[++opt]) * options.m) * options.h;

  if (nbr == 0 || timewait == 0) {
    erreur_traitement("Nombre d'argument invalide");
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
    erreur_traitement("Erreur fork\n");
    exit(errno);
  }
  if (pid_fils == 0) {
    if (options.d == 0) { // Si lancement en différé
      ecris_temps(timewait);
      sleep(timewait);
    }
    exe_cmd_ntimes(nbr, timewait, taille, ligne_de_commande, options.path);
  }

  // Fin du processus père
  return 0;
}
