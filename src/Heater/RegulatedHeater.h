#pragma once
#ifndef _REGULATED_HEATER_H_
#define _REGULATED_HEATER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <Heater/Heater.h>
#include <Sensor/Temperature/TemperatureSensor.h>
#include <Maintain/Maintain.h>

#define _DEF_TEMP       24.0
#define _DEF_HYSTERESIS 0.2

class RegulatedHeater: public Heater, public MaintainedObject {
    public:
        RegulatedHeater(
            const char              *name,
            Relay                   *relay,
            TemperatureSensorCached *temperatureSensor
        ) :
            Heater(name, relay),
            MaintainedObject(),
            _temperatureSensor(temperatureSensor),
            _targetTemperature(_DEF_TEMP),
            _hysteresis(_DEF_HYSTERESIS),
            _regulated(true)
        {};

        void maintain();
        void setTargetTemperature(float targetTemperature);
        float getTargetTemperature();
        void setHysteresis(float t);
        float getHysteresis();
        void setRegulate(bool regulate);
        bool isRegulated();
        TemperatureSensor *getTemperatureSensor();

    protected:
        TemperatureSensorCached *_temperatureSensor;
        float                    _targetTemperature;
        float                    _hysteresis;
        bool                     _regulated;

        void _maintainTemperature();
};

#undef _DEF_TEMP
#undef _DEF_HYSTERESIS

#endif
