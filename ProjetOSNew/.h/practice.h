#ifndef practice_h
#define practice_h

#include "voiture.h"

/*
 * Runs the practice on a car situated at cars[index]
 * @pre : index of a car, p==1 || p==2 || p==3
 * @post : modify the values in the car structure
 */
void practice(int index, int p);

/*
 * Creates the file with the recap of the practice
 * @pre : cars not null
 * @post : creates a file with all the infos needed
 */
void generateRecapFilePractice();


#endif /* practice_h */
