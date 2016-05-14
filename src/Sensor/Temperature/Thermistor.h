#pragma once
#ifndef _THERMISTOR_H_
#define _THERMISTOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include "TemperatureSensor.h"

#define THERMISTOR_NUM_SAMPLES 3
#define THERMISTOR_EXPIRE_TIME 1000

class Thermistor: public TemperatureSensorCached {
    public:
        Thermistor(
            uint8_t  sensorPin,
            uint16_t termistorNominal,
            uint16_t seriesResistor,
            int16_t  adcCorrection  = 0,
            uint8_t  measureSamples = THERMISTOR_NUM_SAMPLES,
            uint16_t expireTime     = THERMISTOR_EXPIRE_TIME
        ):
            TemperatureSensorCached(measureSamples, expireTime),
            _sensorPin(sensorPin),
            _termistorNominal(termistorNominal),
            _seriesResistor(seriesResistor),
            _adcCorrection(adcCorrection)
        {
            analogRead(_sensorPin);
        }

        bool getRealValue(float *value);
        float getTemperature(void) {
            return getValue();
        };

    private:
        uint8_t  _sensorPin;
        uint16_t _termistorNominal;
        uint16_t _seriesResistor;
        int16_t  _adcCorrection;
        uint16_t _rawData;
};

#endif
