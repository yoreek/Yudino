#pragma once
#ifndef _UNDERFLOOR_HEATER_H_
#define _UNDERFLOOR_HEATER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include "ScheduledHeater.h"
#include <Meter/EnergyMeter.h>
#include <Logger/DataLogger.h>
#include <Sensor/Temperature/TemperatureSensor.h>

class UnderfloorHeater: public ScheduledHeater {
    public:
        UnderfloorHeater(
            const char              *name,
            Relay                   *relay,
            TemperatureSensorCached *temperatureSensor,
            EnergyMeter             *energyMeter = NULL,
            DataLogger              *dataLogger  = NULL,
            uint32_t                 logInterval = 0
        ) : ScheduledHeater(
                name,
                relay,
                temperatureSensor
            ),
            _energyMeter(energyMeter),
            _dataLogger(dataLogger),
            _logInterval(logInterval),
            _nextLogging(0),
            _prevRunningTime(0)
        {};

        void maintain();
        void turnOn();
        void turnOff();
        EnergyMeter *getEnergyMeter();

    protected:
        EnergyMeter *_energyMeter;
        DataLogger  *_dataLogger;
        uint32_t     _logInterval;
        uint32_t     _nextLogging;
        uint32_t     _prevRunningTime;
};

#endif
