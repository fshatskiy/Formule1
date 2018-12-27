#include "utilitaire.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>


//indicates that the semaphore value is expected to be 0
struct sembuf semWait = {0,0,SEM_UNDO};

//increments the semaphore value to block it
struct sembuf semDo = {0,1,SEM_UNDO|IPC_NOWAIT};

//decrements the semaphore value to unblock it
struct sembuf semPost = {0,-1,SEM_UNDO|IPC_NOWAIT};

//indicates that the semaphore value is expected to be 0
struct sembuf semWait1 = {1,0,SEM_UNDO};

//increments the semaphore value to block it
struct sembuf semDo1 = {1,1,SEM_UNDO|IPC_NOWAIT};

//decrements the semaphore value to unblock it
struct sembuf semPost1 = {1,-1,SEM_UNDO|IPC_NOWAIT};

//indicates that the semaphore value is expected to be 0
struct sembuf semWait2 = {2,0,SEM_UNDO};

//increments the semaphore value to block it
struct sembuf semDo2 = {2,1,SEM_UNDO|IPC_NOWAIT};

//decrements the semaphore value to unblock it
struct sembuf semPost2 = {2,-1,SEM_UNDO|IPC_NOWAIT};

//variable use to transfer hours in second
double transfHourInSec = 3600;


int generateRandom(int min_number, int max_number){
	int rand_num = rand()%(max_number + 1 - min_number) + min_number;
	return rand_num;
}

int pitStop(int i) {
	int timeStop = 0; //time spent at the pit
	
	// 15% chance of a pit stop
	if (generateRandom(0, 99) > 84) {
		cars[i].inStand ++; //increment the pit stop number for the specified car
		timeStop += (generateRandom(24, 40)/10.0);
	}
	
	// obligation to stop at the pit at least one time during the race
	if (cars[i].inStand == 0 && cars[i].numCircuit == nbrLapMax){
		cars[i].inStand ++; //Increment the number of the pit stop for the specified car
		timeStop += (generateRandom(24, 40)/10.0);
	}
	
	return timeStop;
}

void crash(int index)
{	//0 = no crash
	if (generateRandom(0, 999) > 998) { // 3% chance of crash
		cars[index].isOut = 1; //1=crash
	}
}

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

int nbrLaps(int km)
{
	int nbr = 70;			// The default number of laps
	int lengthMinRace = 305;	// Minimal length for a race
	if(km == 0)  //if the user doesn't enter a parameter for the kilometers
	{
		return nbr;
	}
	if(lengthMinRace % km == 0)
	{
		nbr = lengthMinRace/km;
	}
	else
	{
		nbr = 1 + (lengthMinRace/km);
	}
	return nbr;
}

int indexOf(int i, int length, int t[])
{
	for(int j=0; j<length; j++)
	{
		if(i==t[j])
		{
			return j;
		}
	}
	//if the pid isn't in the tab, we return the length of the tab to enable error detection
	return length;
}

int isIn(int name, int length, structCar t[])
{
	int k=0;
	for(int j=0; j<length; j++)
	{
		if(name==t[j].name)
		{
			k=1;
			break;
		}
	}
	return k;
}

void generateTimeS1(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.28; // Sector length as a percentage of the overall length of the circuit
	double time;
	
	if(!(isRace == 1 && cars[i].numCircuit == 0)){
		cars[i].currCircuit = 0.0;  //reset value of the time for the current lap
	}
	
	double averageSpeed = (double)(generateRandom(3450, 3750)/10); //generation of the average speed of the car
	
	crash(i); //call function to see if the car crashes
	
	if(cars[i].isOut == 0){
		time = lengthPercent*lengthCircuit /(averageSpeed/transfHourInSec); // computation of the time performance of the car in seconds for this sector
		
		// Adding time to current circuit time and overall time since that part of the race started up
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Modification of the best time for sector 1 if the new one is better
		if(cars[i].bestS1 < 1 || time < cars[i].bestS1){
			cars[i].bestS1 = time;
		}
	}
	semop(id_sem, &semPost, 1);
	//	printf("1 %d", i);
	//	sleep(1);
}

void generateTimeS2(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.33; // Sector length as a percentage of the overall length of the circuit
	double time;
	
	double averageSpeed = (double)(generateRandom(3000, 3640)/10); //generation of the average speed of the car
	
	crash(i); //call function to see if car crash
	
	if(cars[i].isOut == 0){
		time = lengthPercent * lengthCircuit / ( averageSpeed / transfHourInSec ); // computation of the time performance of the car in seconds for this sector
		
		// Adding time to current circuit time and overall time since that part of the race started up
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Modification of the best time for sector 2 if the new one is better
		if(cars[i].bestS2 < 1 || time < cars[i].bestS2){
			cars[i].bestS2 = time;
		}
	}
	semop(id_sem, &semPost, 1);
	//	printf("2 %d", i);
	//	sleep(1);
}

void generateTimeS3(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.39; // Sector length as a percentage of the overall length of the circuit
	double time;
	
	double averageSpeed = (double)(generateRandom(3200, 3550)/10); //generation of the average speed of the car
	
	crash(i); //call function to see if car crash
	
	if(cars[i].isOut == 0){
		time = lengthPercent * lengthCircuit / ( averageSpeed / transfHourInSec ); // computation of the time performance of the car in seconds for this sector
		time += (double)pitStop(i); // addition of the pit stop
		
		// Adding time to current circuit time and overall time since that part of the race started up
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Modification of the best time for sector 3 if the new one is better
		if(cars[i].bestS3 < 1 || time < cars[i].bestS3){
			cars[i].bestS3 = time;
		}
		
		// Modification of the best time for the circuit if the new one is better
		if(cars[i].bestCircuit < 1 || cars[i].currCircuit < cars[i].bestCircuit){
			cars[i].bestCircuit= cars[i].currCircuit;
		}
	}
	semop(id_sem, &semPost, 1);
	//	printf("3 %d", i);
	sleep(1);
}

char askAction()
{
	char c;
	char s[100];
	do
	{
		puts("What do you want to do?");
		puts("[C]ontinue or [S]top?");
		
		if (fgets(s, 100, stdin) == NULL)
		{
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}
		
		sscanf(s, "%c", &c);
		c = tolower(c);
	} while (c != 'c'
			 && c != 's');
	
	return c;
}

void interaction(int i)
{
	char c = askAction();
	if(c=='c')
	{
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[i]=0;
		semop(id_sem, &semPost1, 1);
	}
	else
	{
		killChildren();
		exit(0);
	}
}

void killChildren()
{
	for(int i=1; i<21; i++)
	{
		//send signal to kill the process with pid = pidList[i]
		kill(pidList[i], SIGKILL);
	}
}

void wakeChildren()
{
	for(int i=1; i<21; i++)
	{
		//send signal to wake the process with pid = pidList[i]
		kill(pidList[i], SIGCONT);
	}
}


void sortRace(structCar carsQualif[], int sizeArrayCars)
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	
	for(i=0; i < sizeArrayCars; i++)
		//Fill the case i of the array
	{
		for(j = i+1; j < sizeArrayCars; j++)
			//Check if there are not smaller number in the next cases
		{
			if((carsQualif[j].currTime < carsQualif[i].currTime)&&(carsQualif[j].isOut==0))
			{
				//If it's true, swap number
				tmpCar = carsQualif[i];
				carsQualif[i] = carsQualif[j];
				carsQualif[j] = tmpCar;
			}
		}
	}
}

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

