/*
PROJET
2018
*/
#include "utilitaire.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

//Initialisation de voitures
void init(int i, int number)
{
	cars[i].number = number;    //numéro de la voiture
	cars[i].bestCircuit=0;  //Meilleur temps du tour
	cars[i].bestS1=0;       //Meilleur temps du secteur 1
	cars[i].bestS2=0;       //Meilleur temps du secteur 2
	cars[i].bestS3=0;       //Meilleur temps du secteur 3
	cars[i].currTime=0;     //Temps pour le total de la course
	cars[i].currCircuit=0;  //Temps POUR UN TOUR
	cars[i].nbrOfStands=0;      /*nombre de fois de passage au stand (entre 1 et 3) */
	/*prend entre 22 et 27 secondes */
	cars[i].isOut=0;        //retourne 1 si crash

	if(i<10)
	{
		carsQualif2[i].number=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].nbrOfStands=0;
		carsQualif2[i].isOut=0;
		carsQualif3[i].number=0;
		carsQualif3[i].bestCircuit=0;
		carsQualif3[i].bestS1=0;
		carsQualif3[i].bestS2=0;
		carsQualif3[i].bestS3=0;
		carsQualif3[i].currTime=0;
		carsQualif3[i].currCircuit=0;
		carsQualif3[i].nbrOfStands=0;
		carsQualif3[i].isOut=0;
	}
	if(i>=10 && i< 15)
	{
		carsQualif2[i].number=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].nbrOfStands=0;
		carsQualif2[i].isOut=0;
	}
}

//initialise le score de la voiture (index i)
void reset(int i)
{
	cars[i].bestCircuit=0;
	cars[i].bestS1=0;
	cars[i].bestS2=0;
	cars[i].bestS3=0;
	cars[i].currTime=0;
	cars[i].currCircuit=0;
	cars[i].nbrOfStands=0;
	cars[i].isOut=0;
}


//RANDOM fonction
int generateRandom(int min_number, int max_number)
{
    srand(time(NULL));
	int rand_num = rand()%(max_number + 1 - min_number) + min_number;
	sleep(1);
	return rand_num;

}

//PITSTOP le temps de passage au le pitstop
int pitStop(int i)
{
	int timeStop = 0; //temps passé dedans

	// 15% de chance d'entrer dans le pitStop
	if (generateRandom(0, 99) > 84)
    {
		cars[i].nbrOfStands ++; //incrémente le nombre de pitStops pour la voiture concernée
		timeStop += (generateRandom(24, 40)/10.0);
	}

	// obligation de s'arêter au moins une fois dans le pitStop
	if (cars[i].nbrOfStands == 0 && cars[i].numCircuit == nbrLapMax)
    {
		cars[i].nbrOfStands ++; //incrémente le nombre de pitStops pour la voiture concernée
		timeStop += (generateRandom(24, 40)/10.0);
	}

	return timeStop;
}

//CRASH
void crash(int index)
{	//0 = no crash
	if (generateRandom(0, 999) > 996) // 5% chance de crash
    {
		cars[index].isOut = 1; //1=crash
	}
}

//TEMPS D'EQUART ENTRE LES VOITURES AU DEBUT DE LA COURSE
double getCurrTime()
{
	double curr = 0;
	for(int i=0; i<20; i++)
	{
		if(cars[i].currTime>curr)
		{
			curr = cars[i].currTime;
		}
	}
	return curr;
}

//AJOUTE LE TEMPS EN FONCTION DE LA POSITION
void addTimeByPosition()
{
	for (int j = 0; j < 20; j++)//j = position grille de départ
	{
		for(int i = 0; i < 20; i++)//i= index dans le tableau de voiture
		{
			if (cars[i].number == startPosition[j]){   // ajoute le temps par rapport à la position du premier
				cars[i].currTime += j * 0.3;      //  au temps général
				cars[i].currCircuit = j * 0.3;   // au temps du tour ////////////////////////////////////////effacer=>voir s'il existe autre part (norm non)
			}
		}
	}
}

//LES VOITURES DISQUALIFIEES SONT "SUPPRIMEES"
void setOut(int q)
{
	if(q==2)
	{
		for(int i=0; i<20; i++)
		{
			int j = isIn(cars[i].number, 15, carsQualif2);
			//si la voiture n'est pas dans carsQualif2, on la disqualifie
			if(j==0)
			{
				cars[i].isOut=1;
			}
		}
	}
	else
	{
		for(int i=0; i<20; i++)
		{
			int j = isIn(cars[i].number, 10, carsQualif3);
			//si la voiture n'est pas dans carsQualif3, on la disqualifie
			if(j==0)
			{
				cars[i].isOut=1;
			}
		}
	}
}
