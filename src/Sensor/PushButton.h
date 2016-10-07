/*
 * PushButton.h - Arduino PushButton library
 * Copyright (C) 2016 Yuriy Ustushenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the version 3 GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once
#ifndef _PUSH_BUTTON_H_
#define _PUSH_BUTTON_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include <Core/Pin.h>
#include <StateMachine.h>

#ifndef PB_PULLUP
#define PB_PULLUP           true
#endif
#ifndef PB_ACTIVE_LEVEL
#define PB_ACTIVE_LEVEL     LOW
#endif
#ifndef PB_DEBOUNCE_DELAY
#define PB_DEBOUNCE_DELAY   50   // ms
#endif
#ifndef PB_CLICK_DELAY
#define PB_CLICK_DELAY      250  // ms
#endif
#ifndef PB_LONG_PRESS_DELAY
#define PB_LONG_PRESS_DELAY 1000 // ms
#endif

class PushButton;

typedef void (*PushButtonCallback)(PushButton *pb, void *data);

typedef struct PushButtonHandler_ PushButtonHandler;
struct PushButtonHandler_ {
    PushButtonCallback  callback;
    void               *data;
    PushButtonHandler  *next;
};

class PushButton : public StateMachine {
    public:
        PushButton(
            uint8_t  pin,
            bool     pullUp         = PB_PULLUP,
            uint8_t  activeLevel    = PB_ACTIVE_LEVEL,
            uint32_t debounceDelay  = PB_DEBOUNCE_DELAY,
            uint32_t clickDelay     = PB_CLICK_DELAY,
            uint32_t longPressDelay = PB_LONG_PRESS_DELAY) :
            StateMachine((PState) &PushButton::START),
            _pin(pin, pullUp),
            _activeLevel(activeLevel),
            _debounceDelay(debounceDelay),
            _clickDelay(clickDelay),
            _longPressDelay(longPressDelay),
            _pressed(false),
            _triggered(0),
            _onClick(NULL),
            _onDoubleClick(NULL),
            _onLongPress(NULL)
        {};
        inline void onClick(PushButtonCallback callback, void *data = NULL) {
            _setCallback(&_onClick, callback, data);
        };
        inline void onDoubleClick(PushButtonCallback callback, void *data = NULL) {
            _setCallback(&_onDoubleClick, callback, data);
        };
        inline void onLongPress(PushButtonCallback callback, void *data = NULL) {
            _setCallback(&_onLongPress, callback, data);
        };
        State START();
        State DEBOUNCE();
        State PRESS();
        State RELEASE();
        State DOUBLE_CLICK();
        State WAIT_FOR_RELEASE();

    protected:
        InputPin           _pin;
        uint8_t            _activeLevel;
        uint32_t           _debounceDelay;
        uint32_t           _clickDelay;
        uint32_t           _longPressDelay;
        bool               _pressed;
        uint32_t           _triggered;
        PushButtonHandler *_onClick;
        PushButtonHandler *_onDoubleClick;
        PushButtonHandler *_onLongPress;

        void _setCallback(PushButtonHandler **handler, PushButtonCallback callback, void *data);
        void _processCallback(PushButtonHandler *handler);
};

#endif
