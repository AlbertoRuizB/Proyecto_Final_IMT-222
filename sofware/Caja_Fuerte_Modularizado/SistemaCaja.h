// SistemaCaja.h

#ifndef SISTEMACAJA_H
#define SISTEMACAJA_H

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <EEPROM.h>

// Configuración del teclado matricial
#define ROWS 4
#define COLS 4
#define EEPROM_SIZE 512
#define SERVO_PIN 13
#define EEPROM_START_ADDR 0
#define SERVO_OPEN_ANGLE 90
#define SERVO_CLOSED_ANGLE 0
#define MAX_INTENTOS 3
#define BLOQUEO_MS 10000

extern Keypad keypad;
extern LiquidCrystal_I2C lcd;
extern Servo servo;

// Funciones principales
void inicializarSistema();
void gestionarMenu();
void desbloquearCaja();
void cambiarClave();
void cerrarCaja();
void abrirCaja();
void bloquearSistema();
String leerClave();
void mostrarOpcionesIniciales();
void mostrarOpcionCerrar();
String leerClaveEEPROM();
void guardarClaveEEPROM(String clave);

#endif // SISTEMACAJA_H
