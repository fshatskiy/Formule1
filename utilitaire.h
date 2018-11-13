#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

StructCar cars[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};

/*
 * Definition of the structure representing a car
 */
typedef struct structCar {
	int number;           //Name of the car
	double bestCircuit; //Best time on a circuit lap
	double bestS1;      //Best time on the first sector
	double bestS2;      //Best time on the second sector
	double bestS3;      //Best time on the third sector
	int numCircuit;     //Number of laps already done
	double currTime;    //Time elapsed since the start of the race
	double currCircuit; //Current time of the race
	int pitStop;        /*number of times it has passed the stand (between 1 and 3) */
	/*takes between 22 and 27 seconds */
	int isOut;          //0 if the car still run, 1 if it's crash
}structCar;

/*
 * Initialize a car
 * @pre : i the index of the tab containing all the cars and the number of the car
 * @post : initialize car->number of the car indexed by i, the others are initialized at 0.
 */
void init(int i, int number);

/*
 * Reset car's scores indexed by i
 * @pre : i the index of the tab containing all the cars
 * @post : all variable are reset except the car's number.
 */
void reset(int i);

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

#endif // UTILITAIRE_H_INCLUDED
