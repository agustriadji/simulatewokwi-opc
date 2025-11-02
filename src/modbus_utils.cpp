#include "modbus_utils.h"

uint16_t crc16(const uint8_t *data, uint8_t len)
{
    uint16_t crc = 0xFFFF;
    for (uint8_t i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            crc = (crc >> 1) ^ (crc & 1 ? 0xA001 : 0);
        }
    }
    return crc;
}

void sendModbusFrame8Sensors(WiFiClient &client)
{
    uint8_t frame[3 + 16 + 2]; // header + 8 sensor data + CRC
    frame[0] = 0x01;           // Device ID
    frame[1] = 0x03;           // Function Code
    frame[2] = 0x10;           // Byte count (16 bytes)

    for (int i = 0; i < 8; i++)
    {
        uint16_t pressureRaw = 220 + random(-20, 20); // 2.00–2.40 bar
        frame[3 + i * 2] = pressureRaw >> 8;
        frame[4 + i * 2] = pressureRaw & 0xFF;
    }

    uint16_t crc = crc16(frame, 19);
    frame[19] = crc & 0xFF;
    frame[20] = crc >> 8;

    client.write(frame, 21);
    Serial.print("Sent Modbus frame: ");
    for (int i = 0; i < 21; i++)
        Serial.printf("%02X ", frame[i]);
    Serial.println();
}