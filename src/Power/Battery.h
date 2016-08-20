#pragma once
#ifndef _BATTERY_H_
#define _BATTERY_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <Sensor/Power/VoltageSensor.h>

class Battery {
    public:
        Battery(VoltageSensor *sensor, float minVoltage, float maxVoltage) :
            _sensor(sensor),
            _minVoltage(minVoltage),
            _maxVoltage(maxVoltage)
        {
        };
        void begin(void);
        inline float voltage(void) {
            return _sensor->voltage();
        };
        inline bool update(bool forceUpdate = false) {
            return _sensor->update(forceUpdate);
        };
        float level(void);

    private:
        VoltageSensor *_sensor;
        float          _minVoltage;
        float          _maxVoltage;
};

#endif // _BATTERY_H_
