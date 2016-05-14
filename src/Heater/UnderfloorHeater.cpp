#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include "UnderfloorHeater.h"

EnergyMeter *UnderfloorHeater::getEnergyMeter() {
    return _energyMeter;
}

void UnderfloorHeater::maintain() {
    float temp;

    ScheduledHeater::maintain();

    if (_energyMeter != NULL) {
        _energyMeter->update(isTurnedOn());
    }

    if (_dataLogger != NULL && _logInterval != 0
        && _nextLogging <= millis()) {

        double consumption, consumptionDelta;
        if (_energyMeter != NULL) {
            // kWh
            consumption = _energyMeter->getPowerConsumption();
            if (_prevRunningTime == 0) {
                consumptionDelta = 0.0;
            }
            else {
                consumptionDelta = _energyMeter->getPower() * (_energyMeter->getRunningTime() - _prevRunningTime) / 3600000.0;
            }
            _prevRunningTime = _energyMeter->getRunningTime();
        }
        else {
            consumption = consumptionDelta = 0.0;
        }

        if (_temperatureSensor->update()) {
            temp = _temperatureSensor->getTemperature();
        }
        else {
            temp = 999;
        }

        _dataLogger->log((char *) "%F %T,%.1f,%f,%f", (double) temp, consumption, consumptionDelta);

        _nextLogging = millis() + _logInterval * 1000;
    }
}

void UnderfloorHeater::turnOn() {
    if (isTurnedOn()) return;
    _energyMeter->update(false);
    ScheduledHeater::turnOn();
}

void UnderfloorHeater::turnOff() {
    if (!isTurnedOn()) return;
    _energyMeter->update(true);
    ScheduledHeater::turnOff();
}
