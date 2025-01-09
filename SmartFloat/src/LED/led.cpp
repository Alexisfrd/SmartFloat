#include "led.h"
#include "../config.h"



void ledInit() {
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);
}


void ledSend() {
    digitalWrite(LED_PIN_1, HIGH);
    delay(100);
    digitalWrite(LED_PIN_1, LOW);
    delay(100);
    digitalWrite(LED_PIN_1, HIGH);
    delay(100);
    digitalWrite(LED_PIN_1, LOW);
    delay(100);
    digitalWrite(LED_PIN_1, HIGH);
    delay(100);
    digitalWrite(LED_PIN_1, LOW); 
}
