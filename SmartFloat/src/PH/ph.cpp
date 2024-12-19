#include "ph.h"
#include "../config.h"



void initPH() {
    // Code d'initialisation pour le capteur de pH
    // Par exemple, initialiser les broches, les bibliothèques, etc.
}


float readPH() {
    // Code pour lire la valeur de pH à partir du capteur
    // Par exemple, lire une valeur analogique et la convertir en pH
    int sensorValue = analogRead(PH_PIN);
    Serial.println("====================================");
    Serial.print("analogRead: ");
    Serial.println(sensorValue);

    float voltage = (sensorValue / 4095.0) * 5;
    Serial.print("voltage: ");
    Serial.println(voltage);

    float Current = voltage / 0.25;
    Serial.print("Current: ");
    Serial.println(Current);

    //float pHValue = 7 + ((2.5 - voltage) / 0.18); // Ajustez la formule selon votre sonde
    //float pHValue = ph.readPH(voltage,25);
    float pHValue = (Current- 3.539) / 1.2902 ;
    Serial.print("pH Value: ");
    Serial.println(pHValue);
    return pHValue;
}


void calibratePH(float calibrationValue) {
    // Code pour calibrer le capteur de pH

}