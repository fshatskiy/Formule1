/*
PROJET
2018
*/
#include "utilitaire.h"
#include "qualif.h"
#include <stdio.h>
#include <stdlib.h>



double timeQualif1 = 1080; //??????????????
double timeQualif2 = 900;
double timeQualif3 = 720;

//Tri de voitures
void sortCars(structCar carsQualif[], int sizeArrayCars)
{
	int i=0;
	structCar tmpCar;
	int j = 0;
    //Compare les voitures entre elles (1 avec 1, 1 avec 2, etc)
	for(i=0; i < sizeArrayCars; i++)
	{
		for(j = i+1; j < sizeArrayCars; j++)
			//Check if there are not smaller number in the next cases
		{
			if(carsQualif[j].bestCircuit < carsQualif[i].bestCircuit)
			{
				//If it's true, swap number
				tmpCar = carsQualif[i];
				carsQualif[i] = carsQualif[j];
				carsQualif[j] = tmpCar;
			}
		}
	}
}
