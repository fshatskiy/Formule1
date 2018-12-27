#include "voiture.h"
#include "utilitaire.h"
#include "qualification.h"
#include <stdio.h>
#include <stdlib.h>

double timeQualif1 = 1080;//1080/60 = 18 min
double timeQualif2 = 900;//15 min
double timeQualif3 = 720;//12 min

//Tri de voitures
void sortCars(structCar carsQualif[], int sizeArrayCars)
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	//Compare les voitures entre elles (1 avec 1, 1 avec 2, etc)
	for(i=0; i < sizeArrayCars; i++)
		//Remplit le i du tableau /////////////////////////////////// ?? 
	{
		for(j = i+1; j < sizeArrayCars; j++)
			//Vérifie s'il n'y a pas de nb plus petits dans le cas suivant   PQ
		{
			if(carsQualif[j].bestCircuit < carsQualif[i].bestCircuit)
			{
				//Si vrai, switch les nombres
				tmpCar = carsQualif[i];
				carsQualif[i] = carsQualif[j];
				carsQualif[j] = tmpCar;
			}
		}
	}
}

void buildStartPosition(structCar carsQualif[], int q)
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
		startPosition[i] = carsQualif[i].name;
	}
	
	for(int i=startArray2; i < loop2; i++)
	{
		if (q == 1) {
			carsQualif2[i] = carsQualif[i];
		}
		else if (q == 2)
		{
			carsQualif3[i] = carsQualif[i];
		}
	}
}


void qualif(int index, int q)
{
	id_sem = semop(id_sem, &semWait, 1);
	id_sem = semop(id_sem, &semDo, 1);
	double time = getCurrTime();
	id_sem = semop(id_sem, &semPost, 1);
	double timeQualif = 0.0;
	
	//determine la durée de l'essai
	if(q==1)
	{
		timeQualif = timeQualif1;
	}
	if(q==2)
	{
		timeQualif = timeQualif2;
	}
	if(q==3)
	{
		timeQualif = timeQualif3;
	}
	
	//boucle jusqu'à ce que le temps soit écoulé ou que la voiture ait abandonné
	while(time<timeQualif && cars[index].isOut == 0)
	{
		generateTimeS1(index);
		
		//si la voiture a un meilleur temps pour S1 que toutes les autres, mise à jour de la variable globale
		if(cars[index].bestS1<smv[7])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[7] = cars[index].bestS1;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		generateTimeS2(index);
		
		//si la voiture a un meilleur temps pour S2 que toutes les autres, mise à jour de la variable globale
		if(cars[index].bestS2<smv[8])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[8] = cars[index].bestS2;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		generateTimeS3(index);
		
		//si la voiture a un meilleur temps pour S3 que toutes les autres, mise à jour de la variable globale
		if(cars[index].bestS3<smv[9])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[9] = cars[index].bestS3;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		//si la voiture a un meilleur temps du circuit que toutes les autres, mise à jour de la variable globale
		if(cars[index].bestCircuit<smv[10])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[10] = cars[index].bestCircuit;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		// mise à jour de l'heure actuelle de la course
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		time = getCurrTime();
		id_sem = semop(id_sem, &semPost, 1);
	}
	//Ici, mise à jour de la valeur de smv [3], [4] ou [5], 
	//indique au processus parent que la voiture a terminé son cycle de qualification.
	if(q==1)
	{
		id_sem = semop(id_sem, &semWait1, 1);
		id_sem = semop(id_sem, &semDo1, 1);
		smv[3]++;
		id_sem = semop(id_sem, &semPost1, 1);
	}
	if(q==2)
	{
		id_sem = semop(id_sem, &semWait1, 1);
		id_sem = semop(id_sem, &semDo1, 1);
		smv[4]++;
		id_sem = semop(id_sem, &semPost1, 1);
	}
	if(q==3)
	{
		id_sem = semop(id_sem, &semWait1, 1);
		id_sem = semop(id_sem, &semDo1, 1);
		smv[5]++;
		id_sem = semop(id_sem, &semPost1, 1);
	}
	
}

void generateRecapFileQualif()
{
	//ecrire fichier c
	FILE *fichier = NULL;
	
	fichier = fopen("RecapFileQualif.txt", "a");
	structCar temp = cars[0];
	temp.bestCircuit=10000;
	if(fichier != NULL){
		fprintf(fichier,"\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |\n");
		for(int i = 0; i < 20; i++){
			if((temp.bestCircuit>cars[i].bestCircuit)&&(cars[i].bestCircuit != 0)){temp=cars[i];}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit);
		}
		fprintf(fichier,"\n The winner is the car number %2d with a time of %9f s\n",temp.name, temp.bestCircuit);
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
