#pragma once
#ifndef _HEATER_H_
#define _HEATER_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include <Relay/Relay.h>

class Heater {
    public:
        Heater(
            const char *name,
            Relay      *relay
        ) :
            _name(name),
            _relay(relay)
        {};
        virtual const char *name();
        virtual void turnOn();
        virtual void turnOff();
        virtual bool isTurnedOn();

    protected:
        const char *_name;
        Relay      *_relay;
};

#endif
