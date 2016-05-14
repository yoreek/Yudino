#pragma once
#ifndef _ENERGY_METER_H_
#define _ENERGY_METER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class EnergyMeter {
    public:
        EnergyMeter(uint16_t power) :
            _power(power),
            _runningTime(0),
            _lastCalculate(0)
        {
        };
        // Set running time in seconds
        inline void setRunningTime(uint32_t t) {
            _runningTime = t;
        };
        // Get running time in seconds
        inline uint32_t getRunningTime() {
            return _runningTime;
        };
        // Set power in Watts
        inline void setPower(uint16_t power) {
            _power = power;
        };
        // Get power in Watts
        inline uint16_t getPower() {
            return _power;
        };
        // Update running time
        void update(bool isTurnedOn);
        // Return the power consumption in kWh
        float getPowerConsumption();

    private:
        uint16_t _power;
        uint32_t _runningTime;
        uint32_t _lastCalculate;
};

#endif
