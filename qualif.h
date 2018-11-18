/*
PROJET
2018
*/
#ifndef QUALIF_H_INCLUDED
#define QUALIF_H_INCLUDED

#include "utilitaire.h"



/*
 * Trie la table de voitures du base de bestCircuit
 * @pre : carsQualif not null, sizeArrayCars==20 || sizeArrayCars==15 || sizeArrayCars==10
 * @post : modification de carsQualif
 */
void sortCars(structCar carsQualif[], int sizeArrayCars);
#endif // QUALIF_H_INCLUDED
