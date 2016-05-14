#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Relay.h"

void Relay::turnOn() {
    digitalWrite(_pin, _inverted ? LOW : HIGH);
    _turnedOn = true;
}

void Relay::turnOff() {
    digitalWrite(_pin, _inverted ? HIGH : LOW);
    _turnedOn = false;
}
