👩‍💻🌐💾 SOFTWARE:
Las buenas prácticas de programación son fundamentales para el desarrollo de software eficiente, legible y mantenible, 
especialmente en proyectos de sistemas embebidos, donde los recursos suelen ser limitados y las aplicaciones críticas. 
En el contexto del desarrollo con Arduino, estas prácticas permiten optimizar el rendimiento del hardware, reducir errores y facilitar la colaboración en equipos de trabajo.

El uso de bibliotecas en proyectos de Arduino es clave para simplificar tareas complejas y acelerar el desarrollo. 
Estas librerías ofrecen soluciones reutilizables y bien probadas para manejar sensores, actuadores, protocolos de comunicación y más. 
Sin embargo, es importante seleccionar y utilizar las bibliotecas adecuadas para evitar sobrecargar el sistema y mantener la estabilidad del proyecto.

Adoptar buenas prácticas en la escritura del código y el uso de librerías no solo asegura un diseño robusto y eficiente, sino que también facilita la escalabilidad y el mantenimiento del proyecto a largo plazo.

Para el presente proyecto se aplicara el uso de las buenas prácticas de programación, con la finalidad de que la lectura de este se vuelva rápido y facil de entender, a la vez de poder hacer modificar el codigo, manteniendo un orden establecido.

Para ello, cabe destacar se utilizan las siguientes librerias para poder tener un mejor control de los sensores y modulos a manipular:
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Adafruit-Fingerprint-Sensor-Library>
