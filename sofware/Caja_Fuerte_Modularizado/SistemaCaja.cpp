// SistemaCaja.cpp

#include "SistemaCaja.h"

// Definiciones de las variables globales
const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {25, 26, 27, 14}; // Pines para las filas
byte colPins[COLS] = {16, 17, 18, 19}; // Pines para las columnas

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

// Variables de estado
bool cajaAbierta = false;
int intentosFallidos = 0;

void inicializarSistema() {
  // Configurar Serial, LCD, EEPROM y servomotor
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  servo.attach(SERVO_PIN);
  servo.write(SERVO_CLOSED_ANGLE);
  EEPROM.begin(EEPROM_SIZE);

  // Mostrar opciones iniciales
  mostrarOpcionesIniciales();
}

void gestionarMenu() {
  char opcion = keypad.getKey();
  if (opcion) {
    Serial.print("Botón presionado: ");
    Serial.println(opcion);

    if (!cajaAbierta) {
      switch (opcion) {
        case 'A':
          desbloquearCaja();
          break;
        case 'B':
          cambiarClave();
          break;
      }
    } else if (opcion == 'C') {
      cerrarCaja();
    }
  }
}

void desbloquearCaja() {
  if (intentosFallidos >= MAX_INTENTOS) {
    bloquearSistema();
    return;
  }

  lcd.clear();
  lcd.print("Ingrese clave:");
  String claveIngresada = leerClave();
  String claveGuardada = leerClaveEEPROM();

  if (claveIngresada == claveGuardada) {
    lcd.clear();
    lcd.print("Acceso permitido");
    abrirCaja();
  } else {
    lcd.clear();
    lcd.print("Clave incorrecta");
    intentosFallidos++;
    delay(2000);
    mostrarOpcionesIniciales();
  }
}

void cambiarClave() {
  lcd.clear();
  lcd.print("Clave actual:");
  String claveIngresada = leerClave();
  String claveGuardada = leerClaveEEPROM();

  if (claveIngresada == claveGuardada) {
    lcd.clear();
    lcd.print("Nueva clave:");
    String nuevaClave = leerClave();
    guardarClaveEEPROM(nuevaClave);
    lcd.clear();
    lcd.print("Clave actualizada");
    delay(2000);
  } else {
    lcd.clear();
    lcd.print("Clave incorrecta");
    delay(2000);
  }
  mostrarOpcionesIniciales();
}

void cerrarCaja() {
  lcd.clear();
  lcd.print("Cerrando Caja");
  servo.write(SERVO_CLOSED_ANGLE);
  cajaAbierta = false;
  delay(2000);
  mostrarOpcionesIniciales();
}

void abrirCaja() {
  servo.write(SERVO_OPEN_ANGLE);
  cajaAbierta = true;
  delay(2000);
  mostrarOpcionCerrar();
}

void bloquearSistema() {
  lcd.clear();
  lcd.print("Sistema bloqueado");
  delay(BLOQUEO_MS);
  intentosFallidos = 0; // Resetear intentos tras el bloqueo
  mostrarOpcionesIniciales();
}

String leerClave() {
  String clave = "";
  while (clave.length() < 4) {
    char tecla = keypad.getKey();
    if (tecla) {
      lcd.print("*"); // Mostrar asterisco para cada dígito
      Serial.print("Tecla presionada: ");
      Serial.println(tecla);
      clave += tecla;
    }
  }
  delay(1000);
  return clave;
}

void mostrarOpcionesIniciales() {
  lcd.clear();
  lcd.print("A: Abrir Caja");
  lcd.setCursor(0, 1);
  lcd.print("B: Cambiar Clave");
}

void mostrarOpcionCerrar() {
  lcd.clear();
  lcd.print("C: Cerrar Caja");
}

String leerClaveEEPROM() {
  String clave = "";
  for (int i = EEPROM_START_ADDR; i < EEPROM_START_ADDR + 4; i++) {
    char c = EEPROM.read(i);
    if (c != 255) {
      clave += c;
    }
  }
  return clave.length() == 4 ? clave : "1234"; // Valor por defecto si no hay clave
}

void guardarClaveEEPROM(String clave) {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(EEPROM_START_ADDR + i, clave[i]);
  }
  EEPROM.commit();
}
