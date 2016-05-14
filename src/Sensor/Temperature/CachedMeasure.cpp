#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include "CachedMeasure.h"

bool CachedMeasure::update(bool forceUpdate) {
    uint8_t i;
    float   v;

    if (forceUpdate || _timeNextUpdate == 0 || millis() >= _timeNextUpdate) {
        _value = 0.0;
        for (i = 0; i < _measureSamples; i++) {
            if (!getRealValue(&v))
                return false;
            _value += v;
        }
        _value          /= _measureSamples;
        _timeNextUpdate  = millis() + _expireTime;
    }

    return true;
}
