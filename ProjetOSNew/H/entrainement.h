#ifndef entrainement_h
#define entrainement_h

#include "voiture.h"

/*
 * Lance l'entrainement sur la voiture située dans cars[index]
 * @pre : index de la car, p==1 || p==2 || p==3 ---> essais
 * @post : modifie les valeurs de la strucutre car
 */
void entrainement(int index, int p);

/*
 * Crée le récapitulatif de l'essai libre
 * @pre : cars not null
 * @post : crée le fichier les informations 
 */
void generateRecapFilePractice();


#endif /* entrainement_h */
