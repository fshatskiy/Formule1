#ifndef course_h
#define course_h

#include "voiture.h"

/*
 * Trie la table Voitures sur base du temps actuel et du num du tour
 * @pre : voituresCourse not null
 * @post : modifie voituresCourse
 */
void triVoituresEnFctTemps(structTuture voituresCourse[]);

/*
 * Lance la course sur la Tuture
 * @pre : tuture est référencé par l'index (is not null)
 * @post : modifie les valeurs dans la structure Tuture
 */
void course(int index);

/*
 * Creates the file with the recap of the course
 * @pre : voitures not null
 * @post : creates a file with all the infos needed
 */
void genereRecapCourseFile();

#endif /* course_h */
