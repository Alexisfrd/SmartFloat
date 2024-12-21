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
#include "PH/ph.h"
#include "config.h"

/**********************************************************/
/*                    variables globale                   */
/**********************************************************/

sensorData g_sensorData;

String dateString = "";
String derniereDate = ""; // Initialisation de derniereDate
int distance_test = 0;
/**********************************************************/
/*        Config Capteur de température DS18B20           */
/**********************************************************/

OneWire oneWire(TEMP_PIN);
DallasTemperature DS18B20(&oneWire);

/**********************************************************/
/*                      machine à état                    */
/**********************************************************/

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
#if HTTP == 1
  init_Wifi();
#endif
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
      Serial.print("DISTANCE, ");
      g_sensorData.dist = average_distance();
      step = PH;
      break;

    case PH:
      Serial.print("PH, ");
      g_sensorData.phValue = readPH();
      step = TEMP;
      break;

    case TEMP:
      Serial.print("TEMP, ");
      DS18B20.requestTemperatures();
      g_sensorData.Temperature = DS18B20.getTempCByIndex(0);
#if HTTP == 1
      step = SEND;
#else
      step = SLEEP;
#endif
      break;
    
    case SEND:
      dateString = getFormattedDate();

      g_sensorData.doValue = random(0, 1001) / 100.0; // à retirer quand backend finit
      handleLoginAndSendData("DO", g_sensorData.doValue, dateString, "DO", "pass", 0); // à retirer quand backend finit

      handleLoginAndSendData("PH", g_sensorData.phValue, dateString, "PH", "pass1", 1);
      handleLoginAndSendData("TEMP", g_sensorData.Temperature, dateString, "TEMP", "pass2", 2);
      handleLoginAndSendData("DEBIT", g_sensorData.dist, dateString, "DEBIT", "pass3", 3);

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

