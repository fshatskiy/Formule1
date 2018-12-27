#include "voiture.h"
#include "utilitaire.h"
#include "practice.h"
#include "qualification.h"
#include "race.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>


int myGlobalStaticContinueVariable;

void handleSignal(int sig) {
	myGlobalStaticContinueVariable = 1;
}

void worker(int nprocesses)
{
	int pid;
	isRace = 0;
	if(getpid()==pidList[0] && nprocesses==0) //=>parent process after all the forks are done
	{
		
		//start of practice 1
		//the parent process sleeps until all the children have finished the practice
		structCar temp[20];
		while(smv[0]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nPractice 1 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//here, the cars have all finished the practice so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//ask user if he wants to continue : if yes smv[0]=0 if not kill all children
		//and exit program
		interaction(0);
		
		//start of practice 2
		wakeChildren();
		//the parent process sleeps until all the children have finished the practice
		while(smv[1]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nPractice 2 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//here, the cars have all finished the practice so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//ask user if he wants to continue : if yes smv[1]=0 if not kill all children
		//and exit program
		interaction(1);
		
		
		//start of practice 3
		wakeChildren();
		//the parent process sleeps until all the children have finished the practice
		while(smv[2]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nPractice 3 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//here, the cars have all finished the practice so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//ask user if he wants to continue : if yes smv[2]=0 if not kill all children
		//and exit program
		interaction(2);
		
		//start of qualif 1
		wakeChildren();
		//the parent process sleeps until all the children have finished the practice
		while(smv[3]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nQualification 1 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		//creating a temporary variable that holds car, sorting it and building the starting list
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		for(int i =0; i<20; i++)
		{
			temp[i]=cars[i];
		}
		id_sem = semop(id_sem, &semPost, 1);
		
		sortCars(temp, 20);
		buildStartPosition(temp, 1);
		
		//here, the cars have all finished the qualif so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//We're eliminating the cars that haven't been fast enough
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		setOut(2);
		id_sem = semop(id_sem, &semPost, 1);
		
		//ask user if he wants to continue : if yes smv[3]=0 if not kill all children
		//and exit program
		interaction(3);
		
		//start of qualif 2
		wakeChildren();
		//the parent process sleeps until all the children have finished the practice
		while(smv[4]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<15; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nQualification 2 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		//building starting list
		sortCars(carsQualif2, 15);
		buildStartPosition(carsQualif2, 2);
		
		//here, the cars have all finished the qualif so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//eliminating slowest cars
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		setOut(3);
		id_sem = semop(id_sem, &semPost, 1);
		
		//ask user if he wants to continue : if yes smv[4]=0 if not kill all children
		//and exit program
		interaction(4);
		//start of qualif 3
		wakeChildren();
		//the parent process sleeps until all the children have finished the practice
		while(smv[5]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nQualification 3 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit,cars[i].currTime);
			}
			sleep(1);
		}
		//building starting list
		sortCars(carsQualif3, 10);
		buildStartPosition(carsQualif3, 3);
		
		//here, the cars have all finished the qualif so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//ask user if he wants to continue : if yes smv[5]=0 if not kill all children
		//and exit program
		interaction(5);
		//start of race
		wakeChildren();
		//here we add time to cars with regard to startPosition
		addTimeByPosition();
		isRace = 1;
		//the parent process sleeps until all the children have finished the practice
		while(smv[6]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCarsByCurrTime(temp);
			printf("\n\n\n\n\n RACE\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//here, the cars have all finished the race so we generate the recap file.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileRace();
		semop(id_sem, &semPost, 1);
		
		printf("\n\nThe race is over, we hope you've enjoyed yourselves !\n");
		
	}
	
	
	if(nprocesses > 0) //all the forks aren't done yet
	{
		if ((pid = fork()) < 0)
		{
			perror("fork\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)//=>start of the child process
		{
			signal(SIGCONT, handleSignal);
			//the child process sleep for a second to allow the parent process to finish forking
			//that time delay was determined experimentally
			sleep(1);
			
			//start of practice 1
			int index;
			
			//We determine which car belongs to which process
			semop(id_sem, &semWait2, 1);
			semop(id_sem, &semDo2, 1);
			index = indexOf(getpid(), 21, pidList);//index-1 = index of the car
			semop(id_sem, &semPost2, 1);
			
			//here we plant the seed for the random generator so each process has a different one
			srand(time(NULL)+getpid());
			
			if(index==21 || index==0)
			{
				//launch error
				perror("pid not in pidList\n");
				exit(EXIT_FAILURE);
			}
			practice(index-1, 1);
			//waits for the others to finish and for the parent process to finish printing the
			//recap file
			while(smv[0]!=0)
			{
				sleep(1);
			}
			
			//start of practice 2
			practice(index-1, 2);
			//waits for the others to finish and for the parent process to finish printing the
			//recap file
			while(smv[1]!=0)
			{
				sleep(1);
			}
			
			//start of practice 3
			practice(index-1, 3);
			//waits for the others to finish and for the parent process to finish printing the
			//recap file
			while(smv[2]!=0)
			{
				sleep(1);
			}
			
			//start of qualif 1
			qualif(index-1, 1);
			//waits for the others to finish and for the parent process to finish printing the
			//recap file
			while(smv[3]!=0)
			{
				sleep(1);
			}
			
			//start of qualif 2
			qualif(index-1, 2);
			//waits for the others to finish and for the parent process to finish printing the
			//recap file
			while(smv[4]!=0)
			{
				sleep(1);
			}
			
			//start of qualif 3
			qualif(index-1, 3);
			//waits for the others to finish and for the parent process to finish printing the
			//recap file
			while(smv[5]!=0)
			{
				sleep(1);
			}
			
			//start of race
			race(index-1);
			
			//exit the process after everything is done
			exit(0);
			
		}
		else if(pid > 0)//=>parent process while the forks aren't all done
		{
			//save the pid of the child that was just created in the pidList then calls
			//worker with a decreased number to fork the next child
			semop(id_sem, &semWait2, 1);
			semop(id_sem, &semDo2, 1);
			pidList[21-nprocesses]=pid;
			semop(id_sem, &semPost2, 1);
			worker(nprocesses - 1);
			
		}
	}
}

int main(int argc, char *argv[])
{
	int key = 123;//shared memory key
	int key1 = 789;//second shared memory key
	int key2 = 999;//third shared memory key
	int key3 = 888;//fourth shared memory key
	int key4 = 777;//fifth shared memory key
	int keyS = 456;//semaphore key
	//	struct timeval temps_avant, temps_apres; those are the structures we used to determine
	//	the time delay needed to allow the parent process to fork all its children
	
	//creation of the semaphore
	if ((id_sem = semget(keyS, 3, IPC_CREAT|0666)) == -1) {
		perror("semget: semget failed");
		exit(1);
	}
	
	//temporary variables that we used to determine the size needed in shared memory
	structCar temp[20];
	structCar temp3[15];
	structCar temp4[10];
	int temp1[7];
	int temp2[21];
	
	//creation of the shared memory needed (1 for the cars, 1 for the variables needed
	//and 1 for the pidList)
	int id_shm = shmget(key, sizeof(temp), IPC_CREAT|0666); //autorisation 0666??
	int id_shm1 = shmget(key1, sizeof(temp1), IPC_CREAT|0666);
	int id_shm2 = shmget(key2, sizeof(temp2), IPC_CREAT|0666);
	int id_shm3 = shmget(key3, sizeof(temp3), IPC_CREAT|0666);
	int id_shm4 = shmget(key4, sizeof(temp4), IPC_CREAT|0666);
	if(id_shm==-1 || id_shm1==-1 || id_shm2==-1 || id_shm3==-1 || id_shm4==-1)
	{
		printf("error");
		exit(EXIT_FAILURE);
	}
	
	//Here we begin the interaction with the user by asking him the length of the lap
	int km;
	char s[100];
	puts("Welcome to this weekend Formula One GP!");
	do
	{
		puts("Enter here the length of a lap in kilometers");
		puts("This number must be between 1 and 7");
		
		if (fgets(s, 100, stdin) == NULL)
		{
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}
		
		sscanf(s, "%d", &km);
	} while (km<1||km>7);
	lengthCircuit = km;
	nbrLapMax = nbrLaps(lengthCircuit);
	
	//attaching the shared memory
	cars = shmat(id_shm, NULL, SHM_W);
	smv = shmat(id_shm1, NULL, SHM_W);
	pidList = shmat(id_shm2, NULL, SHM_W);
	carsQualif2 = shmat(id_shm3, NULL, SHM_W);
	carsQualif3 = shmat(id_shm4, NULL, SHM_W);
	
	//here we initiliaze the cars
	int c[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
	for(int i=0; i<20; i++)
	{
		//locking semaphore
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		init(i,c[i]);
		semop(id_sem, & semPost, 1);
		startPosition[i]=0;
		//unlocking semaphore
	}
	
	//here we initialize the "global" variables
	semop(id_sem, &semWait1, 1);
	semop(id_sem, &semDo1, 1);
	smv[0]=0; //p1
	smv[1]=0; //p2
	smv[2]=0; //p3
	smv[3]=0; //q1
	smv[4]=0; //q2
	smv[5]=0; //q3
	smv[6]=0; //r
	smv[7]=0; //bestS1
	smv[8]=0; //bestS2
	smv[9]=0; //bestS3
	smv[10]=0; //bestTour
	semop(id_sem, &semPost1, 1);
	
	//here we initialize the pidList (values = -1 to allow error detection later on)
	semop(id_sem, &semWait2, 1);
	semop(id_sem, &semDo2, 1);
	pidList[0]=getpid();
	pidList[1]=-1;
	pidList[2]=-1;
	pidList[3]=-1;
	pidList[4]=-1;
	pidList[5]=-1;
	pidList[6]=-1;
	pidList[7]=-1;
	pidList[8]=-1;
	pidList[9]=-1;
	pidList[10]=-1;
	pidList[11]=-1;
	pidList[12]=-1;
	pidList[13]=-1;
	pidList[14]=-1;
	pidList[15]=-1;
	pidList[16]=-1;
	pidList[17]=-1;
	pidList[18]=-1;
	pidList[19]=-1;
	pidList[20]=-1;
	semop(id_sem, &semPost2, 1);
	
	//	gettimeofday (&temps_avant, NULL);
	//	printf("parent pid %d\n", getpid()); those lines were needed to compute the time delay
	//	mentionned earlier
	worker(20);
	
	//	gettimeofday (&temps_apres, NULL);
	//	printf("temps en us: %ld us pid %d\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 +
	//	temps_apres.tv_usec) - temps_avant.tv_usec, getpid()); those lines were needed to compute the
	//	time delay mentionned earlier
	
	//here we detach the shared memory segments and we delete the semaphores
	if((shmdt(cars))==-1)
	{
		perror("shmdt foireux a");
	}
	
	if((shmdt(smv))==-1)
	{
		perror("shmdt foireux 2");
	}
	if((shmdt(pidList))==-1)
	{
		perror("shmdt foireux 3");
	}
	if((shmdt(carsQualif2))==-1)
	{
		perror("shmdt foireux a");
	}
	if((shmdt(carsQualif3))==-1)
	{
		perror("shmdt foireux a");
	}
	if((shmctl(id_shm, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) failed\n");
	}
	if((shmctl(id_shm1, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 1 failed\n");
	}
	if((shmctl(id_shm2, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 2 failed\n");
	}
	if((shmctl(id_shm3, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 3 failed\n");
	}
	if((shmctl(id_shm4, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 4 failed\n");
	}
	if((semctl(id_sem, 0, IPC_RMID))==-1)
	{
//		printf("errno %d\n", errno);
//		perror("semctl(IPC_RMID) failed\n");
	}
	
}
