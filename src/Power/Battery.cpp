#include "Battery.h"

void Battery::begin(void) {
    _sensor->begin();
}

float Battery::level(void) {
    float v = _sensor->voltage();

    if (v <= _minVoltage ) {
        return 0;
    }

    if (v >= _maxVoltage) {
        return 100;
    }

    return (v - _minVoltage) * 100 / (_maxVoltage - _minVoltage);
}
