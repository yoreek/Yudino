#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <DebugUtil.h>
#include <Yudino.h>

#define RELAY_PIN          7
#define THERMISTOR_PIN     0
#define THERMISTOR_NOMINAL 15000
#define THERMISTOR_SERIAL  10000

Relay            relay(RELAY_PIN);
Heater           heater1("Room heater", &relay);
Thermistor       thermistor(THERMISTOR_PIN, THERMISTOR_NOMINAL, THERMISTOR_SERIAL);
RegulatedHeater  heater2("Room heater", &relay, &thermistor);
ScheduledHeater  heater3("Room heater", &relay, &thermistor);
UnderfloorHeater heater4("Room heater", &relay, &thermistor);

void setup() {
    DEBUG_SERIAL_SETUP(57600);
    DEBUG("setup");

    DEBUG("turn On");
    heater1.turnOn();
    DEBUG("heater status: %d", heater1.isTurnedOn());

    DEBUG("turn Off");
    heater1.turnOff();
    DEBUG("heater status: %d", heater1.isTurnedOn());
}

void loop() {
    while (true)
        ;
}
