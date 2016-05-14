#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#ifndef WITH_NTP_DEBUG
#undef WITH_DEBUG
#endif
#include <DebugUtil.h>
#include "NtpClient.h"

time_t NtpClient::getTime(EthernetUDP &udp, IPAddress &server, uint16_t port, uint8_t tz) {
    uint8_t buf[NTP_CLIENT_PACKET_SIZE];

    udp.flush();

    DEBUG("Send NTP request");
    if (!_sendRequest(udp, server, port, buf)) {
        DEBUG("Failed to send NTP request");
        return 0;
    }

    int size;
    for (uint8_t i = 0; i < NTP_CLIENT_MAX_POLL; i++) {
        size = udp.parsePacket();
        DEBUG("Got packet size: %d", size);
        if (size >= NTP_CLIENT_PACKET_SIZE) {
            udp.read(buf, NTP_CLIENT_PACKET_SIZE);

            uint32_t secsSince1900;
            // convert four bytes starting at location 40 to a long integer
            secsSince1900 =  (uint32_t) buf[40] << 24;
            secsSince1900 |= (uint32_t) buf[41] << 16;
            secsSince1900 |= (uint32_t) buf[42] << 8;
            secsSince1900 |= (uint32_t) buf[43];
            secsSince1900 += - 2208988800UL + tz * SECS_PER_HOUR;

            DEBUG("Got time: %ul", secsSince1900);
            return secsSince1900;
        }
        delay(NTP_CLIENT_POOL_INTERVAL);
    }

    DEBUG("Failed to get time");

    return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
bool NtpClient::_sendRequest(EthernetUDP &udp, IPAddress &server, uint16_t port, uint8_t *buf) {
    memset(buf, 0, NTP_CLIENT_PACKET_SIZE);

    // Initialize values needed to form NTP request
    buf[0]  = 0b11100011;   // LI, Version, Mode
    buf[1]  = 0;            // Stratum, or type of clock
    buf[2]  = 6;            // Polling Interval
    buf[3]  = 0xEC;         // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    buf[12] = 49;
    buf[13] = 0x4E;
    buf[14] = 49;
    buf[15] = 52;

    if (!udp.beginPacket(server, port))
        return false;

    if (udp.write(buf, NTP_CLIENT_PACKET_SIZE) != NTP_CLIENT_PACKET_SIZE)
        return false;

    if (!udp.endPacket())
        return false;

    return true;
}
