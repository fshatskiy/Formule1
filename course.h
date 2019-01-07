#ifndef course_h
#define course_h

#include "voiture.h"

/*
 * Trie la table Voitures sur base du temps actuel et du nb du tour
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
 * Crée le fichier avec le récap de la course
 * @pre : voitures not null
 * @post : Crée le fichier avec toutes les infos dont on a besoin
 */
void genereRecapCourseFile();

#endif /* course_h */
