#include "HTU21DF.h"

bool HTU21DFTempSensor::getRealValue(float *value) {
    uint16_t raw, status;

    _drv->sendRequest(HTU21DF_TEMP_MEASURE_NOHOLD, HTU21DF_TEMP_MEASURE_TIME);

    if ((status = _drv->readMeasure(&raw)) != HTU21DF_OK)
        return false;

    *value = HTU21DF_TEMP_CONVERSION(raw);

    return true;
}

bool HTU21DFHumdSensor::getRealValue(float *value) {
    uint16_t raw;

    _drv->sendRequest(HTU21DF_HUMD_MEASURE_NOHOLD, HTU21DF_HUMD_MEASURE_TIME);

    if (_drv->readMeasure(&raw) != HTU21DF_OK)
        return false;

    *value = HTU21DF_HUMD_CONVERSION(raw);

    return true;
}

bool HTU21DF::update(bool forceUpdate) {
    return _tempSensor.update(forceUpdate) && _humdSensor.update(forceUpdate);
};

float HTU21DF::getHumidityComp(void) {
    return getHumidity() + (25.0 - getTemperature()) * -0.15;
}

float HTU21DF::getDewPoint(void) {
    float h, t, paritalPressure, dewPoint;

    h = getHumidity();
    t = getTemperature();

    paritalPressure = HTU21DF_DEW_POINT_A - HTU21DF_DEW_POINT_B / (t + HTU21DF_DEW_POINT_C);
    paritalPressure = pow(10, paritalPressure);

    dewPoint = (h * paritalPressure / 100.0);         //do the innermost brackets
    dewPoint = log10(dewPoint) - HTU21DF_DEW_POINT_A; //we have calculated the denominator of the equation
    dewPoint = HTU21DF_DEW_POINT_B / dewPoint;        //the whole fraction of the equation has been calculated
    dewPoint = -(dewPoint + HTU21DF_DEW_POINT_C);     //The whole dew point calculation has been performed

    return dewPoint;
}

int HTU21DF::readUserRegister() {
    uint8_t userRegister;

    sendRequest(HTU21DF_READ_USER_REG);

    if (readResponse(&userRegister, 1) != HTU21DF_OK)
        return -1;

    return userRegister;
}

void HTU21DF::writeUserRegister(uint8_t data) {
    sendRequest(HTU21DF_WRITE_USER_REG, 0, &data, 1);
}

void HTU21DF::setResolution(uint8_t resolution) {
    int userRegister = readUserRegister();
    if (userRegister != -1) {
        userRegister &= (~HTU21DF_RESOLUTION);
        writeUserRegister(userRegister | (resolution & HTU21DF_RESOLUTION));
    }
}

int HTU21DF::getResolution(void) {
    int userRegister = readUserRegister();
    if (userRegister != -1) {
        userRegister &= HTU21DF_RESOLUTION;
    }
    return userRegister;
}

void HTU21DF::sendRequest(uint8_t cmd, uint16_t wait, uint8_t *buf, int size) {
    Wire.beginTransmission(HTU21DF_I2C_ADDRESS);

    Wire.write(cmd);
    while (size--)
        Wire.write(*buf++);

    Wire.endTransmission();

    if (wait != 0)
        delay(wait);
}

uint16_t HTU21DF::readResponse(uint8_t *buf, int size) {
    Wire.requestFrom(HTU21DF_I2C_ADDRESS, size);

    uint16_t maxTime = millis() + HTU21DF_I2C_READ_TIME;
    while (Wire.available() < size) {
        if (millis() >= maxTime)
            return HTU21DF_I2C_TIMEOUT;
        delay(1);
    }

    while (size--)
        *buf++ = Wire.read();

    return HTU21DF_OK;
}

uint16_t HTU21DF::readMeasure(uint16_t *data) {
    uint16_t status;
    uint8_t  buf[3];

    if ((status = readResponse(buf, 3)) != HTU21DF_OK)
        return status;

    *data   = buf[0];
    *data <<= 8;
    *data  |= buf[1];

    if (checkCRC(*data, buf[2]) != 0)
        return HTU21DF_BAD_CRC;

    *data &= 0xFFFC; // zero the status bits

    return HTU21DF_OK;
}

uint8_t HTU21DF::checkCRC(uint16_t data, uint8_t crc) {
    uint32_t remainder = (uint32_t) data << 8;
    remainder |= crc;

    uint32_t divsor = (uint32_t) HTU21DF_CRC_POLY;

    for (int i = 0; i < 16; i++) {
        if (remainder & (uint32_t) 1 << (23 - i))
            remainder ^= divsor;

        divsor >>= 1;
    }

    return (uint8_t) remainder;
}
