#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <DebugUtil.h>
#include <StringUtil.h>
#include <Yudino.h>

#define ADC_REF            5.0
#define BAT_SENSOR_PIN     A0
#define BAT_DIVIDER_RATIO  (292.0 / (921.0 + 292.0))
#define BAT_MIN_VOLTAGE    2.5
#define BAT_MAX_VOLTAGE    4.2

Battery bat(new VoltageSensor(BAT_SENSOR_PIN, BAT_DIVIDER_RATIO, ADC_REF),
            BAT_MIN_VOLTAGE, BAT_MAX_VOLTAGE);

void setup() {
    DEBUG_SERIAL_SETUP(57600);
    DEBUG("setup");

    bat.begin();
}

void loop() {
    if (bat.update()) {
        DEBUG("Battery Voltage: %.6f V, level: %.1f %%", bat.voltage(), bat.level());
    }

    delay(1000);
}
