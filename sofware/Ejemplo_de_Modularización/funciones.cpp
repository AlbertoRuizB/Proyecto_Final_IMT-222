#include "funciones.h"
#include <Arduino.h>

void serialInit() {
    Serial.begin(BAUDRATE);
    pinMode(LEDPIN, OUTPUT);
    Serial.println("Introduce un número para controlar el LED:");
}

void OnOff(int x, int y) {
    char z = recibirDatos();  

    if (z == '1') {
        encenderLED(HIGH);
        Serial.println("LED Encendido");
    } else if (z == '0') {
        encenderLED(LOW);
        Serial.println("LED Apagado");
    } else {
        Serial.println("Introduce '1' para encender o '0' para apagar el LED");
    }

    delay(x);
}

void encenderLED(bool estado) {
    digitalWrite(LEDPIN, estado);
}

char recibirDatos() {
    if (Serial.available() > 0) {
        return Serial.read();  
    }
    return '\0';  
