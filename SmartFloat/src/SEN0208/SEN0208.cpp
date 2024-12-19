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

int once_Distance(){
  digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH); // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW); // Send pin low again
  int mesure = pulseIn(ECHOPIN, HIGH,26000); // Read in times pulse
  mesure = mesure / 58;
  //Serial.print(distance);
  //Serial.println("   cm");                   
  delay(50);// Wait 50mS before next ranging
  return mesure;
}

int distance(){
  int moyenne = 0;
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low for 2uS
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH); // Send a 10uS high to trigger ranging
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW); // Send pin low again
    int distance = pulseIn(ECHOPIN, HIGH, 26000); // Read in times pulse
    moyenne = (distance / 58) + moyenne;                  
    delay(50);// Wait 50mS before next ranging
  }
  moyenne = moyenne / 10;
  return moyenne;
  //Serial.print(moyenne);
  //Serial.println("   cm");
}

int distance_mode_0(){
  digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH); // Send a 10uS high to trigger ranging
  delayMicroseconds(20);
  digitalWrite(TRIGPIN, LOW); // Send pin low again
  int distance = pulseIn(ECHOPIN, HIGH)/58; // Read in times pulse
  //Serial.println(distance);
  Serial.print(distance);
  Serial.println("   cm");                   
  delay(50);// Wait 50mS before next ranging
  return distance;
}

int distance_mode_4(){
  digitalWrite(TRIGPIN, LOW); // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH); // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW); // Send pin low again
  int distance = pulseIn(ECHOPIN, HIGH,26000); // Read in times pulse
  distance= distance/58;
  Serial.print(distance);
  Serial.println("   cm");                   
  delay(50);// Wait 50mS before next ranging
  return distance;
}