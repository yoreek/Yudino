#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <DebugUtil.h>
#include <Meter/EnergyMeter.h>

#define POWER 100 // Watts

EnergyMeter meter(100);

void setup() {
    DEBUG_SERIAL_SETUP(57600);
    DEBUG("setup");
}

void loop() {
    meter.update(true);
    DEBUG("running time: %ul secs, power consumption: %f kWh",
        meter.getRunningTime(), meter.getPowerConsumption());
    delay(1000);
}
