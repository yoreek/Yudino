#pragma once
#ifndef __ROTARY_ENCODER_H__
#define __ROTARY_ENCODER_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Encoder.h"
#include <Core/Pin.h>
#include <inttypes.h>

class RotaryEncoder: public Encoder {
    public:
        RotaryEncoder(
                uint8_t pinA,
                uint8_t pinB,
                bool    pullUp       = false,
                bool    reverse      = false,
                int32_t initialValue = 0,
                int32_t minValue     = INT32_MIN,
                int32_t maxValue     = INT32_MAX) :
            Encoder(initialValue),
            _pinA(pinA, pullUp),
            _pinB(pinB, pullUp),
            _reverse(reverse),
            _min(minValue),
            _max(maxValue)
        {
        };
        inline int32_t minValue() {
            return _min;
        };
        inline int32_t maxValue() {
            return _max;
        };
        void updateA();
        void updateB();

    private:
        InputPin _pinA;
        InputPin _pinB;
        bool     _reverse;
        int32_t  _min;
        int32_t  _max;

        inline void _updateAB(uint8_t invert);
};

#endif // __ROTARY_ENCODER_H__
