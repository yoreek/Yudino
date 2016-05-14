#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <Heater/RegulatedHeater.h>

void RegulatedHeater::maintain() {
    if (_regulated) {
        _maintainTemperature();
    }
}

void RegulatedHeater::_maintainTemperature() {
    float actualTemperature;

    if (!_temperatureSensor->update())
        return;

    actualTemperature = _temperatureSensor->getTemperature();
    if (isTurnedOn()) {
        if (actualTemperature > (_targetTemperature + _hysteresis)) {
            turnOff();
        }
    }
    else {
        if (actualTemperature < (_targetTemperature - _hysteresis)) {
            turnOn();
        }
    }
}

TemperatureSensor *RegulatedHeater::getTemperatureSensor() {
    return _temperatureSensor;
}

void RegulatedHeater::setHysteresis(float hysteresis) {
    _hysteresis = hysteresis;
}

float RegulatedHeater::getHysteresis() {
    return _hysteresis;
}

void RegulatedHeater::setTargetTemperature(float targetTemperature) {
    _targetTemperature = targetTemperature;
}

float RegulatedHeater::getTargetTemperature() {
    return _targetTemperature;
}

void RegulatedHeater::setRegulate(bool regulate) {
    _regulated = regulate;
}

bool RegulatedHeater::isRegulated() {
    return _regulated;
}
