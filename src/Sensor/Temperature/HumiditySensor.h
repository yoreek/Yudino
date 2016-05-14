#pragma once
#ifndef _HUMIDITY_SENSOR_H_
#define _HUMIDITY_SENSOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include "CachedMeasure.h"

class HumiditySensor {
    public:
        virtual float getHumidity(void);
};

class HumiditySensorCached : public HumiditySensor, public CachedMeasure {
    public:
        HumiditySensorCached(
            uint8_t  measureSamples = CACHED_MEASURE_NUM_SAMPLES,
            uint16_t expireTime     = CACHED_MEASURE_EXPIRE_TIME
        ) : CachedMeasure(measureSamples, expireTime)
        {};
};

#endif
