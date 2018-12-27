#include "voiture.h"
#include "utilitaire.h"
#include "entrainement.h"
#include <stdio.h>
#include <stdlib.h>

//Valeurs de temps représentant la longueur des essais
double temps1 = 5400;//90 min
double temps2 = 5400;
double temps3 = 3600;//60 min

void practice(int index, int p)
{
	semop(id_sem, &semWait, 1);//verouille
	semop(id_sem, &semDo, 1);//prend le controle du sémaph
	double time = getCurrTime();
	semop(id_sem, &semPost, 1);//deverouille
	
	double timePractice;
	//détermine durée de l'essai
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
	
	//on boucle jusqu'à ce que le temps soit écoulé ou que la voiture soit épuisée
	while(time<timePractice && (cars[index].isOut == 0))
	{
		//comme d'habitude, blocage du processus pour éviter les conflits, lance le premier secteur de la voiture
		generateTimeS1(index);
		
		//si la voiture a un meilleur temps pour S1, màj de la variable globale
		if(cars[index].bestS1 < smv[7])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[7] = cars[index].bestS1;
			semop(id_sem, &semPost1, 1);
		}
		
		//lancement du secteur 2
		generateTimeS2(index);
		
		//si la voiture a un meilleur temps pour S2, màj de la variable globale
		if(cars[index].bestS2 < smv[8])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[8] = cars[index].bestS2;
			semop(id_sem, &semPost1, 1);
		}
		
		//lancement du secteur 3
		generateTimeS3(index);
		
		//si la voiture a un meilleur temps pour S3, màj de la variable globale
		if(cars[index].bestS3 < smv[9])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[9] = cars[index].bestS3;
			semop(id_sem, &semPost1, 1);
		}
		//si la voiture a un meilleur temps que tous les autres, màj de la variable globale
		if(cars[index].bestCircuit>smv[10])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[10] = cars[index].bestCircuit;
			semop(id_sem, &semPost1, 1);
		}
		
		//màj du temps global de la course
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		time = getCurrTime();
		semop(id_sem, &semPost, 1);
	}
	
	//Imàj de la valeur smv [0], [1] ou [2], indique au processus parent que la voiture a terminé sa séance d'essais
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void generateRecapFilePractice()//generateEssaiLibreFile()
{
	FILE *fichier = NULL;
	
	//ouverture du fichier avec l'argument "a" pour annexer chaque essai
	fichier = fopen("RecapEntrainement.txt", "a");//cree et ouvre le fichier
	structCar temp = cars[0];
	temp.bestCircuit=10000;//Gros nombre pour le bon fonctionnement de la fct
	if(fichier != NULL){
		
		fprintf(fichier,"\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |\n");
		
		for(int i = 0; i < 20; i++){
			if((temp.bestCircuit>cars[i].bestCircuit)&&(cars[i].bestCircuit != 0)){temp=cars[i];}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit);
		}//f float, d int
		
		fprintf(fichier,"\n The winner is the car number %2d with a time of %9f s\n",temp.name, temp.bestCircuit);
		fclose(fichier);
	}
	else{
		printf("Ouverture du fichier recap impossible");
	}
	//Après avoir sauvegardé les valeurs dans le fichier, on les initialise, les voitures vont redémarrer 
	//l'essai suivant avec un nouvel état 
	
	for(int i=0; i<20; i++)

	{
		reset(i);
	}
}

