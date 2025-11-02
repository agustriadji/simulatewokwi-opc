#include "sensor_utils.h"
#include <Wire.h>

#ifdef USE_DUMMY_SENSOR

Adafruit_BMP085 bmp180;
Adafruit_BME280 bme280;
bool bmp180Ready = true;
bool bme280Ready = true;

bool initBMP180() { return true; }
float readBMP180Temperature() { return 25.0 + random(-100, 100) / 100.0; }
float readBMP180Pressure() { return 1013.25 + random(-500, 500) / 10.0; }

bool initBME280() { return true; }
float readBME280Temperature() { return 26.0 + random(-100, 100) / 100.0; }
float readBME280Humidity() { return 60.0 + random(-200, 200) / 100.0; }
float readBME280Pressure() { return 1010.0 + random(-300, 300) / 10.0; }

#else

Adafruit_BMP085 bmp180;
Adafruit_BME280 bme280;
bool bmp180Ready = false;
bool bme280Ready = false;

bool initBMP180()
{
    Wire.begin();
    bmp180Ready = bmp180.begin();
    return bmp180Ready;
}

float readBMP180Temperature() { return bmp180.readTemperature(); }
float readBMP180Pressure() { return bmp180.readPressure() / 100.0; }

bool initBME280()
{
    Wire.begin();
    bme280Ready = bme280.begin(0x76);
    return bme280Ready;
}

float readBME280Temperature() { return bme280.readTemperature(); }
float readBME280Humidity() { return bme280.readHumidity(); }
float readBME280Pressure() { return bme280.readPressure(); }

#endif