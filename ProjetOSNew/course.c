#include "voiture.h"
#include "utilitaire.h"
#include "course.h"
#include <stdio.h>
#include <stdlib.h>


void sortCarsByCurrTime(structCar carsRace[])
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	
	for(i=0; i < 20; i++)
		//Remplis les cases i du tableau
	{
		for(j = i+1; j < 20; j++)
			//verifie si il y a pas de numéro plus petit dans les case suivantes
		{
			if(carsRace[j].numCircuit == carsRace[i].numCircuit && carsRace[j].currTime < carsRace[i].currTime)
			{
				//Si c'est vrai, echange le numero
				tmpCar = carsRace[i];
				carsRace[i] = carsRace[j];
				carsRace[j] = tmpCar;
			}
			else if(carsRace[j].numCircuit > carsRace[i].numCircuit)
			{
				//Sinon si c'st plus petit, echange le numero 
				tmpCar = carsRace[i];
				carsRace[i] = carsRace[j];
				carsRace[j] = tmpCar;
				
			}
		}
	}
}

void race(int index)
{
	id_sem = semop(id_sem, &semWait, 1);
	id_sem = semop(id_sem, &semDo, 1);
	id_sem = semop(id_sem, &semPost, 1);
	
	while(cars[index].isOut == 0 && cars[index].numCircuit < nbrLapMax)
	{
		generateTimeS1(index);
		if(cars[index].bestS1<smv[7])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[7] = cars[index].bestS1;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		generateTimeS2(index);
		if(cars[index].bestS2<smv[8])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[8] = cars[index].bestS2;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		generateTimeS3(index);
		if(cars[index].bestS3<smv[9])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[9] = cars[index].bestS3;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		if(cars[index].bestCircuit<smv[10])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[10] = cars[index].bestCircuit;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		id_sem = semop(id_sem, &semPost, 1);
		
		if(cars[index].isOut == 0)
		{
			cars[index].numCircuit++; //Incremente le nombre du circuit déjà terminé
		}
	}
	
	id_sem = semop(id_sem, &semWait1, 1);
	id_sem = semop(id_sem, &semDo1, 1);
	smv[6]++;
	id_sem = semop(id_sem, &semPost1, 1);
	
}

void generateRecapFileRace()
{
	//ecrit le fichier 
	FILE *file = NULL;
	
	file = fopen("RecapFileRace.txt", "a"); // ouvre le fichier RecapFileRace.txt et ecrit dedans ?
	structCar temp = cars[0]; 
	temp.currTime=10000; 
	if(file != NULL){ // si le fichier n'est pas egal à null
		fprintf(file,"\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n"); //affiche ce qu'il y a après le \n 
		for(int i = 0; i < 20; i++){ // boucle : int i est égal à 0 , tant que i est inferieur à 20 , i+1
			if((temp.currTime>cars[i].currTime)&&(cars[i].currTime != 0)){temp=cars[i];}
			fprintf(file,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit,cars[i].currTime);
		}
		fprintf(file,"\n The winner is the car number %2d with a time of %9f s\n",temp.name, temp.currTime);
		fclose(file); // fermeture de fichier 
	}
	else{ //Sinon
		printf("Ouverture du fichier recap impossible"); //Affiche ce msg d'erreur
	}
	//après avoir sauver les valeurs (résultats) dans un fichier on remet toutes les valeurs à zéro à l'aide du reset
	// et les voiture vont repartir
	//(l'entrainement suivant (le practice suivant) avec une ardouase propre
	
	for(int i=0; i<20; i++)
	{
		reset(i); //boucle : int i est égal à 0 , tant que i est inferieur à 20 , i+1
	}
}
