#ifndef entrainement_h
#define entrainement_h

#include "voiture.h"

/*
 * Lance l'entrainement sur la voiture située dans voitures[index]
 * @pre : index de la voitures, p==1 || p==2 || p==3 ---> entrainements
 * @post : modifie les valeurs de la structure voitures
 */
void entrainement(int index, int p);

/*
 * Crée le récapitulatif des entrainements
 * @pre : voitures not null
 * @post : crée le fichier les informations 
 */
void genereRecapEntrainementFile();


#endif /* entrainement_h */
