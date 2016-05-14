#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <SPI.h>
#include <SdFat.h>
#include <DebugUtil.h>
#include <Yudino.h>

#define ETHERNET_SHIELD_SDCARD_PIN 4
#define ETHERNET_SHIELD_W5100_PIN  10

// "/test-YYYY-MM-DD.log"
#define LOG_FILE "/test-%F.log"

SdFat sd;
DataLogger logger(&sd, LOG_FILE);

void setup() {
    DEBUG_SERIAL_SETUP(57600);
    DEBUG("setup");

    // Init Ethernet shield
    // deselect SDcard
    pinMode(ETHERNET_SHIELD_SDCARD_PIN, OUTPUT);
    digitalWrite(ETHERNET_SHIELD_SDCARD_PIN, HIGH);

    // deselect W5100
    // On both boards, pin 10 is used as SS
    pinMode(ETHERNET_SHIELD_W5100_PIN, OUTPUT);
    digitalWrite(ETHERNET_SHIELD_W5100_PIN, HIGH);

    // On the Mega, the hardware SS pin, 53, is not used to select the W5100,
    // but it must be kept as an output or the SPI interface won't work.
    //pinMode(SS, OUTPUT);
    pinMode(53, OUTPUT);

    // Init SD card
    DEBUG("init SDcard");
    if (!sd.begin(ETHERNET_SHIELD_SDCARD_PIN, SPI_HALF_SPEED)) {
        DEBUG("Failed to init SDcard!");
        while (true)
            ;
    }
}

void loop() {
    File file;
    char realFileName[64];

    for (int i = 0; i < 10; i++) {
        DEBUG("log");
        logger.log(F("%F %T: %d"), 1);
        delay(1000);
    }

    logger.getRealFileName(realFileName);
    DEBUG("Dump file: %s", realFileName);
    if (file.open(realFileName, O_READ)) {
        int c;
        while ((c = file.read()) != -1) {
            Serial.print((char) c);
        }
        file.close();
    }
    else {
        DEBUG("Cannot open file: %s", realFileName);
    }

    while (true)
        ;
}
