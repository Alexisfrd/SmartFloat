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
  
}

void handlePushDataResponse(String response) {

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