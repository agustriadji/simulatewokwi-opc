#ifndef MODBUS_UTILS_H
#define MODBUS_UTILS_H

#include <WiFiClient.h>

// Kirim frame Modbus RTU simulasi untuk 8 sensor tekanan ban
void sendModbusFrame8Sensors(WiFiClient &client);

// Fungsi CRC16 untuk frame Modbus
uint16_t crc16(const uint8_t *data, uint8_t len);

#endif