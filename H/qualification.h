#ifndef qualification_h
#define qualification_h

#include "voiture.h"

/*
 * Trie la table de voitures du base de bestCircuit
 * @pre : voituresQualif not null, sizeArrayCars==20 || sizeArrayCars==15 || sizeArrayCars==10
 * @post : modification de voituresQualif
 */
void triVoitures(structTuture voituresQualif[], int sizeArrayCars);

/*
 * Construction de la grille de départ
 * @pre : voituresQualif not null, q==1 || q==2 || q==3
 * @post : modification de la var startPosition
 */
void buildStartPosition(structTuture voituresQualif[], int q);

/*
 * Lance la qualif sur une voiture
 * @pre : tuture referenced by the index is not null, q==1 || q==2 || q==3
 * @post : modification des valeurs dans la structure de la voiture
 */
void qualif(int index, int q);

/*
 * Création du fichier avec le récapitulatif du qualif
 * @pre : /
 * @post : création du fichier avec toutes les informations nécessaires
 */
void genereRecapQualifFile();

#endif /* practice_h */

