#ifndef qualification_h
#define qualification_h

#include "voiture.h"

/*
 * Sort the table cars on the base of bestCircuit
 * @pre : carsQualif not null, sizeArrayCars==20 || sizeArrayCars==15 || sizeArrayCars==10
 * @post : modify the carsQualif
 */
void sortCars(structCar carsQualif[], int sizeArrayCars);

/*
 * Build the start grid
 * @pre : carsQualif not null, q==1 || q==2 || q==3
 * @post : modify the startPosition variable
 */
void buildStartPosition(structCar carsQualif[], int q);

/*
 * Runs the qualif on a car
 * @pre : car referenced by the index is not null, q==1 || q==2 || q==3
 * @post : modify the values in the car structure
 */
void qualif(int index, int q);

/*
 * Creates the file with the recap of the qualif
 * @pre :
 * @post : creates a file with all the infos needed
 */
void generateRecapFileQualif();

#endif /* practice_h */

