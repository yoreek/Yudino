#pragma once
#ifndef __PIN_H__
#define __PIN_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include <util/atomic.h>

class Pin {
    public:
        Pin(uint8_t pin) :
            _pin(pin),
            _bitMask(digitalPinToBitMask(pin))
        {
        };
        inline uint8_t pin() {
            return _pin;
        };
        inline uint8_t bitMask() {
            return _bitMask;
        };

    protected:
        uint8_t _pin;
        uint8_t _bitMask;
};

class InputPin: public Pin {
    public:
        InputPin(uint8_t pin, bool pullup = false) :
            Pin(pin),
            _inputRegister(portInputRegister(digitalPinToPort(pin)))
        {
            pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
        };
        uint8_t read() {
            return *_inputRegister & _bitMask ? HIGH : LOW;
        };

    protected:
        volatile uint8_t *_inputRegister;
};

class OutputPin: public Pin {
    public:
        OutputPin(uint8_t pin, uint8_t initialValue = LOW) :
            Pin(pin),
            _outputRegister(portOutputRegister(digitalPinToPort(pin)))
        {
            write(initialValue);
            pinMode(pin, OUTPUT);
        };
        void write(uint8_t value) {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                if (value == LOW) {
                    *_outputRegister &= ~_bitMask;
                }
                else {
                    *_outputRegister |= _bitMask;
                }
            }
        };

    protected:
        volatile uint8_t *_outputRegister;
};

#endif // __PIN_H__
