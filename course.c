/*
PROJET
2018 raceWE
*/
#include "essaiLibre.h"
#include "utilitaire.h"
#include "qualif.h"
#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>


//INITIALISATION DES VOITURES
int c[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
