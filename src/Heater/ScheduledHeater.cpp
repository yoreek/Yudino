#if defined(WITH_DEBUG) && ! defined(WITH_HEATER_DEBUG)
#  undef WITH_DEBUG
#endif
#include <DebugUtil.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Time.h>
#include "ScheduledHeater.h"

void ScheduledHeater::maintain() {
    long int wday, m;
    time_t   t;

    DEBUG("mode:%d", _mode);

    switch (_mode) {
        case OFF:
            DEBUG("off");
            setRegulate(false);
            turnOff();
            break;

        case SCHEDULE:
            DEBUG("schedule");
            t = now();
            wday = weekday(t) - 2;
            if (wday < 0) wday = 6; // mon = 0, sun = 6
            m = hour(t) * 60 + minute(t);
            DEBUG("wday:%d hour:%d minute:%d", wday, hour(t), m);
            for (int z = 0; z < SCHEDULE_HEATER_MAX_ZONES; z++) {
                DEBUG("start:%d end:%d", schedule[wday][z].start, schedule[wday][z].end);
                if (m >= schedule[wday][z].start && m < schedule[wday][z].end) {
                    setTargetTemperature(schedule[wday][z].setpoint);
                    DEBUG("found:%f", schedule[wday][z].setpoint);
                    break;
                }
            }
            setRegulate(true);
            break;

        case MANUAL:
            DEBUG("manual");
            setRegulate(true);
            break;

        case AWAY:
            DEBUG("away");
            setTargetTemperature(_awayTemperature);
            setRegulate(true);
            break;
        default:
            DEBUG("wrong");

    }

    RegulatedHeater::maintain();
}
