/**
 * @file      printlog_c.c
 * @author    Raphael Bauvin, Johann De Almeida
 * @version   14012020
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'ecritures dans les logs.
 *
 */
#include "../libused.h"

FILE *fichier = NULL;

/**
 *  @brief La fonction écrit le message d'erreur dans les logs puis ferme le
 * fichier
 *
 * @param errorMsg : le message d'erreur a écrire
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
 *  @brief La fonction écrit le temps avant la prochaine execution dans les logs
 *
 * @param timewait : temps à attendre avant prochaine execution
 **/
void ecris_temps(int timewait) {
  if (is_init()) {
    char timewaitstr[12];
    sprintf(timewaitstr, "%d", timewait);
    char *ligne =
        concatLigne("Temps avant prochaine éxécution : ", timewaitstr);
    ecris_log(concatLigne(ligne, " secondes "));
  }
}

/**
 * @brief La fonction converti un entier en chaine de 2 caractères
 *
 * @param dateint : le numéro du jour ou du mois en nombre
 * @return datestr : le numéro du jour ou du mois en chaine de caractères
 */
char *convert_date(int dateint) {
  char *datestr = malloc(sizeof(char) * 3);
  sprintf(datestr, "%d", dateint);
  if (dateint <= 9) {
    char *newdate = malloc(sizeof(char) * 3);
    newdate[0] = '0';
    newdate[1] = datestr[0];
    newdate[2] = '\0';
    return newdate;
  }
  return datestr;
}

/**
 * @brief La fonction concatene les 2 chaines de caractères à la manière de
 * strcat
 *
 * @param log : premiere chaine
 * @param argument : deuxieme chaine
 * @return ligne : la ligne concaténé
 */
char *concatLigne(char *log, char *argument) {
  int nbr = strlen(log) + strlen(argument) + 1;
  char *ligne = malloc(sizeof(char) * nbr);
  strcpy(ligne, "");
  strcat(ligne, log);
  strcat(ligne, argument);
  return ligne;
}

/**
 * @brief La fonction écrit la date et l'heure actuelle dans les logs
 *
 * @param opt : le format de la date désiré : 1 pour le format littéral
 *                                            2 pour le format numérique
 */
void ecris_date_heure(int opt) {
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

  switch (opt) {

  case 1:
    fprintf(fichier, "%s %d %s %d, %02d:%02d:%02d\n", jour_sem, ma_tm->tm_mday,
            mois, ma_tm->tm_year + 1900, ma_tm->tm_hour, ma_tm->tm_min,
            ma_tm->tm_sec);
    break;

  case 2:
    jour_sem = convert_date(ma_tm->tm_mday);
    mois = convert_date(ma_tm->tm_mon + 1);
    fprintf(fichier, "|| %s/%s/%d - %02d:%02d:%02d || ", jour_sem, mois,
            ma_tm->tm_year + 1900, ma_tm->tm_hour, ma_tm->tm_min,
            ma_tm->tm_sec);
    break;
  }
}

/**
 * @breif La fonction écrit le nom du programme dans les logs
 *
 * @param prog : nom du programme
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
 * @brief La fonction vérifie si le fichier est initialisé
 *
 * @return 1 si fichier ouvert
 * @return 0 si fichier fermé
 */
int is_init(void) { return fichier != NULL; }

/**
 * @breif La fonction ferme le fichier
 *
 * @return 0 si fichier est fermé avec succés
 */
int close_log(void) { return fclose(fichier); }

/**
 * @brief La fonction écrit dans les logs le message ainsi que la date et
 * l'heure d'enregistrement du message
 *
 * @param trace : le message à écrire
 */
void ecris_log(char *trace) {
  ecris_date_heure(2);
  fprintf(fichier, "%s\n", trace);
  fflush(fichier);
}

/**
 * @brief La fonction fait des jolies séparations dans les logs :D
 *
 * @param log : le numéro de la séparation désiré
 */
void ecris_log_ES(int log) {
  switch (log) {
  case -1:
    fprintf(fichier, "====================================================\n");
    fprintf(fichier, "                  DEBUT DU TRAITEMENT   \n");
    fprintf(fichier, "====================================================\n");
    break;
  case 0:
    fprintf(fichier, "====================================================\n");
    fprintf(fichier, "              FIN NORMALE DU TRAITEMENT\n");
    fprintf(fichier, "====================================================\n");
    break;
  case 1:
    fprintf(fichier, "====================================================\n");
    fprintf(fichier, "              FIN ANORMALE DU TRAITEMENT\n");
    fprintf(fichier, "====================================================\n");
    break;
  }
  fflush(fichier);
}

/**
 * @brief La fonction ouvre le fichier des logs
 *
 * @param nom_prog : le nom du programme lancé
 * @return 0 si le fichier est ouvert avec succé
 * @return 1 si une erreur est survenu
 */
int init_log(char *nom_prog) {
  char *prog = nom_prog;
  fichier = fopen("log/test.log", "w+");
  if (fichier == NULL) {
    perror("Erreur lors de l'ouverture du fichier de log");
    return 1;
  }
  ecris_nom_prog(prog);
  ecris_date_heure(1);
  ecris_log_ES(-1);
  return 0;
}
