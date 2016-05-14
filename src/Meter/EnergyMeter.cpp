#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "EnergyMeter.h"

// Update running time
void EnergyMeter::update(bool isTurnedOn) {
    uint32_t now;

    if (isTurnedOn) {
        now = millis();
        if (now < _lastCalculate) {
            _lastCalculate = 0;
        }
        _runningTime   += (now - _lastCalculate) / 1000;
        _lastCalculate  = now;
    }
    else {
        _lastCalculate = millis();
    }
}

// Return the power consumption in kWh
float EnergyMeter::getPowerConsumption() {
    return (float) _runningTime * _power / 3600 / 1000;
}
