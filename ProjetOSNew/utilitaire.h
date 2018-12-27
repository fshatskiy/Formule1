#ifndef utilitaire_h
#define utilitaire_h

#include "voiture.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Global variables that stay constant while the program runs

/*
 * Number of laps during one race
 */
int nbrLapMax;

/*
 * Length of the circuit. This value is entered by the user.
 */
int lengthCircuit;

/*
 * This the pointer to the shared memory segment that holds the cars structures
 */
structCar *cars;

/*
 * This is the pointer to the shared memory segment that holds the global variables that needs to be shared by
 * all the process and changed throughout the running time of the program
 */
int *smv;

/*
 * This is the pointer to the shared memory segment that holds the list of pids
 */
int *pidList;


/*
 * This is the pointer to the semaphores.
 */
int id_sem;

/*
 * This the pointer to the shared memory segment that holds the cars structures for
 * the cars running in the second qualification
 */
structCar *carsQualif2;

/*
 * This the pointer to the shared memory segment that holds the cars structures for
 * the cars running in the third qualification
 */
structCar *carsQualif3;

/*
 * Start position for the race (fill with the number of the car)
 */
int startPosition[20];

/*
 * This is a flag to know if it's the race or not 0 = not and 1 =race
 */
int isRace;

//Structures for the semaphores
//- first semaphore handles the shared memory segment for the cars (cras, carQualif 2 and 3)
//- second semaphore handles the shared memory segment for different variables
//- third semaphore handles the shared memory segment for the pid list
extern struct sembuf semWait;
extern struct sembuf semDo;
extern struct sembuf semPost;
extern struct sembuf semWait1;
extern struct sembuf semDo1;
extern struct sembuf semPost1;
extern struct sembuf semWait2;
extern struct sembuf semDo2;
extern struct sembuf semPost2;



/*
 * This function generate a random number between min & max.
 * @pre : min_number < max_number
 * @post : min_number < x < max_number & @returns x
 */
int generateRandom(int min_number, int max_number);

/*
 * This function generate a pit stop (based on a random function). i is the index of the car in the cars structure
 * @pre : 0 <= i <= |cars|
 * @post : if pitStop, increments car[i].pitStop and returns time of that pitStop, otherwise returns 0.
 */
int pitStop(int i);

/*
 * This function generate a random crash. index is the index of the car in cars.
 * @pre : 0 <= index <= |cars|
 * @post : returns 1 if crash, 0 otherwise
 */
void crash(int index);

/*
 * This function gets the maximum currentTime of the cars
 * @pre : structCar *cars exists
 * @post : returns the maximum currentTime of the cars
 */
double getCurrTime();

/*
 * This function computes the number of laps required for that track. This number is the smallest number
 * of laps so that the kilometers of the race >= 305 km.
 * @pre : km > 0
 * @post : returns x = 305/km if km%2==0|| x=1+305/km
 */
int nbrLaps(int km);

/*
 * This function matches the index of the process (in pidList) to an index in cars.
 * i is the pidList to match,
 * length is the length of the tab, t is the tab.
 * @pre : length>0
 * @post : returns the index if i is in the tab or length if it isn't
 */
int indexOf(int i, int length, int t[]);

/*
 * This function checks whether or not the car is in the array. It returns 1 if it is and 0
 * if it isn't
 * @pre: length>0
 * @post: returns 1 if name is in t, 0 otherwise
 */
int isIn(int name, int length, structCar t[]);

/*
 * This function generates the time that a structCar car takes to do the first sector. i is the index of the car in cars.
 * @pre : 0 <= i <= |cars|
 * @post : returns nothing and modify the following parameters from the car : currTime, currCircuit and if needed bestS1
 */
void generateTimeS1(int i);

/*
 * This function generates the time that a structCar car takes to do the first sector. i is the index of the car in cars.
 * @pre : 0 <= i <= |cars|
 * @post : returns nothing and modify the following parameters from the car : currTime, currCircuit and if needed bestS2
 */
void generateTimeS2(int i);

/*
 * This function generates the time that a structCar car takes to do the first sector. i is the index of the car in cars.
 * @pre : 0 <= i <= |cars|
 * @post : returns nothing and modify the following parameters from the car : currTime, currCircuit and if needed bestS3 and bestCircuit
 */
void generateTimeS3(int i);

/*
 * This function ask the user for an input and loops until the input is correct.
 * This input is a character.
 * @pre :/
 * @post : return the character
 */
char askAction();

/*
 * This function handles the interaction with the user and the killing of the children
 * if needed. i is the index of the variable to reset.
 * @pre:/
 * @post : if the user wants to stop, calls killchildren
 */
void interaction(int i);

/*
 * This function allows the parent process to kill all its children.
 * @pre:/
 * @post: returns nothing. All the children processes have been killed.
 */
void killChildren();

/*
 * This function allows the parent process to wake up all its children.
 * @pre:/
 * @post: returns nothing. All the children processes have been woken up.
 */
void wakeChildren();

/*
 * This function sorts an array of cars by their current global time.
 * @pre:/
 * @post: returns nothing, the array carsQualif has been sorted.
 */
void sortRace(structCar carsQualif[], int sizeArrayCars);
/*
 * This function add time by position of the car for the race.
 * @pre:/
 * @post: returns nothing. Just add time to the cars.
 */
void addTimeByPosition();

/*
 * This functions sets the out variables of the cars that can"t compete in q
 * to 1.
 * @pre: q==2||q==3
 * @post: returns nothing. out has been modified for the right cars
 */
void setOut(int q);

#endif // utilitaire_h 
