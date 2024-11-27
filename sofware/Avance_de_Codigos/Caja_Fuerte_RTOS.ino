#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Arduino_FreeRTOS.h>

// Configuración del teclado
const byte rowsCount = 4;
const byte columsCount = 4;

char keys[rowsCount][columsCount] = {
    {'D', 'C', 'B', 'A'},
    {'#', '9', '6', '3'},
    {'0', '8', '5', '2'},
    {'*', '7', '4', '1'}
};

const byte rowPins[rowsCount] = {9, 8, 7, 6};
const byte columnPins[columsCount] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

// Configuración del LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Variables compartidas
String pin = "1234";
char base[8] = {'0', '0', '0', '0', '0', '0', '0', '0'};
int i = 0;
bool entrada = 0;
String c = "r";

// Mutex para proteger recursos compartidos
SemaphoreHandle_t lcdMutex;

// Prototipos de tareas
void vTaskReadKeypad(void *pvParameters);
void vTaskUpdateLCD(void *pvParameters);
void vTaskValidatePin(void *pvParameters);

// Función de inicialización
void setup()
{
    Serial.begin(9600);

    // Configuración del LCD
    lcd.begin(16, 2);
    lcd.home();
    lcd.print("CAJA CERRADA");
    lcd.setCursor(0, 1);
    lcd.print("Presione D:");

    // Crear Mutex
    lcdMutex = xSemaphoreCreateMutex();

    // Crear tareas
    xTaskCreate(vTaskReadKeypad, "ReadKeypad", 128, NULL, 1, NULL);
    xTaskCreate(vTaskUpdateLCD, "UpdateLCD", 128, NULL, 1, NULL);
    xTaskCreate(vTaskValidatePin, "ValidatePin", 128, NULL, 1, NULL);
}

// Bucle principal vacío, FreeRTOS gestionará las tareas
void loop()
{
}

// Tarea: Leer el teclado
void vTaskReadKeypad(void *pvParameters)
{
    char key;

    while (true)
    {
        key = keypad.getKey();
        if (key)
        {
            Serial.println(key);

            if (entrada == 1)
            {
                if (key == 'D') // Validar PIN
                {
                    c = String(base);
                    i = 0;
                }
                else if (key == 'C') // Limpiar entrada
                {
                    memset(base, '0', sizeof(base));
                    i = 0;
                }
                else
                {
                    if (i < sizeof(base))
                    {
                        base[i] = key;
                        i++;
                    }
                }
            }
            else if ((key == 'D') && (entrada == 0))
            {
                entrada = 1;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Esperar 100 ms
    }
}

// Tarea: Actualizar la pantalla LCD
void vTaskUpdateLCD(void *pvParameters)
{
    while (true)
    {
        xSemaphoreTake(lcdMutex, portMAX_DELAY);

        if (entrada == 0)
        {
            lcd.clear();
            lcd.home();
            lcd.print("CAJA CERRADA");
            lcd.setCursor(0, 1);
            lcd.print("Presione D:");
        }
        else
        {
            lcd.clear();
            lcd.home();
            lcd.print("Ingrese Pin:");
            lcd.setCursor(0, 1);
            for (int j = 0; j < i; j++)
            {
                lcd.print(base[j]);
            }
        }

        xSemaphoreGive(lcdMutex);
        vTaskDelay(pdMS_TO_TICKS(200)); // Actualizar cada 200 ms
    }
}

// Tarea: Validar el PIN ingresado
void vTaskValidatePin(void *pvParameters)
{
    while (true)
    {
        if (entrada == 1 && c == pin)
        {
            xSemaphoreTake(lcdMutex, portMAX_DELAY);
            lcd.clear();
            lcd.home();
            lcd.print("PIN Correcto!");
            lcd.setCursor(0, 1);
            lcd.print("Caja Abierta");
            xSemaphoreGive(lcdMutex);

            entrada = 0; // Reiniciar estado
            vTaskDelay(pdMS_TO_TICKS(5000)); // Mantener mensaje 5s
        }

        vTaskDelay(pdMS_TO_TICKS(100)); // Revisar cada 100 ms
    }
}
