#include "voiture.h"
#include "utilitaire.h"

//Initialization of the car
void init(int i, int name)
{
	cars[i].name = name;    //Name of the car
	cars[i].bestCircuit=0;  //Best time on a circuit lap
	cars[i].bestS1=0;       //Best time on the first sector
	cars[i].bestS2=0;       //Best time on the second sector
	cars[i].bestS3=0;       //Best time on the third sector
	cars[i].numCircuit=0;   //Number of laps already done
	cars[i].currTime=0;     //Time elapsed since the start of the race
	cars[i].currCircuit=0;  //Current time of the race
	cars[i].inStand=0;      /*number of times it has passed the stand (between 1 and 3) */
	/*takes between 22 and 27 seconds */
	cars[i].isOut=0;        //0 if the car still run, 1 if it's crash
	
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

//reset car's scores indexed by i
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
