#include "voiture.h"
#include "utilitaire.h"
#include "qualification.h"
#include <stdio.h>
#include <stdlib.h>

double tempsQualif1 = 1080;//1080/60 = 18 min
double tempsQualif2 = 900;//15 min
double tempsQualif3 = 720;//12 min

//Tri de voitures
void sortVoitures(structTuture voituresQualif[], int sizeArrayVoitures)
{
	int i=0;
	structTuture tmpTuture;
	int j = 0;
	//Compare les voitures entre elles (1 avec 1, 1 avec 2, etc)
	for(i=0; i < sizeArrayVoitures; i++)
		//Remplit le i du tableau /////////////////////////////////// ?? 
	{
		for(j = i+1; j < sizeArrayVoitures; j++)
			//Vérifie s'il n'y a pas de nb plus petits dans le cas suivant   PQ
		{
			if(voituresQualif[j].topCircuit < voituresQualif[i].topCircuit)
			{
				//Si vrai, switch les nombres
				tmpTuture = voituresQualif[i];
				voituresQualif[i] = voituresQualif[j];
				voituresQualif[j] = tmpTuture;
			}
		}
	}
}

void buildStartPosition(structTuture voituresQualif[], int q)
{
	//fixe les limites des boucles en fonction des paramètres
	int loop = 0;
	int startArray = 0;
	int loop2 = 0;
	int startArray2 = 0;
	
	if (q == 1) {
		loop = 20;
		startArray = 15;
		
		loop2 = 15;
		startArray2 = 0;
	}
	if (q == 2) {
		loop = 15;
		startArray = 10;
		
		loop2 = 10;
		startArray2 = 0;
	}
	if (q == 3) {
		loop = 10;
		startArray = 0;
	}
	
	//Remplissage des tableaux de listes de départ (prochain qualif et course)
	for(int i=startArray; i < loop; i++)
	{
		startPosition[i] = voituresQualif[i].nom;
	}
	
	for(int i=startArray2; i < loop2; i++)
	{
		if (q == 1) {
			voituresQualif2[i] = voituresQualif[i];
		}
		else if (q == 2)
		{
			voituresQualif3[i] = voituresQualif[i];
		}
	}
}


void qualif(int index, int q)
{
	id_sem = semaph(id_sem, &semWait, 1);
	id_sem = semaph(id_sem, &semDo, 1);
	double temps = getCurrTemps();
	id_sem = semaph(id_sem, &semPost, 1);
	double tempsQualif = 0.0;
	
	//determine la durée de l'essai
	if(q==1)
	{
		tempsQualif = tempsQualif1;
	}
	if(q==2)
	{
		tempsQualif = tempsQualif2;
	}
	if(q==3)
	{
		tempsQualif = tempsQualif3;
	}
	
	//boucle jusqu'à ce que le temps soit écoulé ou que la voiture ait abandonné
	while(temps<tempsQualif && voitures[index].isOut == 0)
	{
		genereTempsS1(index);
		
		//si la voiture a un meilleur temps pour S1 que toutes les autres, mise à jour de la variable globale
		if(voitures[index].topS1<smv[7])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[7] = voitures[index].topS1;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		genereTempsS2(index);
		
		//si la voiture a un meilleur temps pour S2 que toutes les autres, mise à jour de la variable globale
		if(voitures[index].topS2<smv[8])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[8] = voitures[index].topS2;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		genereTempsS3(index);
		
		//si la voiture a un meilleur temps pour S3 que toutes les autres, mise à jour de la variable globale
		if(voitures[index].topS3<smv[9])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[9] = voitures[index].topS3;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		//si la voiture a un meilleur temps du circuit que toutes les autres, mise à jour de la variable globale
		if(voitures[index].topCircuit<smv[10])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[10] = voitures[index].topCircuit;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		// mise à jour de l'heure actuelle de la course
		id_sem = semaph(id_sem, &semWait, 1);
		id_sem = semaph(id_sem, &semDo, 1);
		temps = getCurrTemps();
		id_sem = semaph(id_sem, &semPost, 1);
	}
	//Ici, mise à jour de la valeur de smv [3], [4] ou [5], 
	//indique au processus parent que la voiture a terminé son cycle de qualification.
	if(q==1)
	{
		id_sem = semaph(id_sem, &semWait1, 1);
		id_sem = semaph(id_sem, &semDo1, 1);
		smv[3]++;
		id_sem = semaph(id_sem, &semPost1, 1);
	}
	if(q==2)
	{
		id_sem = semaph(id_sem, &semWait1, 1);
		id_sem = semaph(id_sem, &semDo1, 1);
		smv[4]++;
		id_sem = semaph(id_sem, &semPost1, 1);
	}
	if(q==3)
	{
		id_sem = semaph(id_sem, &semWait1, 1);
		id_sem = semaph(id_sem, &semDo1, 1);
		smv[5]++;
		id_sem = semaph(id_sem, &semPost1, 1);
	}
	
}

void genereRecapQualifFile()
{
	//ecrire fichier c
	FILE *fichier = NULL;
	
	fichier = fopen("RecapQualifFile.txt", "a");
	structTuture tempo = voitures[0];
	tempo.topCircuit=10000;
	if(fichier != NULL){
		fprintf(fichier,"\n| N Voiture |     top S1    |     top S2    |     top S3    |    top Tour     |\n");
		for(int i = 0; i < 20; i++){
			if((tempo.topCircuit>voitures[i].topCircuit)&&(voitures[i].topCircuit != 0)){tempo=voitures[i];}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", voitures[i].nom,voitures[i].topS1,voitures[i].topS2,voitures[i].topS3,voitures[i].topCircuit);
		}
		fprintf(fichier,"\n The winner is the tuture number %2d with a temps of %9f s\n",tempo.nom, tempo.topCircuit);
		fclose(fichier);
	}
	else{
		printf("Ouverture du fichier recap impossible");
	}
	
	//après avoir sauvegardé les valeurs dans un fichier,
	//on les réinitialise à zéro, les voitures reprendront le prochain essai avec une table vide.
	
	for(int i=0; i<20; i++)
	{
		reset(i);
	}
}
