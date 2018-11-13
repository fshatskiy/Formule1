#include "utilitaire.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>

void init(int i, int number)
{
	cars[i].number = number;    //Number of the car
	cars[i].bestCircuit=0;  //Best time on a circuit lap
	cars[i].bestS1=0;       //Best time on the first sector
	cars[i].bestS2=0;       //Best time on the second sector
	cars[i].bestS3=0;       //Best time on the third sector
	//cars[i].numCircuit=0;   //Number of laps already done
	cars[i].currTime=0;     //Time elapsed since the start of the race
	cars[i].currCircuit=0;  //Current time of the race
	cars[i].standTime=0;      /*number of times it has passed the stand (between 1 and 3) */
	/*takes between 22 and 27 seconds */
	cars[i].isOut=0;        //0 if the car still run, 1 if it's crash

	if(i<10)
	{
		carsQualif2[i].number=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		//carsQualif2[i].numCircuit=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].standTime=0;
		carsQualif2[i].isOut=0;
		carsQualif3[i].number=0;
		carsQualif3[i].bestCircuit=0;
		carsQualif3[i].bestS1=0;
		carsQualif3[i].bestS2=0;
		carsQualif3[i].bestS3=0;
		//carsQualif3[i].numCircuit=0;
		carsQualif3[i].currTime=0;
		carsQualif3[i].currCircuit=0;
		carsQualif3[i].standTime=0;
		carsQualif3[i].isOut=0;
	}
	if(i>=10 && i< 15)
	{
		carsQualif2[i].number=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		//carsQualif2[i].numCircuit=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].standTime=0;
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
	//cars[i].numCircuit=0;
	cars[i].currTime=0;
	cars[i].currCircuit=0;
	cars[i].standTime=0;
	cars[i].isOut=0;
}


//RANDOM
int generateRandom(int min_number, int max_number)
{
    srand(time(NULL));
	int rand_num = rand()%(max_number + 1 - min_number) + min_number;
	sleep(1);
	return rand_num;

}

//PITSTOP
int pitStop(int i)
{
	int timeStop = 0; //time spent at the pit

	// 15% chance of a pit stop
	if (generateRandom(0, 99) > 84)
    {
		cars[i].standTime ++; //increment the pit stop number for the specified car
		timeStop += (generateRandom(24, 40)/10.0);
	}

	// obligation to stop at the pit at least one time during the race
	if (cars[i].standTime == 0 && cars[i].numCircuit == nbrLapMax)
    {
		cars[i].standTime ++; //Increment the number of the pit stop for the specified car
		timeStop += (generateRandom(24, 40)/10.0);
	}

	return timeStop;
}

//CRASH
void crash(int index)
{	//0 = no crash
	if (generateRandom(0, 999) > 996) // 5% chance of crash
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
	for (int j = 0; j < 20; j++)
	{
		for(int i = 0; i < 20; i++)
		{
			if (cars[i].name == startPosition[j]){   // add time by position compared to the first
				cars[i].currTime += j * 0.3;      //  to general time
				cars[i].currCircuit = j * 0.3;   // to time on a lap
			}
		}
	}
}

//LES VOITURES DISQUALIFIE SONT "SUPPRIMER"
void setOut(int q)
{
	if(q==2)
	{
		for(int i=0; i<20; i++)
		{
			int j = isIn(cars[i].name, 15, carsQualif2);
			//if the car isn't in carsQuelif2, we disqualify it
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
			int j = isIn(cars[i].name, 10, carsQualif3);
			//if the car isn't in carsQuelif3, we disqualify it
			if(j==0)
			{
				cars[i].isOut=1;
			}
		}
	}
}
