#include "utilitaire.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>


//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait = {0,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo = {0,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost = {0,-1,SEM_UNDO|IPC_NOWAIT};

//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait1 = {1,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo1 = {1,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost1 = {1,-1,SEM_UNDO|IPC_NOWAIT};

//indique que la valeur du sémaphore devrait être 0
struct sembuf semWait2 = {2,0,SEM_UNDO};

//incrémente la valeur du sémaphore pour la bloquer
struct sembuf semDo2 = {2,1,SEM_UNDO|IPC_NOWAIT};

//décrémente la valeur du sémaphore pour la débloquer
struct sembuf semPost2 = {2,-1,SEM_UNDO|IPC_NOWAIT};

//variable pour transférer des heures en seconde
double transfHourInSec = 3600;

// RANDOM
int generateRandom(int min_number, int max_number){
	int rand_num = rand()%(max_number + 1 - min_number) + min_number;
	return rand_num;
}

//PITSTOP
int pitStop(int i) {
	int timeStop = 0; //temps passé au pit
	
	// 15% chance of a pit stop
	if (generateRandom(0, 99) > 84) {
		cars[i].inStand ++; //incrémente le nombre de pitstop
		timeStop += (generateRandom(24, 40)/10.0);
	}
	
	// obligation de s'arrêter au stand au moins une fois pendant la course
	if (cars[i].inStand == 0 && cars[i].numCircuit == nbrLapMax){
		cars[i].inStand ++; //Incrémenter le numéro du pitstop pour la voiture spécifiée
		timeStop += (generateRandom(24, 40)/10.0);
	}
	
	return timeStop;
}

//CRASH
void crash(int index)
{	//0 = no crash
	if (generateRandom(0, 999) > 998) { // 3% chance de crash
		cars[index].isOut = 1; //1=crash
	}
}

//Renvoie le temps que la voiture a fait 
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

// NBR TOURS
int nbrLaps(int km)
{
	int nbr = 70;			// Le nombre de tours par défaut
	int lengthMinRace = 305;	// Longueur minimale pour une course
	if(km == 0)  //si l'utilisateur n'entre pas de paramètre pour les kilomètres
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
	//si le pid n'est pas dans l'onglet, nous renvoyons la longueur de l'onglet pour permettre la détection d'erreur
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
	double lengthPercent = 0.28; // Longueur du secteur en pourcentage de la longueur totale du circuit
	double time;
	
	if(!(isRace == 1 && cars[i].numCircuit == 0)){
		cars[i].currCircuit = 0.0;  //réinitialiser la valeur du temps pour le tour en cours
	}
	
	double averageSpeed = (double)(generateRandom(3450, 3750)/10); //génération de la vitesse moyenne de la voiture
	
	crash(i); //appelle la fonction pour voir si la voiture tombe en panne
	
	if(cars[i].isOut == 0){
		time = lengthPercent*lengthCircuit /(averageSpeed/transfHourInSec); //calcul de la performance temporelle de la voiture en secondes pour ce secteur
		
		//Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
		if(cars[i].bestS1 < 1 || time < cars[i].bestS1){
			cars[i].bestS1 = time;
		}
	}
	semop(id_sem, &semPost, 1);
}

void generateTimeS2(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.33; //Longueur du secteur en pourcentage de la longueur totale du circuit
	double time;
	
	double averageSpeed = (double)(generateRandom(3000, 3640)/10); //génération de la vitesse moyenne de la voiture
	
	crash(i); //appelez la fonction pour voir si l'accident de voiture
	
	if(cars[i].isOut == 0){
		time = lengthPercent * lengthCircuit / ( averageSpeed / transfHourInSec ); // calcul de la performance temporelle de la voiture en secondes pour ce secteur
		
		// Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Modification du meilleur moment pour le secteur 2 si le nouveau est meilleur
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
	double lengthPercent = 0.39; //Longueur du secteur en pourcentage de la longueur totale du circuit
	double time;
	
	double averageSpeed = (double)(generateRandom(3200, 3550)/10); //génération de la vitesse moyenne de la voiture
	
	crash(i); //appelez la fonction pour voir si l'accident de voiture
	
	if(cars[i].isOut == 0){
		time = lengthPercent * lengthCircuit / ( averageSpeed / transfHourInSec ); //calcul de la performance temporelle de la voiture en secondes pour ce secteur
		time += (double)pitStop(i); // ajout du pit stop
		
		// Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Modification du meilleur moment pour le secteur 3 si le nouveau est meilleur
		if(cars[i].bestS3 < 1 || time < cars[i].bestS3){
			cars[i].bestS3 = time;
		}
		
		// Modification du meilleur temps pour le circuit si le nouveau est meilleur
		if(cars[i].bestCircuit < 1 || cars[i].currCircuit < cars[i].bestCircuit){
			cars[i].bestCircuit= cars[i].currCircuit;
		}
	}
	semop(id_sem, &semPost, 1);
	//printf("3 %d", i);
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
		//envoyer un signal pour tuer le processus avec pid = pidList [i]
		kill(pidList[i], SIGKILL);
	}
}

void wakeChildren()
{
	for(int i=1; i<21; i++)
	{
		//envoyer un signal pour réveiller le processus avec pid = pidList [i]
		kill(pidList[i], SIGCONT);
	}
}


void sortRace(structCar carsQualif[], int sizeArrayCars)
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	
	for(i=0; i < sizeArrayCars; i++)
		//Remplir le cas i du tableau
	{
		for(j = i+1; j < sizeArrayCars; j++)
			//Vérifiez s'il n'y a pas de plus petit nombre dans les cas suivants
		{
			if((carsQualif[j].currTime < carsQualif[i].currTime)&&(carsQualif[j].isOut==0))
			{
				//Si c'est vrai, le numéro change
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
			if (cars[i].name == startPosition[j]){   // ajouter du temps par position par rapport à la première
				cars[i].currTime += j * 0.3;     // à l'heure normale
				cars[i].currCircuit = j * 0.3;   // chronométrer sur un tour
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
			//si la voiture n'est pas dans carsQuelif2, nous la disqualifions
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
			//si la voiture n'est pas dans carsQuelif3, nous la disqualifions
			if(j==0)
			{
				cars[i].isOut=1;
			}
		}
	}
}

