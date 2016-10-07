#include "RotaryEncoder.h"

/*
 *  On update A:
 *  A | B | XOR | CW/CCW
 * ----------------------
 *  0 | 0 |  0  |  CW
 *  0 | 1 |  1  |  CCW
 *  1 | 0 |  1  |  CCW
 *  1 | 1 |  0  |  CW
 *
 *  On update B:
 *  B | A | XOR | CW/CCW
 * ----------------------
 *  0 | 0 |  0  |  CCW
 *  0 | 1 |  1  |  CW
 *  1 | 0 |  1  |  CW
 *  1 | 1 |  0  |  CCW
 */

#define _UPDATE_A   1
#define _UPDATE_B   0
#define _IS_CW(ab)  (_pinA.read() ^ _pinB.read() ^ ab ^ _reverse)

inline void RotaryEncoder::_updateAB(uint8_t invert) {
    if (_IS_CW(invert)) {
        if (_value < _max)
            _value++;
    }
    else {
        if (_value > _min)
            _value--;
    }
}

void RotaryEncoder::updateA() {
    _updateAB(_UPDATE_A);
}

void RotaryEncoder::updateB() {
    _updateAB(_UPDATE_B);
}
