#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C de la pantalla LCD, generalmente es 0x27 o 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 es el tamaño de la pantalla

void setup() {
  lcd.begin();
  lcd.backlight(); // Enciende la retroiluminación
  lcd.setCursor(0, 0); // Posiciona el cursor en la primera línea
  lcd.print("Hola, Mundo!"); // Muestra el mensaje en la primera línea
  lcd.setCursor(0, 1); // Cambia a la segunda línea
  lcd.print("I2C LCD Activo"); // Muestra otro mensaje
}

void loop() {
  // No se necesita código en el loop para este ejemplo básico
}
