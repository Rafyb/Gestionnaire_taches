#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>

int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;

FILE* fichier = NULL;

void Donne_date_heure() {
	time_t t;
	struct tm* ma_tm;
 
	time(&t);
	ma_tm = localtime(&t);
	
	char* jour_sem;
	char* mois;
	
	switch(ma_tm->tm_wday){
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
	
	switch(ma_tm->tm_mon){
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
	
	fprintf(fichier, "%s %d %s %d, %02d:%02d:%02d\n", jour_sem, ma_tm->tm_mday, mois, ma_tm->tm_year+1900, ma_tm->tm_hour, ma_tm->tm_min, ma_tm->tm_sec);
}

void Nom_prog(char* prog){
	char* chemin=getcwd(NULL,1024);
	char* programme = NULL;
	char* complet;
	
	size_t nb_chemin  = strlen(chemin);
	size_t nb_programme = strlen(prog);
	
	programme = malloc (nb_programme); 
	strcpy(programme, prog +2);
	
	complet = malloc( (nb_chemin + nb_programme +2) * sizeof(char));
	complet = strcat(complet, chemin);
	complet = strcat(complet, "/");
	complet = strcat(complet, programme);
	
	fprintf(fichier, "- programme lancé: %s\n", programme);
	fprintf(fichier, "- répertoire courant: %s\n", chemin);
	fprintf(fichier, "- chemin complet: %s\n", complet);
}

void Ecris_Log(int log){
	switch(log){
		case -1:
			fprintf(fichier, "+-------------------------------------+\n");
			fprintf(fichier, "|         DEBUT DU TRAITEMENT         |\n");
			fprintf(fichier, "+-------------------------------------+\n");
			break;
		case 0:
			fprintf(fichier, "\n+-------------------------------------+\n");
			fprintf(fichier, "|      FIN NORMALE DU TRAITEMENT      |\n");
			fprintf(fichier, "+-------------------------------------+\n");
			break;
		case 1:
			fprintf(fichier, "\n+-------------------------------------+\n");
			fprintf(fichier, "|       FIN ANORMALE DU TRAITEMENT    |\n");
			fprintf(fichier, "+-------------------------------------+\n");
			break;
		case 2:
			fprintf(fichier, "Le chemin n'a pas été spécifié\n");
			break;
		default:
			fprintf(fichier, "+-------------------------------------+\n\n");
			break;
	}
}


int main(int argc, char** argv){

    fichier = fopen("../log/test.log", "w+");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de log");
        return 1;
    }
    else
    {
		Ecris_Log(-1);
		Nom_prog(argv[0]);
		Donne_date_heure();
		Ecris_Log(99);
		
		for (int j=1; j< argc; j++) {
			if (argv[j][0]=='-'){
				int idx = 1;
				while (argv[j][idx]!='\0'){
					if (argv[j][idx]=='A')A=j;
					if (argv[j][idx]=='B')B=j;
					if (argv[j][idx]=='C')C=j;
					if (argv[j][idx]=='D')D=j;
					if (argv[j][idx]=='E')E=j;
					idx++;
				}
			}
		}
		
		if (A != 0) {
			if (A==argc-1) {
				printf("Le chemin n'a pas été spécifié\n");
				Ecris_Log(2);
				Ecris_Log(1);
				fclose(fichier);
				return 1;
				
			}	
			else {
				if (argv[A +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					Ecris_Log(2);
					Ecris_Log(1);
					fclose(fichier);
					return 1;
				}
				else
				{
					printf("A: %s\n", argv[A +1]);
					fprintf(fichier, "A: %s\n", argv[A+1]);
				}
			}
		}
		if (B != 0) {
			if (B==argc-1) {
				printf("Le chemin n'a pas été spécifié\n");
				Ecris_Log(2);
				Ecris_Log(1);
				fclose(fichier);
				return 1;
			}
			else {
				if (argv[B +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					Ecris_Log(2);
					Ecris_Log(1);
					fclose(fichier);
					return 1;
				}
				else
				{
					printf("B: %s\n", argv[B +1]);
					fprintf(fichier, "B: %s\n", argv[B+1]);
				}
			}
		}
		if (C != 0) {
			if (C==argc-1) {
				printf("Le chemin n'a pas été spécifié\n");
				Ecris_Log(2);
				Ecris_Log(1);
				fclose(fichier);
				return 1;
			}		
			else {
				if (argv[C +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					Ecris_Log(2);
					Ecris_Log(1);
					fclose(fichier);
					return 1;
				}
				else
				{
					printf("C: %s\n", argv[C +1]);
					fprintf(fichier, "C: %s\n", argv[C+1]);
				}
			}
		}
		if (D != 0) {
			if (D==argc-1) {
				printf("Le chemin n'a pas été spécifié\n");
				Ecris_Log(2);
				Ecris_Log(1);
				fclose(fichier);
				return 1;
			}
			else {
				if (argv[D +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					Ecris_Log(2);
					Ecris_Log(1);
					fclose(fichier);
					return 1;
				}
				else
				{
					printf("D: %s\n", argv[D +1]);
					fprintf(fichier, "D: %s\n", argv[D+1]);
				}
			}
		}
		if (E != 0) {
			if (E==argc-1) {
				printf("Le chemin n'a pas été spécifié\n");
				Ecris_Log(2);
				Ecris_Log(1);
				fclose(fichier);
				return 1;
			}
			else {
				if (argv[E +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					Ecris_Log(2);
					Ecris_Log(1);
					fclose(fichier);
					return 1;
				}
				else
				{
					printf("E: %s\n", argv[E +1]);
					fprintf(fichier, "E: %s\n", argv[E+1]);
				}
			}
		}	
	}
	Ecris_Log(0);
	fclose(fichier);
	return 0;
}
