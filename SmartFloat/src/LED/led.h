#ifndef LED_H
#define LED_H

#include <Arduino.h>

void ledInit();
void ledSend();
void ledConnecteWifi();
void ledPingOk();
void ledPingFail();

#endif // LD_H