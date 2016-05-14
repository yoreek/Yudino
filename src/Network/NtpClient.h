#pragma once
#ifndef _NTP_CLIENT_H_
#define _NTP_CLIENT_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Time.h>

#define NTP_CLIENT_SERVER_PORT   123
#define NTP_CLIENT_PACKET_SIZE   48
#define NTP_CLIENT_POOL_INTERVAL 150
#define NTP_CLIENT_MAX_POLL      10

class NtpClient {
    public:
        static time_t getTime(EthernetUDP &udp, IPAddress &server, uint16_t port, uint8_t tz);
        static time_t getTime(EthernetUDP &udp, IPAddress &server, uint8_t tz) {
            return getTime(udp, server, NTP_CLIENT_SERVER_PORT, tz);
        };

    private:
        static bool _sendRequest(EthernetUDP &udp, IPAddress &server, uint16_t port, uint8_t *buf);
};

#endif
