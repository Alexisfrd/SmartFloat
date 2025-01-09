#include "led.h"
#include "../config.h"



void ledInit() {
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);
}


void ledSend() {
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);

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

void ledConnecteWifi(){
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_3, LOW);

    digitalWrite(LED_PIN_2, HIGH);
    delay(100);
}

void ledPingOk(){
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_3, LOW);

    digitalWrite(LED_PIN_2, LOW);
    delay(100);
    digitalWrite(LED_PIN_2, HIGH);
    delay(100);
    digitalWrite(LED_PIN_2, LOW);
    delay(100);
    digitalWrite(LED_PIN_2, HIGH);
}

void ledPingFail(){
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    

    digitalWrite(LED_PIN_3, LOW);
    delay(100);
    digitalWrite(LED_PIN_3, HIGH);
    delay(100);
    digitalWrite(LED_PIN_3, LOW);
    delay(100);
    digitalWrite(LED_PIN_3, HIGH);
}

void ledTestRGB(){
#if 1
    digitalWrite(LED_PIN_1, HIGH);
    delay(1000);
    digitalWrite(LED_PIN_1, LOW);
    delay(1000);
#endif
#if 1
    digitalWrite(LED_PIN_2, HIGH);
    delay(1000);
    digitalWrite(LED_PIN_2, LOW);
    delay(1000);
#endif
#if 1
    digitalWrite(LED_PIN_3, HIGH);
    delay(1000);
    digitalWrite(LED_PIN_3, LOW);
    delay(1000);
#endif
}

