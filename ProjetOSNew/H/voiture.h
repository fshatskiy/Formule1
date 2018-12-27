#ifndef _VOITURE_H
#define _VOITURE_H

/*
 * Definition of the structure representing a car
 */
typedef struct structCar {
	int name;           //Name of the car
	double bestCircuit; //Best time on a circuit lap
	double bestS1;      //Best time on the first sector
	double bestS2;      //Best time on the second sector
	double bestS3;      //Best time on the third sector
	int numCircuit;     //Number of laps already done
	double currTime;    //Time elapsed since the start of the race
	double currCircuit; //Current time of the race
	int inStand;        /*number of times it has passed the stand (between 1 and 3) */
	/*takes between 22 and 27 seconds */
	int isOut;          //0 if the car still run, 1 if it's crash
}structCar;

/*
 * Initialize a car
 * @pre : i the index of the tab containing all the cars and name the name of the car
 * @post : initialize car->name of the car indexed by i, the others are initialized at 0.
 */
void init(int i, int name);

/*
 * Reset car's scores indexed by i
 * @pre : i the index of the tab containing all the cars
 * @post : all variable are reset except the car's name.
 */
void reset(int i);

#endif
