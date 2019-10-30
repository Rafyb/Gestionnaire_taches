#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;


int main(int argc, char** argv){
	
	FILE* fichier = NULL;

    fichier = fopen("../log/test.log", "w+");

    if (fichier = NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de log");
        return 1;
    }
    else
    {
		fprintf(fichier, "==========================");
		fprintf(fichier, "    DEBUT DU TRAITEMENT");
		fprintf(fichier, "==========================");
		
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
				fprintf(fichier, "Le chemin n'a pas été spécifié\n");
				fprintf(fichier, "==========================");
				fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
				fprintf(fichier, "==========================");
				fclose(fichier);
				return 1;
				
			}	
			else {
				if (argv[A +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "==========================");
					fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
					fprintf(fichier, "==========================");
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
				fprintf(fichier, "Le chemin n'a pas été spécifié\n");
				fprintf(fichier, "==========================");
				fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
				fprintf(fichier, "==========================");
				fclose(fichier);
				return 1;
			}
			else {
				if (argv[B +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "==========================");
					fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
					fprintf(fichier, "==========================");
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
				fprintf(fichier, "Le chemin n'a pas été spécifié\n");
				fprintf(fichier, "==========================");
				fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
				fprintf(fichier, "==========================");
				fclose(fichier);
				return 1;
			}		
			else {
				if (argv[C +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "==========================");
					fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
					fprintf(fichier, "==========================");
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
				fprintf(fichier, "Le chemin n'a pas été spécifié\n");
				fprintf(fichier, "==========================");
				fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
				fprintf(fichier, "==========================");
				fclose(fichier);
				return 1;
			}
			else {
				if (argv[D +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "==========================");
					fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
					fprintf(fichier, "==========================");
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
				fprintf(fichier, "Le chemin n'a pas été spécifié\n");
				fprintf(fichier, "==========================");
				fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
				fprintf(fichier, "==========================");
				fclose(fichier);
				return 1;
			}
			else {
				if (argv[E +1][0]=='-') {
					printf("Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "Le chemin n'a pas été spécifié\n");
					fprintf(fichier, "==========================");
					fprintf(fichier, "FIN ANORMALE DU TRAITEMENT");
					fprintf(fichier, "==========================");
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
	fprintf(fichier, "==========================");
	fprintf(fichier, "FIN NORMALE DU TRAITEMENT");
	fprintf(fichier, "==========================");
	fclose(fichier);
	return 0;
}
