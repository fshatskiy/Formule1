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
int genereRandom(int min_number, int max_number){
	int rand_num = rand()%(max_number + 1 - min_number) + min_number;
	return rand_num;
}

//PITSTOP
int pitStop(int i) {
	int tempsStop = 0; //temps passé au pit
	
	// 15% chance du pit stop
	if (genereRandom(0, 99) > 84) {
		voitures[i].inStand ++; //incrémente le nombre de pitstop
		tempsStop += (genereRandom(24, 40)/10.0);
	}
	
	// obligation de s'arrêter au stand au moins une fois pendant la course
	if (voitures[i].inStand == 0 && voitures[i].numCircuit == nbrLapMax){
		voitures[i].inStand ++; //Incrémenter le numéro du pitstop pour la voiture spécifiée
		tempsStop += (genereRandom(24, 40)/10.0);
	}
	
	return tempsStop;
}

//CRASH
void crash(int index)
{	//0 = no crash
	if (genereRandom(0, 999) > 998) { // 3% chance de crash
		voitures[index].isOut = 1; //1=crash
	}
}

//Renvoie le temps que la voiture a fait 
double getCurrTemps()
{
	double curr = 0;
	for(int i=0; i<20; i++)
	{
		if(voitures[i].currTemps>curr)
		{
			curr = voitures[i].currTemps;
		}
	}
	return curr;
}

// NBR TOURS
int nbrLaps(int km)
{
	int nbr = 70;			// Le nombre de tours par défaut
	int longueurMinCourse = 305;	// longueur minimale pour une course
	if(km == 0)  //si l'utilisateur n'entre pas de paramètre pour les kilomètres
	{
		return nbr;
	}
	if(longueurMinCourse % km == 0)
	{
		nbr = longueurMinCourse/km;
	}
	else
	{
		nbr = 1 + (longueurMinCourse/km);
	}
	return nbr;
}

int indexOf(int i, int longueur, int t[])
{
	for(int j=0; j<longueur; j++)
	{
		if(i==t[j])
		{
			return j;
		}
	}
	//si le pid n'est pas dans l'onglet, nous renvoyons la longueur de l'onglet pour permettre la détection d'erreur
	return longueur;
}
//.h
int isIn(int nom, int longueur, structTuture t[])
{
	int k=0;
	for(int j=0; j<longueur; j++)
	{
		if(nom==t[j].nom)
		{
			k=1;
			break;
		}
	}
	return k;
}

void genereTempsS1(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double longueurPercent = 0.28; // longueur du secteur en pourcentage de la longueur totale du circuit
	double temps;
	
	if(!(isCourse == 1 && voitures[i].numCircuit == 0)){
		voitures[i].currCircuit = 0.0;  //réinitialiser la valeur du temps pour le tour en cours
	}
	
	double vitesseMoy = (double)(genereRandom(3450, 3750)/10); //génération de la vitesse moyenne de la voiture
	
	crash(i); //appelle la fonction pour voir si la voiture tombe en panne
	
	if(voitures[i].isOut == 0){
		temps = longueurPercent*longueurCircuit /(vitesseMoy/transfHourInSec); //calcul de la performance temporelle de la voiture en secondes pour ce secteur
		
		//Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
		voitures[i].currCircuit += temps;
		voitures[i].currTemps += temps;
		
		// Modification du meilleur moment pour le secteur 1 si le nouveau est meilleur
		if(voitures[i].topS1 < 1 || temps < voitures[i].topS1){
			voitures[i].topS1 = temps;
		}
	}
	semop(id_sem, &semPost, 1);
}

void genereTempsS2(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double longueurPercent = 0.33; //longueur du secteur en pourcentage de la longueur totale du circuit
	double temps;
	
	double vitesseMoy = (double)(genereRandom(3000, 3640)/10); //génération de la vitesse moyenne de la voiture
	
	crash(i); //appelez la fonction pour voir si l'accident de voiture
	
	if(voitures[i].isOut == 0){
		temps = longueurPercent * longueurCircuit / ( vitesseMoy / transfHourInSec ); // calcul de la performance temporelle de la voiture en secondes pour ce secteur
		
		// Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
		voitures[i].currCircuit += temps;
		voitures[i].currTemps += temps;
		
		// Modification du meilleur moment pour le secteur 2 si le nouveau est meilleur
		if(voitures[i].topS2 < 1 || temps < voitures[i].topS2){
			voitures[i].topS2 = temps;
		}
	}
	semop(id_sem, &semPost, 1);
}

void genereTempsS3(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double longueurPercent = 0.39; //longueur du secteur en pourcentage de la longueur totale du circuit
	double temps;
	
	double vitesseMoy = (double)(genereRandom(3200, 3550)/10); //génération de la vitesse moyenne de la voiture
	
	crash(i); //appelez la fonction pour voir si l'accident de voiture
	
	if(voitures[i].isOut == 0){
		temps = longueurPercent * longueurCircuit / ( vitesseMoy / transfHourInSec ); //calcul de la performance temporelle de la voiture en secondes pour ce secteur
		temps += (double)pitStop(i); // ajout du pit stop
		
		// Ajout du temps au temps actuel du circuit et au temps total depuis le début de la partie de la course
		voitures[i].currCircuit += temps;
		voitures[i].currTemps += temps;
		
		// Modification du meilleur moment pour le secteur 3 si le nouveau est meilleur
		if(voitures[i].topS3 < 1 || temps < voitures[i].topS3){
			voitures[i].topS3 = temps;
		}
		
		// Modification du meilleur temps pour le circuit si le nouveau est meilleur
		if(voitures[i].topCircuit < 1 || voitures[i].currCircuit < voitures[i].topCircuit){
			voitures[i].topCircuit= voitures[i].currCircuit;
		}
	}
	semop(id_sem, &semPost, 1);
	sleep(1);
}

char demandeAction()
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
	char c = demandeAction();
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


void sortCourse(structTuture voituresQualif[], int sizeArrayVoitures)
{
	int i=0;
	structTuture tmpTuture;
	int j = 0;
	
	for(i=0; i < sizeArrayVoitures; i++)
		//Remplir le cas i du tableau
	{
		for(j = i+1; j < sizeArrayVoitures; j++)
			//Vérifiez s'il n'y a pas de plus petit nombre dans les cas suivants
		{
			if((voituresQualif[j].currTemps < voituresQualif[i].currTemps)&&(voituresQualif[j].isOut==0))
			{
				//Si c'est vrai, le numéro change
				tmpTuture = voituresQualif[i];
				voituresQualif[i] = voituresQualif[j];
				voituresQualif[j] = tmpTuture;
			}
		}
	}
}

void ajouteTempsEnFctPosition()//en fct de la place de la voiture au début de la course, un temps est ajouté
{
	for (int j = 0; j < 20; j++)
	{
		for(int i = 0; i < 20; i++)
		{
			if (voitures[i].nom == startPosition[j]){   // ajouter du temps par position par rapport à la première
				voitures[i].currTemps += j * 0.3;     // à l'heure normale
				voitures[i].currCircuit = j * 0.3;   // chronométrer sur un tour
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
			int j = isIn(voitures[i].nom, 15, voituresQualif2);
			//si la voiture n'est pas dans voituresQuelif2, nous la disqualifions
			if(j==0)
			{
				voitures[i].isOut=1;
			}
		}
	}
	else
	{
		for(int i=0; i<20; i++)
		{
			int j = isIn(voitures[i].nom, 10, voituresQualif3);
			//si la voiture n'est pas dans voituresQuelif3, nous la disqualifions
			if(j==0)
			{
				voitures[i].isOut=1;
			}
		}
	}
}

