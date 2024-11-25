#ifndef FUNCIONES_H
#define FUNCIONES_H

#define LEDPIN 5
#define BAUDRATE 9600
#define TIMEDELAY 1000

void serialInit();
void OnOff(int x, int y);
void encenderLED(bool estado); 
char recibirDatos();             

#endif
