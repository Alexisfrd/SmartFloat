#ifndef HTTP_H
#define HTTP_H

#include <Arduino.h> // Ajoutez cette ligne pour définir String



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

#endif // HTTP_H