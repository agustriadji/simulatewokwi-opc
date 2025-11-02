#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <WiFi.h>
#include <WiFiClient.h>

// Konfigurasi jaringan
extern const char *ssid;
extern const char *password;
extern const char *SERVER_IP;
extern const uint16_t SERVER_PORT;

// TCP client global
extern WiFiClient tcpClient;

// Inisialisasi WiFi
void connectWiFi();

// Pastikan TCP client terkoneksi
bool ensureTCPConnected();

#endif