#pragma once
#ifndef _RELAY_H_
#define _RELAY_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Relay {
    public:
        Relay(
            uint8_t pin,
            bool    inverted = false
        ) :
            _pin(pin),
            _inverted(inverted),
            _turnedOn(false)
        {
            pinMode(_pin, OUTPUT);
            turnOff();
        };
        virtual void turnOn();
        virtual void turnOff();
        virtual bool isTurnedOn() {
            return _turnedOn;
        };
        virtual bool isInverted() {
            return _inverted;
        };

    protected:
        uint8_t _pin;
        bool    _inverted;
        bool    _turnedOn;
};

#endif
