#include "voiture.h"
#include "utilitaire.h"

//Initialisation des voitures
void init(int i, int nom)
{
	voitures[i].nom = nom;    //Nom de la voiture
	voitures[i].topCircuit=0;  //Meilleur temps sur un tour de circuit
	voitures[i].topS1=0;       //Meilleur temps sur le premier secteur
	voitures[i].topS2=0;       //Meilleur temps sur le deuxieme secteur
	voitures[i].topS3=0;       //Meilleur temps sur le troisieme secteur
	voitures[i].numCircuit=0;   //Nombre de tours déjà effectués
	voitures[i].currTemps=0;     //Temps écoulé depuis le début de la course
	voitures[i].currCircuit=0;  //Heure actuelle de la course
	voitures[i].inStand=0;      /*nombre de fois qu'il a passé le stand (entre 1 et 3) */
	/*prend entre 22 et 27 secondes */
	voitures[i].isOut=0;        //0 si la voiture continue de rouler, 1 si elle s'écrase
	
	if(i<10)
	{
		voituresQualif2[i].nom=0;
		voituresQualif2[i].topCircuit=0;
		voituresQualif2[i].topS1=0;
		voituresQualif2[i].topS2=0;
		voituresQualif2[i].topS3=0;
		voituresQualif2[i].numCircuit=0;
		voituresQualif2[i].currTemps=0;
		voituresQualif2[i].currCircuit=0;
		voituresQualif2[i].inStand=0;
		voituresQualif2[i].isOut=0;
		voituresQualif3[i].nom=0;
		voituresQualif3[i].topCircuit=0;
		voituresQualif3[i].topS1=0;
		voituresQualif3[i].topS2=0;
		voituresQualif3[i].topS3=0;
		voituresQualif3[i].numCircuit=0;
		voituresQualif3[i].currTemps=0;
		voituresQualif3[i].currCircuit=0;
		voituresQualif3[i].inStand=0;
		voituresQualif3[i].isOut=0;
	}
	if(i>=10 && i< 15)
	{
		voituresQualif2[i].nom=0;
		voituresQualif2[i].topCircuit=0;
		voituresQualif2[i].topS1=0;
		voituresQualif2[i].topS2=0;
		voituresQualif2[i].topS3=0;
		voituresQualif2[i].numCircuit=0;
		voituresQualif2[i].currTemps=0;
		voituresQualif2[i].currCircuit=0;
		voituresQualif2[i].inStand=0;
		voituresQualif2[i].isOut=0;
	}
}

//réinitialiser les scores de la voiture indexés par i
void reset(int i)
{
	voitures[i].topCircuit=0;
	voitures[i].topS1=0;
	voitures[i].topS2=0;
	voitures[i].topS3=0;
	voitures[i].numCircuit=0;
	voitures[i].currTemps=0;
	voitures[i].currCircuit=0;
	voitures[i].inStand=0;
	voitures[i].isOut=0;
}
