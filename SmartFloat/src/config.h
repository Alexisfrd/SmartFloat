#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define TEMP_PIN  16  // GPIO16
#define ECHOPIN   2   // Pin to receive echo pulse
#define TRIGPIN   15  // Pin to send trigger pulse
#define PH_PIN    12  // GPIO12
#define LED_PIN_1 4   // GPIO4
#define LED_PIN_2 17   // GPIO17
#define LED_PIN_3 18   // GPIO18

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