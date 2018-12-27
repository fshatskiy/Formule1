neemn#include "voiture.h"
#include "utilitaire.h"
#include "entrainement.h"
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
	if(getpid()==pidList[0] && nprocesses==0) //=>process du parent (du père?) après que tout les forks soit fait
		
		//debut du practice 1 (entrainement 1?)
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//demander à l'utilisateur si il veut continuer : si oui smv[0]=0 sinon tuer tout les enfants
		//et quiter le programme
		interaction(0);
		
		//debut du practice 2 (entrainement 2?)
		wakeChildren();
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//demander à l'utilisateur si il veut continuer : si oui smv[1]=0 sinon tuer tout les enfants
		//et quiter le programme
		interaction(1);
		
		
		//debut du practice 3 (entrainement 3?)
		wakeChildren(); //reveiller les enfants
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//demander à l'utilisateur si il veut continuer : si oui smv[2]=0 sinon tuer tout les enfants
		//et quiter le programme
		interaction(2);
		
		//Debut des qualif 1
		wakeChildren();
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		//creation d'une variable temporaire qui contient les voitures, en les triant et en les mettant dans la liste des départs. (starting list)
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		for(int i =0; i<20; i++)
		{
			temp[i]=cars[i];
		}
		id_sem = semop(id_sem, &semPost, 1);
		
		sortCars(temp, 20);
		buildStartPosition(temp, 1);
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//Nous éliminons les voitures n'ayant pas été assez rapides
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		setOut(2);
		id_sem = semop(id_sem, &semPost, 1);
		
		//demander à l'utilisateur si il veut continuer : si oui smv[3]=0 sinon tuer tout les enfants
		//et quiter le programme
		interaction(3);
		
		//Debut des qualif 2
		wakeChildren();
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		//créer la list de départs 
		sortCars(carsQualif2, 15);
		buildStartPosition(carsQualif2, 2);
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//élimination de la voiture la plus lente 
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		setOut(3);
		id_sem = semop(id_sem, &semPost, 1);
		
		//demander à l'utilisateur si il veut continuer : si oui smv[4]=0 sinon tuer tout les enfants
		//and exit program
		interaction(4);
		//start of qualif 3
		wakeChildren();
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		//Construction de la liste des départs ? (building) starting list
		sortCars(carsQualif3, 10);
		buildStartPosition(carsQualif3, 3);
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//demander à l'utilisateur si il veut continuer : si oui smv[5]=0 sinon tuer tout les enfants
		//and exit program
		interaction(5);
		//debut de la course
		wakeChildren();
		//here we add time to cars with regard to startPosition
		addTimeByPosition();
		isRace = 1;
		//le processus parent dort jusqu'a ce que tout les enfants aient fini leurs practice (entrainement) 
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
		
		//ici, toutes les voitures on fini le practice donc on génère le fichier recap.
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileRace();
		semop(id_sem, &semPost, 1);
		
		printf("\n\nThe race is over, we hope you've enjoyed yourselves !\n");
		
	}
	
	
	if(nprocesses > 0) //toutes les forks ne sont pas encore finies
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
			
			//debut du practice  1 (entrainement 1?)
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
			//attends que les autres ait fini et que les processus parents aient fini (d'imprimer 'd'ecrire) 
			//le fichier recap;
			while(smv[0]!=0)
			{
				sleep(1);
			}
			
			//debut du practice 2 (entrainement 2?)
			practice(index-1, 2);
			//attends que les autres ait fini et que les processus parents aient fini (d'imprimer 'd'ecrire) 
			//le fichier recap;
			while(smv[1]!=0)
			{
				sleep(1);
			}
			
			//debut du practice 3 (entrainement 3?)
			practice(index-1, 3);
			//attends que les autres ait fini et que les processus parents aient fini (d'imprimer 'd'ecrire) 
			//le fichier recap;
			while(smv[2]!=0)
			{
				sleep(1);
			}
			
			//Debut des qualif 1
			qualif(index-1, 1);
			//attends que les autres ait fini et que les processus parents aient fini (d'imprimer 'd'ecrire) 
			//le fichier recap;
			while(smv[3]!=0)
			{
				sleep(1);
			}
			
			//Debut des qualif 2
			qualif(index-1, 2);
			//attends que les autres ait fini et que les processus parents aient fini (d'imprimer 'd'ecrire) 
			//le fichier recap; 
			while(smv[4]!=0)
			{
				sleep(1);
			}
			
			//Debut des qualif 3
			qualif(index-1, 3);
			//attends que les autres ait fini et que les processus parents aient fini (d'imprimer 'd'ecrire) 
			//le fichier recap;
			while(smv[5]!=0)
			{
				sleep(1);
			}
			
			//Debut de la course
			race(index-1);
			
			//quiter le processus une fois que tout à été fait 
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
	int key = 123;//clé de la mémoire partagée
	int key1 = 789;//deuxieme clé de la mémoire partagée
	int key2 = 999;//troisième clé de la mémoire partagée
	int key3 = 888;//quatrième clé de la mémoire partagée
	int key4 = 777;//cinquième clé de la mémoire partagée
	int keyS = 456;//clé de la semaphore
	//	struct timeval temps_avant, temps_apres; se sont les structures que nous avons utilisé pour determiner
	//	le temps du délais requis pour permettre au processus du parent the forker tous ces enfants 
	
	//Création de la sémaphore
	if ((id_sem = semget(keyS, 3, IPC_CREAT|0666)) == -1) {
		perror("semget: semget failed");
		exit(1);
	}
	
	//Variables temporaires que nous avons utilisé pour determiner la taille requise de la mémoire partagée
	structCar temp[20];
	structCar temp3[15];
	structCar temp4[10];
	int temp1[7];
	int temp2[21];
	
	//Création de mémoires partagées dont nous avions besoin (1 pour les voitures, 1 pour les variables dont nous avions besoin
	//et 1 pour la pidList)
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
	
	//Ici on débute l'interaction avec l'utilisateur en lui demandant de choisir la longueur du tour. 
	int km; // en kilomètre
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
	
	//on attache la memoire partagée
	cars = shmat(id_shm, NULL, SHM_W);
	smv = shmat(id_shm1, NULL, SHM_W);
	pidList = shmat(id_shm2, NULL, SHM_W);
	carsQualif2 = shmat(id_shm3, NULL, SHM_W);
	carsQualif3 = shmat(id_shm4, NULL, SHM_W);
	
	//ici on initialise les voitures 
	int c[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
	for(int i=0; i<20; i++)
	{
		//locking semaphore (verrouille)
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		init(i,c[i]);
		semop(id_sem, & semPost, 1);
		startPosition[i]=0;
		//unlocking semaphore (déverouille)
	}
	
	//ici on initialise les variables "globales" 
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
	
	//ici on initialise la pidList (values = -1 pour permettre la detection d'erreur plus tard)
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
	//	printf("parent pid %d\n", getpid()); ces lignes étaient nécéssaires pour calculer
	//	délais de temps mentionné plus tot.
	worker(20);
	
	//	gettimeofday (&temps_apres, NULL);
	//	printf("temps en us: %ld us pid %d\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 +
	//	temps_apres.tv_usec) - temps_avant.tv_usec, getpid()); ces lignes étaient nécéssaires pour calculer
	//	délais de temps mentionné plus tot.
	
	//ici on detache le segment de la mémoire partagée et on supprime les semaphores
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
