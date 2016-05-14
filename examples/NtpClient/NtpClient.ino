#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <DebugUtil.h>
#include <Yudino.h>

#define ETHERNET_SHIELD_SDCARD_PIN 4
#define ETHERNET_SHIELD_W5100_PIN  10


uint8_t MAC_ADDRESSS[] = { 0x70, 0x5A, 0xB6, 0x01, 0x02, 0x03 };
IPAddress NTP_SERVER(132, 163, 4, 101);

#define NTP_LOCAL_PORT 8887
#define NTP_TIMEZONE   3

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

    DEBUG("Configure ethernet");
    if ( Ethernet.begin(MAC_ADDRESSS) == 0 ) {
        DEBUG("Failed to configure Ethernet using DHCP");
        return;
    }

    DEBUG("Ethernet configured successfully");
    Serial.print("IP: "); Serial.println(Ethernet.localIP());


    EthernetUDP udp;
    if (!udp.begin(NTP_LOCAL_PORT)) {
        DEBUG("udp.begin() failed");
        return;
    }

    DEBUG("Get time");
    time_t time = NtpClient::getTime(udp, NTP_SERVER, NTP_TIMEZONE);
    if (time == 0) {
        DEBUG("Failed to get time");
        udp.stop();
        return;
    }

    setTime(time);
    DEBUG("Current time: %F %T");
}

void loop() {
    while (true)
        ;
}
