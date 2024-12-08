#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

// Configuración del UART2 del ESP32
HardwareSerial mySerial(2); // UART2
Adafruit_Fingerprint finger(&mySerial);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Inicializando sensor de huellas dactilares...");

  mySerial.begin(57600, SERIAL_8N1, 16, 17); // Baudrate: 57600, RX: GPIO16, TX: GPIO17
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor de huellas conectado correctamente.");
  } else {
    Serial.println("Error al conectar con el sensor. Verifique las conexiones.");
    while (1); // Detiene el programa si no se conecta
  }

  Serial.println("\nOpciones:");
  Serial.println("1: Registrar huella");
  Serial.println("2: Reconocer huella");
}

void loop() {
  if (Serial.available()) {
    char option = Serial.read();
    if (option == '1') {
      Serial.println("Opción seleccionada: Registrar huella.");
      registerFingerprint(1); // Registrar huella con ID 1
    } else if (option == '2') {
      Serial.println("Opción seleccionada: Reconocer huella.");
      recognizeFingerprint(); // Reconocer huella
    } else {
      Serial.println("Opción no válida. Introduzca '1' o '2'.");
    }
  }
}

// Función para registrar una huella en 10 pasos con dos capturas por paso
void registerFingerprint(int id) {
  Serial.print("Comenzando el registro de huella para ID ");
  Serial.println(id);

  for (int step = 1; step <= 10; step++) {
    Serial.print("Paso ");
    Serial.print(step);
    Serial.println(" de 10: Coloca tu dedo.");

    // Captura 1
    while (finger.getImage() != FINGERPRINT_OK) {
      Serial.println("Coloca tu dedo correctamente...");
      delay(500);
    }
    if (finger.image2Tz(1) != FINGERPRINT_OK) {
      Serial.println("Error al procesar la primera captura. Inténtalo de nuevo.");
      step--; // Reintenta este paso
      continue;
    }
    Serial.println("Primera captura completada. Retira el dedo.");

    delay(2000); // Espera para levantar el dedo

    // Captura 2
    Serial.println("Coloca nuevamente tu dedo.");
    while (finger.getImage() != FINGERPRINT_OK) {
      Serial.println("Coloca tu dedo correctamente...");
      delay(500);
    }
    if (finger.image2Tz(2) != FINGERPRINT_OK) {
      Serial.println("Error al procesar la segunda captura. Inténtalo de nuevo.");
      step--; // Reintenta este paso
      continue;
    }
    Serial.println("Segunda captura completada.");

    // Crear el modelo
    if (finger.createModel() != FINGERPRINT_OK) {
      Serial.println("Error al combinar las capturas. Inténtalo de nuevo.");
      step--; // Reintenta este paso
      continue;
    }
    Serial.println("Paso completado. Retira el dedo.");
    delay(2000); // Pausa para levantar el dedo
  }

  // Guardar el modelo en la memoria
  if (finger.storeModel(id) == FINGERPRINT_OK) {
    Serial.println("Huella registrada exitosamente.");
  } else {
    Serial.println("Error al guardar la huella. Inténtalo de nuevo.");
  }
}

// Función para reconocer una huella
void recognizeFingerprint() {
  Serial.println("Coloca tu dedo para reconocimiento...");

  while (finger.getImage() != FINGERPRINT_OK) {
    Serial.println("Coloca tu dedo correctamente...");
    delay(500);
  }

  if (finger.image2Tz() != FINGERPRINT_OK) {
    Serial.println("No se pudo convertir la imagen.");
    return;
  }

  int id = finger.fingerFastSearch();
  if (id == FINGERPRINT_OK) {
    Serial.print("Huella reconocida con ID ");
    Serial.println(finger.fingerID);
  } else {
    Serial.println("Huella no reconocida.");
  }
}
