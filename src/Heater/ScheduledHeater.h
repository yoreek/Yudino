#pragma once
#ifndef _SCHEDULED_HEATER_H_
#define _SCHEDULED_HEATER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include "RegulatedHeater.h"

#define _DEF_AWAY_TEMP             20.0
#define SCHEDULE_HEATER_MAX_ZONES 5
#define SCHEDULE_HEATER_MAX_DAYS  7

struct SchedulePeriod {
    int start;
    int end;
    float setpoint;
};

const struct SchedulePeriod _DEF_SCHEDULE_PER_DAY[SCHEDULE_HEATER_MAX_ZONES] = {
    {  0 * 60,  6 * 60, 20.0 },
    {  6 * 60,  9 * 60, 25.0 },
    {  9 * 60, 17 * 60, 23.0 },
    { 17 * 60, 22 * 60, 25.0 },
    { 22 * 60, 24 * 60, 20.0 }
};

class ScheduledHeater: public RegulatedHeater {
    public:
        enum Mode {
            OFF      = 0,
            SCHEDULE = 1,
            MANUAL   = 2,
            AWAY     = 3
        };

        SchedulePeriod schedule[SCHEDULE_HEATER_MAX_DAYS][SCHEDULE_HEATER_MAX_ZONES];

        ScheduledHeater(
            const char              *name,
            Relay                   *relay,
            TemperatureSensorCached *temperatureSensor
        ) : RegulatedHeater(
                name,
                relay,
                temperatureSensor
            ),
            _mode(OFF),
            _awayTemperature(_DEF_AWAY_TEMP)
        {
            for (int i = 0; i < 7; i++) {
                memcpy(&schedule[i], &_DEF_SCHEDULE_PER_DAY, sizeof(_DEF_SCHEDULE_PER_DAY));
            }
        };

        void setMode(ScheduledHeater::Mode mode) {
            _mode = mode;
        };
        ScheduledHeater::Mode getMode(void) {
            return _mode;
        };
        void maintain();
        float awayTemperature(void) {
            return _awayTemperature;
        };

    private:
        Mode  _mode;
        float _awayTemperature;
};

#undef _DEF_AWAY_TEMP

#endif
