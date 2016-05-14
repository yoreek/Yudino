#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <DebugUtil.h>
#include <Yudino.h>

#define MAINTAIN_INTERVAL 60 // seconds

MaintainedObject obj1;
MaintainedObject obj2;
MaintainedCollection coll(MAINTAIN_INTERVAL);

void setup() {
    DEBUG_SERIAL_SETUP(57600);
    DEBUG("setup");

    coll.add(&obj1);
    coll.add(&obj2);
}

void loop() {
    while (true)
        ;
}
