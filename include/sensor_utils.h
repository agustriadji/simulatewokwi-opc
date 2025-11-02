#ifndef SENSOR_UTILS_H
#define SENSOR_UTILS_H

#include <Adafruit_BMP085.h>
#include <Adafruit_BME280.h>

// BMP180
extern Adafruit_BMP085 bmp180;
extern bool bmp180Ready;

bool initBMP180();
float readBMP180Temperature();
float readBMP180Pressure();

// BME280
extern Adafruit_BME280 bme280;
extern bool bme280Ready;

bool initBME280();
float readBME280Temperature();
float readBME280Humidity();
float readBME280Pressure();

#endif