#ifndef race_h
#define race_h

#include "voiture.h"

/*
 * Sort the table cars on the base of current time and lap's number
 * @pre : carsRace not null
 * @post : modify the carsRace
 */
void sortCarsByCurrTime(structCar carsRace[]);

/*
 * Runs the race on a car
 * @pre : car referenced by the index is not null
 * @post : modify the values in the car structure
 */
void race(int index);

/*
 * Creates the file with the recap of the race
 * @pre : cars not null
 * @post : creates a file with all the infos needed
 */
void generateRecapFileRace();

#endif /* race_h */
