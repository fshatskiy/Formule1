/*
PROJET
2018
*/
#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
 * Définition de la strucutre de voiture
 */
typedef struct structCar {
	int number;           //numéro de la voiture
	double bestCircuit; //Meilleur temps du tour
	double bestS1;      //Meilleur temps du secteur 1
	double bestS2;      //Meilleur temps du secteur 2
	double bestS3;      //Meilleur temps du secteur 3
	double currTime;    //Temps lancé depuis le début de la course
	double currCircuit; //Temps actuel de la course //PAS BESOIN ?
	int nbrOfStands;        /*nombre de fois de passage au stand (entre 1 et 3) */
	/*prend entre 22 et 27 secondes */
	int isOut;          //retourne 1 si crash
}structCar;

/*
 * Initialise la voiture
 * @pre : i index du tableau centenant toutes les voitures et leurs nombres
 * @post : initialise la voiture, numéro indexé par i, les autres sont initialisés à 0
 */
void init(int i, int number);

/*
 * Initialise les scores des voitures indexé par i
 * @pre : i ,l'index du tableau contenant toutes les voitures
 * @post : les variables sont initialisées sauf le numéro de voiture
 */
void reset(int i);

/*
 * Génère un pitStop random. i est l'index de voiture de la structure
 * @pre : 0 <= i <= |cars|
 * @post : si arrêt au pitStop, incrémente car[i].pitStop et retourne le temps de ce pitStop, sinon retourne 0
 */
int pitStop(int i);

/*
 * Génère un crash random. Index est l'index de la voiture dans "Voitures"
 * @pre : 0 <= index <= |cars|
 * @post : retourne 1 si crash a eu lieu, 0 sinon
 */
void crash(int index);

/*
 * Retourne le temps de chaque voiture 							????
 * @pre : structCar *cars existe
 * @post : retourne le temps max "currentTime" des voitures				????
 */
double getCurrTime();

/*
 * Ajoute un certain temps dépendant de la position de la voiture au Start de la course
 * @pre:/
 * @post: retourne void. Ajoute le temps aux voitures pa rapport au placement
 */
void addTimeByPosition();

/*
 * Modifie la variable "out" à 0 des voitures qui ne peuvent pas aller en qualif
 * to 1.
 * @pre: q==2||q==3
 * @post: retourne void. "out" a été modifié pour les voitures concernées
 */
void setOut(int q);

#endif // UTILITAIRE_H_INCLUDED
