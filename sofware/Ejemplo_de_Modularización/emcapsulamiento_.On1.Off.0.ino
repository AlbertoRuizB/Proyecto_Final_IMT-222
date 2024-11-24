#include "funciones.h"

void setup() {
    serialInit();
}

void loop() {
    OnOff(TIMEDELAY, LEDPIN);
}
