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

#define SENSOR_PIN  16 // GPIO15
#define ECHOPIN 2 // Pin to receive echo pulse
#define TRIGPIN 15 // Pin to send trigger pulse

String derniereDate = ""; // Initialisation de derniereDate


int dist = 0;
int phValue = 0;

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

/*
  Prototype de fonctions
*/
void POST(String jdata, String url, std::function<void(String)> callback);
void sendData(String sensorName, float sensorValue, String dateString, String token, int target);
void handleLoginAndSendData(String sensorName, float sensorValue, String dateString, String login, String password, int target);
String parseToken(String response);
String getFormattedDate();
void generateRandomData();
void handleLoginResponse(String response);
void handlePushDataResponse(String response);



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
      generateRandomData();
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
      handleLoginAndSendData("DISTANCE", dist, dateString, "DEBIT", "pass3", 3);
      //handleLoginAndSendData("PH", phValue, dateString, "PH", "pass1", 1);
      //handleLoginAndSendData("TEMP", Temperature, dateString, "TEMP", "pass2", 2);
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


void POST(String jdata, String url, std::function<void(String)> callback) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String fullUrl = String("http://") + SERVERNAME + ":3000" + url;
    //Serial.print("Connexion à l'URL : ");
    //Serial.println(fullUrl);
    http.begin(fullUrl);
    http.addHeader("Content-Type", "application/json");

    //Serial.print("Envoi des données JSON : ");
    //Serial.println(jdata);

    int httpResponseCode = http.POST(jdata);

    if (httpResponseCode > 0) {
      String response = http.getString();
      //Serial.print("Réponse HTTP : ");
      //Serial.println(response);
      callback(response);
    } else {
      Serial.print("Erreur lors de l'envoi de la requête POST : ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi non connecté");
  }
}

void sendData(String sensorName, float sensorValue, String dateString, String token, int target) {
  String data = "{\"name\":\"" + sensorName + "\",\"value\":" + String(sensorValue) + ",\"date\":\"" + dateString + "\"}";
  String jdata = "{\"token\":\"" + token + "\",\"data\":" + data + ",\"target\":" + String(target) + "}";

  POST(jdata, "/pushdata", handlePushDataResponse);
}

void handleLoginAndSendData(String sensorName, float sensorValue, String dateString, String login, String password, int target) {
  String jdata = "{\"login\":\"" + login + "\",\"password\":\"" + password + "\"}";

  // Définir un callback pour gérer la réponse de login et envoyer les données
  std::function<void(String)> handleLoginResponseAndSendData = [=](String response) {
    handleLoginResponse(response); // Traitez la réponse de login ici
    String token = parseToken(response); // Supposons que vous avez une fonction pour extraire le token de la réponse
    sendData(sensorName, sensorValue, dateString, token, target); // Envoyer les données après le login
  };

  POST(jdata, "/login", handleLoginResponseAndSendData);
}

void handleLoginResponse(String response) {
  // Traitez la réponse de la requête de login ici
  //Serial.print("Réponse de login : ");
  //Serial.println(response);
}

void handlePushDataResponse(String response) {
  // Traitez la réponse de la requête de push data ici
  //Serial.print("Réponse de push data : ");
  //Serial.println(response);
}

void generateRandomData() {
  float doValue = random(0, 1001) / 100.0;
  float phValue = random(0, 1401) / 100.0;
  //float tempValue = random(0, 4001) / 100.0;
  float debitValue = random(0, 10001) / 100.0;
  
  DS18B20.requestTemperatures();       // send the command to get temperatures
  Temperature = DS18B20.getTempCByIndex(0);  // read temperature in °C

  String dateString = getFormattedDate();

  if (derniereDate != dateString) {
    derniereDate = dateString;
    // Envoyer les données pour les trois sondes
    handleLoginAndSendData("DO", doValue, dateString, "DO", "pass", 0);
    handleLoginAndSendData("PH", phValue, dateString, "PH", "pass1", 1);
    handleLoginAndSendData("TEMP", Temperature, dateString, "TEMP", "pass2", 2);
    handleLoginAndSendData("DEBIT", debitValue, dateString, "DEBIT", "pass3", 3);
  }
}

String getFormattedDate() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", timeinfo);
  return String(buffer);
}
String parseToken(String response) {
  // Créez un objet JSON à partir de la réponse
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);

  // Extraire le token du document JSON
  const char* token = doc["token"];
  
  // Retourner le token comme une chaîne de caractères
  return String(token);
}