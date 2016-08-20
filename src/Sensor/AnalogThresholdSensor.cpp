#include "AnalogThresholdSensor.h"

#define ADC_MAX 1023

void AnalogThresholdSensor::begin(void) {
    pinMode(_sensorPin, INPUT);
}

bool AnalogThresholdSensor::getRealValue(float *value) {
    analogRead(_sensorPin);

    delay(2);

    *value = (float) analogRead(_sensorPin) / ADC_MAX;

    return true;
}

bool AnalogThresholdSensor::isExceedsThreshold(void) {
    return getValue() >= _threshold;
}
