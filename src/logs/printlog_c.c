/**
 * @file      printlog_c.c
 * @author    Johann
 * @version   1.0
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'ecritures des logs.
 *
 */

#include "printlog_h.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

FILE *fichier = NULL;
char *prog = NULL;

/**
 *  La fonction écris le message d'erreur dans les logs puis ferme le fichier
 *
 * @author Raphael
 *
 **/
void erreur_traitement(char *errorMsg) {
  perror(errorMsg);
  if (is_init()) {
    ecris_log(errorMsg);
    ecris_log_ES(1);
    close_log();
  }
  exit(EXIT_FAILURE);
}

/**
 * La fonction
 *
 * @author Johann
 *
 */
void ecris_date_heure(void) {
  time_t t;
  struct tm *ma_tm;

  time(&t);
  ma_tm = localtime(&t);

  char *jour_sem;
  char *mois;

  switch (ma_tm->tm_wday) {
  case 0:
    jour_sem = "Dimanche";
    break;
  case 1:
    jour_sem = "Lundi";
    break;
  case 2:
    jour_sem = "Mardi";
    break;
  case 3:
    jour_sem = "Mercredi";
    break;
  case 4:
    jour_sem = "Jeudi";
    break;
  case 5:
    jour_sem = "Vendredi";
    break;
  case 6:
    jour_sem = "Samedi";
    break;
  }

  switch (ma_tm->tm_mon) {
  case 0:
    mois = "Janvier";
    break;
  case 1:
    mois = "Février";
    break;
  case 2:
    mois = "Mars";
    break;
  case 3:
    mois = "Avril";
    break;
  case 4:
    mois = "Mai";
    break;
  case 5:
    mois = "Juin";
    break;
  case 6:
    mois = "Juillet";
    break;
  case 7:
    mois = "Aout";
    break;
  case 8:
    mois = "Septembre";
    break;
  case 9:
    mois = "Octobre";
    break;
  case 10:
    mois = "Novembre";
    break;
  case 11:
    mois = "Décembre";
    break;
  }

  fprintf(fichier, "%s %d %s %d, %02d:%02d:%02d\n", jour_sem, ma_tm->tm_mday,
          mois, ma_tm->tm_year + 1900, ma_tm->tm_hour, ma_tm->tm_min,
          ma_tm->tm_sec);
}

/**
 * La fonction
 *
 * @author Johann
 *
 */
void ecris_nom_prog(char *prog) {
  char *chemin = getcwd(NULL, 1024);
  char *programme = NULL;
  char *complet;

  size_t nb_chemin = strlen(chemin);
  size_t nb_programme = strlen(prog);

  programme = malloc(nb_programme);
  strcpy(programme, prog + 2);

  complet = malloc((nb_chemin + nb_programme + 2) * sizeof(char));
  complet = strcat(complet, chemin);
  complet = strcat(complet, "/");
  complet = strcat(complet, programme);

  fprintf(fichier, "- programme lancé: %s\n", programme);
  fprintf(fichier, "- répertoire courant: %s\n", chemin);
  fprintf(fichier, "- chemin complet: %s\n", complet);
}

/**
 * La fonction verifie si le fichier est initialise
 *
 * @author Raphael Bauvin
 * @return 1 si fichier ouvert
 * @return 0 si fichier fermé
 */
int is_init(void) { return fichier != NULL; }

/**
 * La fonction ferme le fichier
 *
 * @author Raphael Bauvin
 * @return 0 si fichier fermé avec succé
 */
int close_log(void) { return fclose(fichier); }

/**
 * La fonction écris dans les logs le message ainsi que la date et l'heure
 * d'enregistrement
 *
 * @author Johann
 *
 */
void ecris_log(char *trace) {
  ecris_date_heure();
  fprintf(fichier, "%s\n", trace);
  fflush(fichier);
}
/**
 * La fonction
 *
 * @author Johann
 *
 */
void ecris_log_ES(int log) {
  switch (log) {
  case -1:
    fprintf(fichier, "==========================\n");
    fprintf(fichier, "    DEBUT DU TRAITEMENT   \n");
    fprintf(fichier, "==========================\n");
    break;
  case 0:
    fprintf(fichier, "==========================\n");
    fprintf(fichier, "FIN NORMALE DU TRAITEMENT\n");
    fprintf(fichier, "==========================\n");
    break;
  case 1:
    fprintf(fichier, "==========================\n");
    fprintf(fichier, "FIN ANORMALE DU TRAITEMENT\n");
    fprintf(fichier, "==========================\n");
    break;
  }
  fflush(fichier);
}

/**
 * La fonction ouvre le fichier des logs
 *
 * @return 0 si le fichier est ouvert avec succé
 * @return 1 si une erreur est survenu
 *
 */
int init_log(char *nom_prog) {
  prog = nom_prog;
  fichier = fopen("log/test.log", "w+");
  if (fichier == NULL) {
    perror("Erreur lors de l'ouverture du fichier de log");
    return 1;
  }
  ecris_nom_prog(prog);
  ecris_date_heure();
  ecris_log_ES(-1);
  return 0;
}
