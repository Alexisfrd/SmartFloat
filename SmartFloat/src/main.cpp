#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include <ESP32Ping.h> // Assurez-vous d'avoir installé la bibliothèque ESP32Ping
#include <ArduinoJson.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <OneWire.h>
#include "SEN0208/SEN0208.h"
#include "WIFI/wifiproject.h"
#include "HTTP/http.h"

#define SENSOR_PIN  16 // GPIO15
#define ECHOPIN 2 // Pin to receive echo pulse
#define TRIGPIN 15 // Pin to send trigger pulse

String derniereDate = ""; // Initialisation de derniereDate


int dist = 0;
int phValue = 0;
float doValue = 0; 

String dateString = "";

/**
 * Config Capteur de température DS18B20
 */
float Temperature = 0;
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

enum STEP {
  DI = 0,
  PH,
  TEMP,
  SEND,
  SLEEP
} step;

void setup() {
  // Initialisation de la communication série
  Serial.begin(115200);

  init_Wifi();
  
  // Initialiser le générateur de nombres aléatoires
  randomSeed(analogRead(32));

  // Configurer l'heure
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

/**
 * init Capteur de température DS18B20
 */

  DS18B20.begin();
  Wire.begin();

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);


}

void loop() {
  
  switch (step)
  {
    case DI:
      dist = distance();
      Serial.print("Distance: ");
      Serial.println(dist);
      step = PH;
      break;

    case PH:
      Serial.print("PH, ");
      step = TEMP;
      break;

    case TEMP:
      DS18B20.requestTemperatures();
      Temperature = DS18B20.getTempCByIndex(0);
      
      Serial.print("TEMP, ");
      step = SEND;
      break;
    
    case SEND:
      dateString = getFormattedDate();

      doValue = random(0, 1001) / 100.0; // à retirer quand bckend finit
      handleLoginAndSendData("DO", doValue, dateString, "DO", "pass", 0); // à retirer quand bckend finit

      handleLoginAndSendData("PH", phValue, dateString, "PH", "pass1", 1);
      handleLoginAndSendData("TEMP", Temperature, dateString, "TEMP", "pass2", 2);
      handleLoginAndSendData("DEBIT", dist, dateString, "DEBIT", "pass3", 3);

      Serial.print("SEND, ");
      step = SLEEP;
      break;

    case SLEEP:
      Serial.println("SLEEP");
      delay(1000);
      step = DI;
      break;
    
    default:
      Serial.println("default");
      break;
  }

/*
  distance();
  delay(1000); // Attendre une seconde avant de générer de nouvelles données

  // Mettre le microcontrôleur en mode sommeil pendant 10 secondes
  Serial.println("Entrée en mode sommeil pendant 10 secondes...");
  esp_sleep_enable_timer_wakeup(10 * 1000000); // 10 secondes en microsecondes
  esp_light_sleep_start();
  Serial.println("Réveil du mode sommeil");
*/
}

