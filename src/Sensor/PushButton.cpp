/*
 * PushButton.cpp - Arduino PushButton library
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
#ifndef WITH_PUSH_BUTTON_DEBUG
#  undef WITH_DEBUG
#endif
#include <DebugUtil.h>
#include "PushButton.h"
#undef SM_CLASS
#define SM_CLASS PushButton

#define _IS_PRESSED() (_pin.read() == _activeLevel)

State PushButton::START() {
    if (_IS_PRESSED())
        SM_CALL2(DEBOUNCE, PRESS, START);
}

State PushButton::DEBOUNCE() {
    if (_IS_PRESSED() == _pressed) {
        SM_RETURN_FAIL();
    }

    if (isTimeout(_debounceDelay)) {
        _triggered = millis();
        _pressed   = ! _pressed;
        SM_RETURN_SUCCESS();
    }
}

State PushButton::PRESS() {
    if (!_IS_PRESSED())
        SM_CALL2(DEBOUNCE, RELEASE, PRESS);

    if ((millis() -_triggered) >= _longPressDelay) {
        _processCallback(_onLongPress);

        SM_GOTO(WAIT_FOR_RELEASE);
    }
}

State PushButton::RELEASE() {
    if (_IS_PRESSED())
        SM_CALL2(DEBOUNCE, DOUBLE_CLICK, RELEASE);

    if ((millis() -_triggered) >= _clickDelay) {
        _processCallback(_onClick);

        SM_GOTO(START);
    }
}

State PushButton::DOUBLE_CLICK() {
    _processCallback(_onDoubleClick);

    SM_GOTO(WAIT_FOR_RELEASE);
}

State PushButton::WAIT_FOR_RELEASE() {
    if (!_IS_PRESSED())
        SM_CALL2(DEBOUNCE, START, WAIT_FOR_RELEASE);
}

void PushButton::_setCallback(PushButtonHandler **handler, PushButtonCallback callback, void *data) {
    PushButtonHandler *h = (PushButtonHandler *) calloc(1, sizeof(PushButtonHandler));
    if (h == NULL) {
        while (true)
            ;
    }

    h->callback = callback;
    h->data     = data;

    h->next     = *handler;
    *handler    = h;
}

void PushButton::_processCallback(PushButtonHandler *handler) {
    for (; handler != NULL; handler = handler->next) {
        handler->callback(this, handler->data);
    }
}
