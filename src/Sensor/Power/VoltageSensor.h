#pragma once
#ifndef _VOLTAGE_SENSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <inttypes.h>
#include <Sensor/CachedMeasure.h>

#define VOLTAGE_SENSOR_DIVIDER_RATIO  1.0
#define VOLTAGE_SENSOR_ADC_REF        5.0   // 5V

class VoltageSensor : public CachedMeasure {
    public:
        VoltageSensor(
            uint8_t  sensorPin,
            float    dividerRatio   = VOLTAGE_SENSOR_DIVIDER_RATIO,
            float    adcRef         = VOLTAGE_SENSOR_ADC_REF,
            uint8_t  measureSamples = CACHED_MEASURE_NUM_SAMPLES,
            uint16_t expireTime     = CACHED_MEASURE_EXPIRE_TIME) :
            CachedMeasure(measureSamples, expireTime),
            _sensorPin(sensorPin),
            _dividerRatio(dividerRatio),
            _adcRef(adcRef)
        {
        };
        void begin(void);
        bool getRealValue(float *value);
        inline float voltage(void) {
            return getValue();
        };

    private:
        uint8_t _sensorPin;
        float   _dividerRatio;
        float   _adcRef;
};

#endif // _VOLTAGE_SENSOR_H_
