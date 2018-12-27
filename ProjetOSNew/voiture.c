#include "voiture.h"
#include "utilitaire.h"

//Initialisation des voitures
void init(int i, int name)
{
	cars[i].name = name;    //Nom de la voiture
	cars[i].bestCircuit=0;  //Meilleur temps sur un tour de circuit
	cars[i].bestS1=0;       //Meilleur temps sur le premier secteur
	cars[i].bestS2=0;       //Meilleur temps sur le deuxieme secteur
	cars[i].bestS3=0;       //Meilleur temps sur le troisieme secteur
	cars[i].numCircuit=0;   //Nombre de tours déjà effectués
	cars[i].currTime=0;     //Temps écoulé depuis le début de la course
	cars[i].currCircuit=0;  //Heure actuelle de la course
	cars[i].inStand=0;      /*nombre de fois qu'il a passé le stand (entre 1 et 3) */
	/*prend entre 22 et 27 secondes */
	cars[i].isOut=0;        //0 si la voiture continue de rouler, 1 si elle s'écrase
	
	if(i<10)
	{
		carsQualif2[i].name=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		carsQualif2[i].numCircuit=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].inStand=0;
		carsQualif2[i].isOut=0;
		carsQualif3[i].name=0;
		carsQualif3[i].bestCircuit=0;
		carsQualif3[i].bestS1=0;
		carsQualif3[i].bestS2=0;
		carsQualif3[i].bestS3=0;
		carsQualif3[i].numCircuit=0;
		carsQualif3[i].currTime=0;
		carsQualif3[i].currCircuit=0;
		carsQualif3[i].inStand=0;
		carsQualif3[i].isOut=0;
	}
	if(i>=10 && i< 15)
	{
		carsQualif2[i].name=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		carsQualif2[i].numCircuit=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].inStand=0;
		carsQualif2[i].isOut=0;
	}
}

//réinitialiser les scores de la voiture indexés par i
void reset(int i)
{
	cars[i].bestCircuit=0;
	cars[i].bestS1=0;
	cars[i].bestS2=0;
	cars[i].bestS3=0;
	cars[i].numCircuit=0;
	cars[i].currTime=0;
	cars[i].currCircuit=0;
	cars[i].inStand=0;
	cars[i].isOut=0;
}
