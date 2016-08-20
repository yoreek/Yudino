#include "VoltageSensor.h"

#define ADC_MAX  1023

void VoltageSensor::begin(void) {
    pinMode(_sensorPin, INPUT);
}

bool VoltageSensor::getRealValue(float *value) {
    analogRead(_sensorPin);

    delay(2);

    *value = _adcRef * analogRead(_sensorPin) / ADC_MAX / _dividerRatio;

    return true;
}
