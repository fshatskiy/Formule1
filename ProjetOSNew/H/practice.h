#ifndef practice_h
#define practice_h

#include "voiture.h"

/*
 * Runs the practice on a car situated at cars[index]
 * @pre : index of a car, p==1 || p==2 || p==3
 * @post : modify the values in the car structure
 */
//A Remplacer le commentaire par

/*
 * Lance l'essai sur la voiture située dans cars[index]
 * @pre : index de la car, essai==1 || essai==2 || essai==3 ---> essais
 * @post : modifie les valeurs de la strucutre car
 */
void practice(int index, int p);

/*
 * Crée le récapitulatif de l'essai libre
 * @pre : cars not null
 * @post : crée le fichier les informations 
 */
void generateRecapFilePractice();


#endif /* practice_h */
