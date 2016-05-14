#pragma once
#ifndef _CACHED_MEASURE_H_
#define _CACHED_MEASURE_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>

#define CACHED_MEASURE_NUM_SAMPLES 3
#define CACHED_MEASURE_EXPIRE_TIME 1000

class CachedMeasure {
    public:
        CachedMeasure(
            uint8_t  measureSamples = CACHED_MEASURE_NUM_SAMPLES,
            uint16_t expireTime     = CACHED_MEASURE_EXPIRE_TIME):
            _measureSamples(measureSamples),
            _expireTime(expireTime),
            _timeNextUpdate(0)
        {};

        virtual bool update(bool forceUpdate = false);
        virtual float getValue(void) {
            return _value;
        };
        virtual bool getRealValue(float *value);

    private:
        uint8_t  _measureSamples;
        uint16_t _expireTime;
        uint16_t _timeNextUpdate;
        float    _value;
};

#endif
