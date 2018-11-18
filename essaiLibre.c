/*
PROJET
2018
*/
#include <essaiLibre.h>
#include <utilitaire.h>
#include <stdio.h>
#include <stdlib.h>


//+fonction PRACTICE voir

//
void generateRecapFileEssai()//generateRecapFilePractice
{
	FILE *fichier = NULL;

	//we're opening the file with the argument a because we want to append every practice                 //traduire
	//recap to that file
	fichier = fopen("RecapFilePractice.txt", "a"); //cree le fichier et l ouvre
	structCar temp = cars[0];
	temp.bestCircuit=10000;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(fichier != NULL){

		fprintf(fichier,"\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |\n");

		for(int i = 0; i < 20; i++){
			if((temp.bestCircuit>cars[i].bestCircuit)&&(cars[i].bestCircuit != 0)){
				temp=cars[i];
			}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", 						cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit);
		}

		fprintf(fichier,"\n The winner is the car number %2d with a time of %9f s\n",temp.name, temp.bestCircuit);
		fclose(fichier);
	}
	else{
		printf("Ouverture du fichier recap impossible");
	}
	//Après avoir sauvegardé les valeurs dans le fichier, on les initialise, les voitures vont redémarrer 
	//l'essai suivant avec un nouvel état

	for(int i=0; i<20; i++)
	{
		reset(i);
	}
}
