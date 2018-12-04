/*
PROJET
2018
*/
#ifndef ESSAILIBRE_H
#define ESSAILIBRE_H
#include "utilitaire.h"




/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * Runs the practice on a car situated at cars[index]
 * @pre : index of a car, p==1 || p==2 || p==3 ---> p = essais
 * @post : modify the values in the car structure
 */
void practice(int index, int p);

/*
 * Crée le récapitulatif de l'essai libre
 * @pre : cars not null
 * @post : crée le fichier les informations 
 */
void generateEssaiLibreFile();

#endif // ESSAILIBRE_H
