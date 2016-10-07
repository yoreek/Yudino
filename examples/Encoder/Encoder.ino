#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <DebugUtil.h>
#include <Yudino.h>

#define SERIAL_BAUDRATE  57600

#define ENC_PIN_A        2
#define ENC_PIN_B        3
#ifndef ENC_RESOLUTION
#define ENC_RESOLUTION   1     // resolution: 1, 2 or 4
#endif

RotaryEncoder enc(ENC_PIN_A, ENC_PIN_B);

void encUpdateA() { enc.updateA(); }
#if ENC_RESOLUTION == 4
void encUpdateB() { enc.updateB(); }
#endif

void setup() {
    DEBUG_SERIAL_SETUP(SERIAL_BAUDRATE);

#if ENC_RESOLUTION == 1
    attachInterrupt(digitalPinToInterrupt(ENC_PIN_A), encUpdateA, RISING);
#elif ENC_RESOLUTION == 2
    attachInterrupt(digitalPinToInterrupt(ENC_PIN_A), encUpdateA, CHANGE);
#elif ENC_RESOLUTION == 4
    attachInterrupt(digitalPinToInterrupt(ENC_PIN_A), encUpdateA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_PIN_B), encUpdateB, CHANGE);
#endif
}

void loop() {
    DEBUG_EVERY(100, "value: %d", enc.getValue());
}
