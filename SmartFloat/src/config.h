#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define TEMP_PIN  16 // GPIO15
#define ECHOPIN 2 // Pin to receive echo pulse
#define TRIGPIN 15 // Pin to send trigger pulse
#define PH_PIN   12 // GPIO12

#define SERVERNAME "192.168.1.189"
#define PASSWORD "5vCMZAn4pd3b"
#define SSID1 "Airbox-33EE"

#define HTTP 0

struct sensorData
{
  /* data */
  int dist = 0;
  int phValue = 0;
  float doValue = 0; 
  float Temperature = 0;
};



#endif // CONFIG_H