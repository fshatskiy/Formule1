#include "voiture.h"
#include "utilitaire.h"
#include "entrainement.h"
#include <stdio.h>
#include <stdlib.h>

//Valeurs de temps représentant la longueur des entrainements
double temps1 = 100;//90 min 5400
double temps2 = 100;//5400
double temps3 = 100;//60 min 3600

void entrainement(int index, int p)
{
	semop(id_sem, &semWait, 1);//verouille
	semop(id_sem, &semDo, 1);//prend le controle du sémaph
	double temps = getCurrTemps();
	semop(id_sem, &semPost, 1);//deverouille

	double tempsEntrainement;
	//détermine durée de l'entrainement
	if(p==1)
	{
		tempsEntrainement = temps1;
	}
	if(p==2)
	{
		tempsEntrainement = temps2;
	}
	if(p==3)
	{
		tempsEntrainement = temps3;
	}

	//on boucle jusqu'à ce que le temps soit écoulé ou que la voiture soit épuisée
	while(temps<tempsEntrainement && (voitures[index].isOut == 0))
	{
		//comme d'habitude, blocage du processus pour éviter les conflits, lance le premier secteur de la voiture
		genereTempsS1(index);

		//si la voiture a un meilleur temps pour S1, màj de la variable globale
		if(voitures[index].topS1 < smv[7])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[7] = voitures[index].topS1;
			semop(id_sem, &semPost1, 1);
		}

		//lancement du secteur 2
		genereTempsS2(index);

		//si la voiture a un meilleur temps pour S2, màj de la variable globale
		if(voitures[index].topS2 < smv[8])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[8] = voitures[index].topS2;
			semop(id_sem, &semPost1, 1);
		}

		//lancement du secteur 3
		genereTempsS3(index);

		//si la voiture a un meilleur temps pour S3, màj de la variable globale
		if(voitures[index].topS3 < smv[9])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[9] = voitures[index].topS3;
			semop(id_sem, &semPost1, 1);
		}
		//si la voiture a un meilleur temps que tous les autres, màj de la variable globale
		if(voitures[index].topCircuit>smv[10])
		{
			semop(id_sem, &semWait1, 1);
			semop(id_sem, &semDo1, 1);
			smv[10] = voitures[index].topCircuit;
			semop(id_sem, &semPost1, 1);
		}

		//màj du temps global de la course
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		temps = getCurrTemps();
		semop(id_sem, &semPost, 1);
	}

	//Imàj de la valeur smv [0], [1] ou [2], indique au processus parent que la voiture a terminé sa séance d'entrainement
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


void genereRecapEntrainementFile()
{
	FILE *fichier = NULL;

	//ouverture du fichier avec l'argument "a" pour annexer chaque entrainement
	fichier = fopen("RecapEntrainement.txt", "a");//cree et ouvre le fichier
	structTuture tempo = voitures[0]; //temporaire
	tempo.topCircuit=10000;//Gros nombre pour le bon fonctionnement de la fct
	if(fichier != NULL){

		fprintf(fichier,"\n| N Voiture |     top S1    |     top S2    |     top S3    |    top Tour     |\n");

		for(int i = 0; i < 20; i++){
			if((tempo.topCircuit>voitures[i].topCircuit)&&(voitures[i].topCircuit != 0)){tempo=voitures[i];}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", voitures[i].nom,voitures[i].topS1,voitures[i].topS2,voitures[i].topS3,voitures[i].topCircuit);
		}//f float, d int

		fprintf(fichier,"\n La voiture gagnante est n°%2d avec un temps de %9f s\n",tempo.nom, tempo.topCircuit);
		fclose(fichier);
	}
	else{
		printf("Ouverture du fichier recap impossible");
	}
	//Après avoir sauvegardé les valeurs dans le fichier, on les initialise, les voitures vont redémarrer
	//l'entrainement suivant avec un nouvel état

	for(int i=0; i<20; i++)

	{
		reset(i);
	}
}
