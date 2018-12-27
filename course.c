#include "voiture.h"
#include "utilitaire.h"
#include "course.h"
#include <stdio.h>
#include <stdlib.h>


void sortVoituresByCurrTemps(structTuture voituresCourse[])
{
	int i=0;
	structTuture tmpTuture;
	int j = 0;
	
	for(i=0; i < 20; i++)
		//Remplis les cases i du tableau
	{
		for(j = i+1; j < 20; j++)
			//verifie si il y a pas de numéro plus petit dans les case suivantes
		{
			if(voituresCourse[j].numCircuit == voituresCourse[i].numCircuit && voituresCourse[j].currTemps < voituresCourse[i].currTemps)
			{
				//Si c'est vrai, echange le numero
				tmpTuture = voituresCourse[i];
				voituresCourse[i] = voituresCourse[j];
				voituresCourse[j] = tmpTuture;
			}
			else if(voituresCourse[j].numCircuit > voituresCourse[i].numCircuit)
			{
				//Sinon si c'st plus petit, echange le numero 
				tmpTuture = voituresCourse[i];
				voituresCourse[i] = voituresCourse[j];
				voituresCourse[j] = tmpTuture;
				
			}
		}
	}
}

void course(int index)
{
	id_sem = semaph(id_sem, &semWait, 1);
	id_sem = semaph(id_sem, &semDo, 1);
	id_sem = semaph(id_sem, &semPost, 1);
	
	while(voitures[index].isOut == 0 && voitures[index].numCircuit < nbrLapMax)
	{
		genereTempsS1(index);
		if(voitures[index].topS1<smv[7])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[7] = voitures[index].topS1;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		genereTempsS2(index);
		if(voitures[index].topS2<smv[8])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[8] = voitures[index].topS2;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		genereTempsS3(index);
		if(voitures[index].topS3<smv[9])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[9] = voitures[index].topS3;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		if(voitures[index].topCircuit<smv[10])
		{
			id_sem = semaph(id_sem, &semWait1, 1);
			id_sem = semaph(id_sem, &semDo1, 1);
			smv[10] = voitures[index].topCircuit;
			id_sem = semaph(id_sem, &semPost1, 1);
		}
		id_sem = semaph(id_sem, &semWait, 1);
		id_sem = semaph(id_sem, &semDo, 1);
		id_sem = semaph(id_sem, &semPost, 1);
		
		if(voitures[index].isOut == 0)
		{
			voitures[index].numCircuit++; //Incremente le nombre du circuit déjà terminé
		}
	}
	
	id_sem = semaph(id_sem, &semWait1, 1);
	id_sem = semaph(id_sem, &semDo1, 1);
	smv[6]++;
	id_sem = semaph(id_sem, &semPost1, 1);
	
}

void genereRecapCourseFile()
{
	//ecrit le fichier 
	FILE *file = NULL;
	
	file = fopen("RecapFileCourse.txt", "a"); // ouvre le fichier RecapFileCourse.txt et ecrit dedans ?
	structTuture tempo = voitures[0]; 
	tempo.currTemps=10000; 
	if(file != NULL){ // si le fichier n'est pas egal à null
		fprintf(file,"\n| N Voiture |     top S1    |     top S2    |     top S3    |    top Tour     |    Global temps   |\n"); //affiche ce qu'il y a après le \n 
		for(int i = 0; i < 20; i++){ // boucle : int i est égal à 0 , tant que i est inferieur à 20 , i+1
			if((tempo.currTemps>voitures[i].currTemps)&&(voitures[i].currTemps != 0)){tempo=voitures[i];}
			fprintf(file,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", voitures[i].nom,voitures[i].topS1,voitures[i].topS2,voitures[i].topS3,voitures[i].topCircuit,voitures[i].currTemps);
		}
		fprintf(file,"\n The winner is the tuture number %2d with a temps of %9f s\n",tempo.nom, tempo.currTemps);
		fclose(file); // fermeture de fichier 
	}
	else{ //Sinon
		printf("Ouverture du fichier recap impossible"); //Affiche ce msg d'erreur
	}
	//après avoir sauver les valeurs (résultats) dans un fichier on remet toutes les valeurs à zéro à l'aide du reset
	// et les voiture vont repartir
	//(l'entrainement suivant (le entrainement suivant) avec une ardouase propre
	
	for(int i=0; i<20; i++)
	{
		reset(i); //boucle : int i est égal à 0 , tant que i est inferieur à 20 , i+1
	}
}
