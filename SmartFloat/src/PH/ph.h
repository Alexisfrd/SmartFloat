#ifndef PH_H
#define PH_H

#include <Arduino.h>

// Déclaration des fonctions
void initPH();
float readPH();
void calibratePH(float calibrationValue);

#endif // PH_H