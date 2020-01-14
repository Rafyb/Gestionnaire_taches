/**
 * @file      printlog_h.h
 * @author    Raphael Bauvin, Johann De Almeida
 * @version   14012020
 * @date      30 Octobre 2019
 * @brief     Définit les fonctions utiles a l'ecritures dans les logs.
 *
 */
#ifndef PRINTLOG_H
#define PRINTLOG_H

/**
 *  @brief La fonction écrit le message d'erreur dans les logs puis ferme le
 * fichier
 *
 * @param errorMsg : le message d'erreur a écrire
 **/
void erreur_traitement(char *errorMsg);

/**
 *  @brief La fonction écrit le temps avant la prochaine execution dans les logs
 *
 * @param timewait : temps à attendre avant prochaine execution
 **/
void ecris_temps(int timewait);

/**
 * @brief La fonction converti un entier en chaine de 2 caractères
 *
 * @param dateint : le numéro du jour ou du mois en nombre
 * @return datestr : le numéro du jour ou du mois en chaine de caractères
 */
char *convert_date(int dateint);

/**
 * @brief La fonction concatene les 2 chaines de caractères à la manière de
 * strcat
 *
 * @param log : premiere chaine
 * @param argument : deuxieme chaine
 * @return ligne : la ligne concaténé
 */
char *concatLigne(char *log, char *argument);

/**
 * @brief La fonction écrit la date et l'heure actuelle dans les logs
 *
 * @param opt : le format de la date désiré : 1 pour le format littéral
 *                                            2 pour le format numérique
 */
void ecris_date_heure(int opt);

/**
 * @breif La fonction écrit le nom du programme dans les logs
 *
 * @param prog : nom du programme
 */
void ecris_nom_prog(char *prog);

/**
 * @brief La fonction vérifie si le fichier est initialisé
 *
 * @return 1 si fichier ouvert
 * @return 0 si fichier fermé
 */
int is_init(void);

/**
 * @breif La fonction ferme le fichier
 *
 * @return 0 si fichier est fermé avec succés
 */
int close_log(void);

/**
 * @brief La fonction écrit dans les logs le message ainsi que la date et
 * l'heure d'enregistrement du message
 *
 * @param trace : le message à écrire
 */
void ecris_log(char *trace);

/**
 * @brief La fonction fait des jolies séparations dans les logs :D
 *
 * @param log : le numéro de la séparation désiré
 */
void ecris_log_ES(int log);

/**
 * @brief La fonction ouvre le fichier des logs
 *
 * @param nom_prog : le nom du programme lancé
 * @return 0 si le fichier est ouvert avec succé
 * @return 1 si une erreur est survenu
 */
int init_log(char *nom_prog);

#endif
