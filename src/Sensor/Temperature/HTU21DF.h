#pragma once
#ifndef _HTU21DF_H_
#define _HTU21DF_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <inttypes.h>
#include <Wire.h>
#include "CachedMeasure.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"

// Address
#define HTU21DF_I2C_ADDRESS         0x40

// Commands
#define HTU21DF_TEMP_MEASURE_HOLD   0xE3
#define HTU21DF_HUMD_MEASURE_HOLD   0xE5
#define HTU21DF_TEMP_MEASURE_NOHOLD 0xF3
#define HTU21DF_HUMD_MEASURE_NOHOLD 0xF5
#define HTU21DF_WRITE_USER_REG      0xE6
#define HTU21DF_READ_USER_REG       0xE7
#define HTU21DF_SOFT_RESET          0xFE

// User register
#define HTU21DF_RESOLUTION_RH12_T14 0b00000000
#define HTU21DF_RESOLUTION_RH8_T12  0b00000001
#define HTU21DF_RESOLUTION_RH10_T13 0b10000000
#define HTU21DF_RESOLUTION_RH11_T11 0b10000001
#define HTU21DF_RESOLUTION          0b10000001
#define HTU21DF_END_OF_BATTERY      0b01000000
#define HTU21DF_REGISTER_RESERVED   0b00111000
#define HTU21DF_ENABLE_HEATER       0b00000100
#define HTU21DF_DISABLE_OTP_RELOAD  0b00000010

// Timing
#define HTU21DF_MEASURE_SAMPLES     3
#define HTU21DF_EXPIRE_TIME         1000
#define HTU21DF_TEMP_MEASURE_TIME   (50 + 5)
#define HTU21DF_HUMD_MEASURE_TIME   (14 + 4)
#define HTU21DF_SOFT_RESET_TIME     (15 + 5)
#define HTU21DF_I2C_READ_TIME       100

// Status
#define HTU21DF_I2C_TIMEOUT         998
#define HTU21DF_BAD_CRC             999
#define HTU21DF_OK                  0

// Calculate
#define HTU21DF_CRC_POLY            0x988000
#define HTU21DF_TEMP_CONVERSION(x)  (((float) x) * 175.72 / 65536.0 - 46.85)
#define HTU21DF_HUMD_CONVERSION(x)  (((float) x) * 125.0  / 65536.0 -   6.0)
#define HTU21DF_DEW_POINT_A         8.1332
#define HTU21DF_DEW_POINT_B         1762.39
#define HTU21DF_DEW_POINT_C         235.66

class HTU21DF;

class HTU21DFTempSensor: public CachedMeasure {
    public:
        HTU21DFTempSensor(
            HTU21DF *drv,
            uint8_t  measureSamples = HTU21DF_MEASURE_SAMPLES,
            uint16_t expireTime     = HTU21DF_EXPIRE_TIME):
            CachedMeasure(measureSamples, expireTime),
            _drv(drv)
        {};

        bool getRealValue(float *value);

    private:
        HTU21DF *_drv;
};

class HTU21DFHumdSensor: public CachedMeasure {
    public:
        HTU21DFHumdSensor(
            HTU21DF *drv,
            uint8_t  measureSamples = HTU21DF_MEASURE_SAMPLES,
            uint16_t expireTime     = HTU21DF_EXPIRE_TIME):
            CachedMeasure(measureSamples, expireTime),
            _drv(drv)
        {};

        bool getRealValue(float *value);

    private:
        HTU21DF *_drv;
};

class HTU21DF: public TemperatureSensor, public HumiditySensor {
    public:
        HTU21DF(
            uint8_t  measureSamples = HTU21DF_MEASURE_SAMPLES,
            uint16_t expireTime     = HTU21DF_EXPIRE_TIME):
            _tempSensor(this, measureSamples, expireTime),
            _humdSensor(this, measureSamples, expireTime)
        {};

        void reset() {
            sendRequest(HTU21DF_SOFT_RESET, HTU21DF_SOFT_RESET_TIME);
        };
        void begin() {
            reset();
        };
        bool isAlive() {
            return readUserRegister() != -1;
        };
        bool update(bool forceUpdate = false);
        float getTemperature(void) {
            return _tempSensor.getValue();
        };
        float getHumidity(void) {
            return _humdSensor.getValue();
        };
        float getHumidityComp(void);
        float getDewPoint(void);
        int readUserRegister();
        void writeUserRegister(uint8_t data);
        void setResolution(uint8_t resolution);
        int getResolution(void);
        void sendRequest(uint8_t cmd, uint16_t wait = 0, uint8_t *buf = NULL, int size = 0);
        uint16_t readResponse(uint8_t *buf, int size);
        uint16_t readMeasure(uint16_t *data);
        uint8_t checkCRC(uint16_t data, uint8_t crc);

    private:
        HTU21DFTempSensor _tempSensor;
        HTU21DFHumdSensor _humdSensor;
};

#endif
