#pragma once
#ifndef __ENCODER_H__
#define __ENCODER_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>

class Encoder {
    public:
        Encoder(int32_t initialValue = 0) :
            _value(initialValue)
        {
        };
        inline int32_t getValue() {
            return _value;
        };
        void setValue(int32_t value) {
            cli();
            _value = value;
            sei();
        };
        inline void reset() {
            setValue(0);
        };

    protected:
        volatile int32_t  _value;
};

#endif // __ENCODER_H__
