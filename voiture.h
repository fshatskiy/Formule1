#ifndef _VOITURE_H
#define _VOITURE_H

/*
 * Définition de la structure représentant une voiture
 */
typedef struct structTuture {
	int nom;           //nom de la voiture
	double topCircuit; //Meilleur temps sur un tour de circuit
	double topS1;      //Meilleur temps sur le premier secteur
	double topS2;      //Meilleur temps sur le deuxieme secteur
	double topS3;      //Meilleur temps sur le troisieme secteur
	int numCircuit;     //Nombre de tours déjà effectués
	double currTemps;    //Temps écoulé depuis le début de la course
	double currCircuit; //Heure actuelle de la course
	int inStand;        /*nombre de fois qu'il a passé le stand (entre 1 et 3) */
	/*prend entre 22 et 27 secondes */
	int isOut;          //0 si la voiture est toujours en marche, 1 si c'est le crash
}structTuture;

/*
 * initialisation des voitutres
 * @pre : i est l'index de l'onglet contenant toutes les voitures et nommez le nom de la voiture
 * @post : initialize tuture-> nom de la voiture indexée par i, les autres sont initialisées à 0.
 */
void init(int i, int nom);

/*
 * Réinitialiser les scores de la voiture indexés par i
 * @pre : i l'index de l'onglet contenant toutes les voitures
 * @post : toutes les variables sont réinitialisées sauf le nom de la voiture.
 */
void reset(int i);

#endif
