#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include "Heater.h"

const char *Heater::name() {
    return _name;
}

bool Heater::isTurnedOn() {
    return _relay->isTurnedOn();
}

void Heater::turnOn() {
    _relay->turnOn();
}

void Heater::turnOff() {
    _relay->turnOff();
}
