#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#ifndef WITH_DEBUG
#  define WITH_DEBUG
#endif
#include <DebugUtil.h>
#include <Yudino.h>

#define SERIAL_BAUDRATE  57600
#define BUTTON_PIN       4
#define LED_PIN          13

void click(PushButton *, void *) {
    DEBUG("Click");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
}

void doubleClick(PushButton *, void *) {
    DEBUG("Double click");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
}

void longPress(PushButton *, void *) {
    DEBUG("Long press");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
}

PushButton btn(BUTTON_PIN);

void setup() {
    DEBUG_SERIAL_SETUP(SERIAL_BAUDRATE);


    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    btn.onClick(click);
    btn.onDoubleClick(doubleClick);
    btn.onLongPress(longPress);
}

void loop() {
    btn.loop();
}

