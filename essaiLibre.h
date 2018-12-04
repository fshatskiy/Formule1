/*
PROJET
2018
*/
#ifndef ESSAILIBRE_H
#define ESSAILIBRE_H
#include "utilitaire.h"

/*
 * Lance l'essai sur la voiture située dans cars[index]
 * @pre : index de la car, essai==1 || essai==2 || essai==3 ---> essais
 * @post : modifie les valeurs de la strucutre car
 */
void practice(int index, int essai);

/*
 * Crée le récapitulatif de l'essai libre
 * @pre : cars not null
 * @post : crée le fichier les informations 
 */
void generateEssaiLibreFile();

#endif // ESSAILIBRE_H
