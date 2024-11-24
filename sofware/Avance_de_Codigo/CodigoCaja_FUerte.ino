#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <Keypad.h>
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { 'D','C','B','A'},
   { '#','9','6','3'},
   { '0','8','5','2'},
   { '*','7','4','1'}
};
 
const byte rowPins[rowsCount] = { 9, 8, 7, 6 };
const byte columnPins[columsCount] = { 5, 4, 3, 2 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

bool entrada = 0;


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  // Indicar a la libreria que tenemos conectada una pantalla de 16x2
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.home ();
  // Imprimir "Hola Mundo" en la primera linea
  lcd.print("CAJA CERRADA");
  // Mover el cursor a la segunda linea (1) primera columna
  lcd.setCursor ( 0, 1 );
  // Imprimir otra cadena en esta posicion
  lcd.print("Presione D:");
  // Esperar un segundo
  delay(1000);
  Serial.begin(9600);
  
  
}
String pin = "1234000000000000";
char base[] = {'0','0','0','0','0','0','0','0'};
String c="r";
int i = 0;
void loop()
{
  char key = keypad.getKey();

 
   if (key)
   {
      if(entrada == 1)
      {
        if(key == 'D')
        {
          //si es ENTER
          i=0;
          c = String(base);
          Serial.println(c);
        }
        if(key == 'C')
        {
          Limpiar();
          i = 0;
        }
        else
        {
          
          lcd.print(key);
          base[i]= key;
          i=i+1;
          //Serial.println(base);
        }
        
      }
      if((key == 'D')&&(entrada == 0))
      {
        lcd.clear();
        lcd.home();
        lcd.print("Ingrese Pin:");
        lcd.setCursor(0,1);
        //Serial.println(base);
        entrada = 1;
        //lcd.print("-");
        //key = '>';
      }
      
      Serial.println(key);
   }
}


void Limpiar()
{
  lcd.clear();
  lcd.home();
  lcd.print("Ingrese Pin:");
  lcd.setCursor(0,1);
}
