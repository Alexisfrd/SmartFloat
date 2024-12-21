#include "SEN0208.h"
#include <Arduino.h>
#include "../config.h"

/**
 * init Capteur ultrason SEN0208
 */
void init_SEN0208(){
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}


int get_distance(){
  digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH); // Send a 10uS high to trigger ranging
  delayMicroseconds(20);
  digitalWrite(TRIGPIN, LOW); // Send pin low again
  int distance = pulseIn(ECHOPIN, HIGH)/58; // Read in times pulse
  //Serial.println(distance);
  //Serial.print(distance);
  //Serial.println("   cm");                   
  delay(50);// Wait 50mS before next ranging
  return distance;
}

int average_distance() {
  int somme = 0;
  for (int i = 0; i < 100; i++) {
    somme += get_distance();
  }
  int moyenne = somme / 100;
  Serial.print("Moyenne: ");
  Serial.println(moyenne);
  return moyenne;
}
    

