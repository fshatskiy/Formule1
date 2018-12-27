#include "voiture.h"
#include "utilitaire.h"
#include "practice.h"
#include <stdio.h>
#include <stdlib.h>

//Time values representing the length of the practice runs
double time1 = 5400;
double time2 = 5400;
double time3 = 3600;

void practice(int index, int p)
{
	semop(id_sem, &semWait, 1);//locking
	semop(id_sem, &semDo, 1);//taking control of the semaphore
	double time = getCurrTime();
	semop(id_sem, &semPost, 1);//unlocking
	
	double timePractice;
	//we determine the duration of the practice
	if(p==1)
	{
		timePractice = time1;
	}
	if(p==2)
	{
		timePractice = time2;
	}
	if(p==3)
	{
		timePractice = time3;
	}
	
	//we loop until the time runs out or the car is out
	while(time<timePractice && (cars[index].isOut == 0))
	{
		//as usual we lock the other process out to avoid conflicts then we make the car
		//do the first sector
		generateTimeS1(index);
		
		//if the car has a better time for S1 than all the others we update the global variable
		if(cars[index].bestS1 < smv[7])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[7] = cars[index].bestS1;
			semop(id_sem, &semPost1, 1);
		}
		
		//here, the car runs the second sector
		generateTimeS2(index);
		
		//if the car has a better time for S2 than all the others we update the global variable
		if(cars[index].bestS2 < smv[8])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[8] = cars[index].bestS2;
			semop(id_sem, &semPost1, 1);
		}
		
		//here, we make the car run the third sector
		generateTimeS3(index);
		
		//if the car has a better time for S3 than all the others we update the global variable
		if(cars[index].bestS3 < smv[9])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[9] = cars[index].bestS3;
			semop(id_sem, &semPost1, 1);
		}
		//if the car has a better time for the circuit than all the others we update
		//the global variable
		if(cars[index].bestCircuit>smv[10])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[10] = cars[index].bestCircuit;
			semop(id_sem, &semPost1, 1);
		}
		
		//we update the global current time of the race
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		time = getCurrTime();
		semop(id_sem, &semPost, 1);
	}
	
	//here we update the value of smv[0], [1] or [2], this signals to the parent process that
	//the car has finished its practice run.
	if(p==1)
	{
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[0]++;
		semop(id_sem, &semPost1, 1);
	}
	else if(p==2)
	{
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[1]++;
		semop(id_sem, &semPost1, 1);
	}
	else
	{
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[2]++;
		semop(id_sem, &semPost1, 1);
	}
}

void generateRecapFilePractice()
{
	FILE *fichier = NULL;
	
	//we're opening the file with the argument a because we want to append every practice
	//recap to that file
	fichier = fopen("RecapFilePractice.txt", "a");
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
	//after having saved the values in a file we reset them to zero, the cars will restart
	//the next practice with a clean slate
	
	for(int i=0; i<20; i++)

	{
		reset(i);
	}
}

