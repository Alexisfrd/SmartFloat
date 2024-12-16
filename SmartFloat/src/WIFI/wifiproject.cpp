#include "wifiproject.h"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Ping.h> // Assurez-vous d'avoir installé la bibliothèque ESP32Ping




// Remplacez par vos informations de réseau
//const char* ssid = "Livebox-EAC0";
//const char* password = "gaAhxFhjDJeXYpWRgH";
const char* ssid = SSID1;
const char* password = PASSWORD;
// Adresse du serveur
const char* serverName = SERVERNAME; // Utilisez uniquement l'adresse IP sans le protocole
const IPAddress remote_ip(192,168,1,189);


void init_Wifi(){
  // Connexion au WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
  Serial.println("Connecté au WiFi");

  // Afficher l'adresse IP
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());


  // Vérifier la connectivité avec le serveur
  Serial.print("Pinging server: ");
  Serial.println(serverName);
  if (Ping.ping(remote_ip)) {
    Serial.println("Ping successful");
  } else {
    Serial.println("Ping failed");
  }
}