#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor de huella conectado!");
  } else {
    Serial.println("Error al conectar el sensor");
    while (1);
  }
}

void loop() {
  Serial.println("Coloque su dedo");
  int result = finger.getImage();
  if (result == FINGERPRINT_OK) {
    Serial.println("Huella detectada!");
  } else {
    Serial.println("Intente de nuevo");
  }
  delay(1000);
}
