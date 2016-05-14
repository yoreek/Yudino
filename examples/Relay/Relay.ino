#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <DebugUtil.h>
#include <Relay/Relay.h>

#define RELAY_PIN      7
#define RELAY_INVERTED false

Relay relay(RELAY_PIN, RELAY_INVERTED);

void setup() {
    DEBUG_SERIAL_SETUP(57600);
    DEBUG("setup");

    DEBUG("turn On");
    relay.turnOn();
    DEBUG("relay status: %d", relay.isTurnedOn());

    DEBUG("turn Off");
    relay.turnOff();
    DEBUG("relay status: %d", relay.isTurnedOn());
}

void loop() {
    while (true)
        ;
}
