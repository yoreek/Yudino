#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Thermistor.h"
#include <inttypes.h>

bool Thermistor::getRealValue(float *value) {
    float r, k;

    r = _seriesResistor / (1023.0 / (analogRead(_sensorPin) + _adcCorrection) - 1);
    k = r / _termistorNominal;
    *value = 1 / (
          0.003354016
        + 0.0002569355   * log(k)
        + 0.000002625311 * pow(log(k), 2)
        + 0.000000675278 * pow(log(k), 3)
    ) - 273.15;

    return true;
}
