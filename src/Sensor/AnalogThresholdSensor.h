#pragma once
#ifndef _ANALOG_THRESHOLD_SENSOR_H_
#define _ANALOG_THRESHOLD_SENSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <inttypes.h>
#include <Sensor/CachedMeasure.h>

#define ANALOG_THRESHOLD_SENSOR_THRESHOLD  0.5

class AnalogThresholdSensor : public CachedMeasure {
    public:
        AnalogThresholdSensor(
            uint8_t  sensorPin,
            float    threshold      = ANALOG_THRESHOLD_SENSOR_THRESHOLD,
            uint8_t  measureSamples = CACHED_MEASURE_NUM_SAMPLES,
            uint16_t expireTime     = CACHED_MEASURE_EXPIRE_TIME) :
            CachedMeasure(measureSamples, expireTime),
            _sensorPin(sensorPin),
            _threshold(threshold)
        {
        };
        void begin(void);
        bool getRealValue(float *value);
        bool isExceedsThreshold(void);

    private:
        uint8_t _sensorPin;
        float   _threshold;
};

#endif // _ANALOG_THRESHOLD_SENSOR_H_
