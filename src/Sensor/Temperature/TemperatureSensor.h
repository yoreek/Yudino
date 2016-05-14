#pragma once
#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include "CachedMeasure.h"

class TemperatureSensor {
    public:
        virtual float getTemperature(void);
};

class TemperatureSensorCached : public TemperatureSensor, public CachedMeasure {
    public:
        TemperatureSensorCached(
            uint8_t  measureSamples = CACHED_MEASURE_NUM_SAMPLES,
            uint16_t expireTime     = CACHED_MEASURE_EXPIRE_TIME
        ) : CachedMeasure(measureSamples, expireTime)
        {};
};

#endif
