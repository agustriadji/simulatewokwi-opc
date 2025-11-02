#include <Arduino.h>
#include "sensor_utils.h"
#include "modbus_utils.h"
#include "network_utils.h"

#define USE_MODBUS_SIMULATION // aktifkan untuk kirim frame Modbus RTU

unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 5000;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting simulation...");

    connectWiFi();

#ifdef USE_DUMMY_SENSOR
    Serial.println("Using dummy sensor mode");
    bmp180Ready = true;
    bme280Ready = true;
#else
    bmp180Ready = initBMP180();
    Serial.println(bmp180Ready ? "BMP180 initialized" : "BMP180 not found");

    bme280Ready = initBME280();
    Serial.println(bme280Ready ? "BME280 initialized" : "BME280 not found");
#endif
}

void loop()
{
    unsigned long now = millis();
    if (now - lastSend >= SEND_INTERVAL)
    {
        lastSend = now;

        if (!ensureTCPConnected())
            return;

#ifdef USE_MODBUS_SIMULATION
        sendModbusFrame8Sensors(tcpClient);
#else
        float bmpTemp = bmp180Ready ? readBMP180Temperature() : NAN;
        float bmpPress = bmp180Ready ? readBMP180Pressure() : NAN;
        float bmeTemp = bme280Ready ? readBME280Temperature() : NAN;
        float bmeHum = bme280Ready ? readBME280Humidity() : NAN;
        float bmePress = bme280Ready ? readBME280Pressure() : NAN;

        Serial.printf("BMP180: T=%.2f °C, P=%.2f hPa\n", bmpTemp, bmpPress);
        Serial.printf("BME280: T=%.2f °C, H=%.2f %%, P=%.2f hPa\n", bmeTemp, bmeHum, bmePress);

        if (!isnan(bmpTemp) && !isnan(bmpPress))
        {
            sendJsonToServer(bmpTemp, bmpPress, bmeTemp, bmeHum, bmePress);
        }
        else
        {
            Serial.println("Sensor read failed");
        }
#endif
    }

    if (tcpClient && !tcpClient.connected())
    {
        tcpClient.stop();
        Serial.println("TCP disconnected");
    }

    delay(10);
}