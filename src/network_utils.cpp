#include "network_utils.h"

const char *ssid = "Wokwi-GUEST";
const char *password = "";
const char *SERVER_IP = "192.168.100.23";
const uint16_t SERVER_PORT = 5000;

WiFiClient tcpClient;

void connectWiFi()
{
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());
}

bool ensureTCPConnected()
{
    if (!tcpClient.connected())
    {
        Serial.printf("Connecting to TCP %s:%d\n", SERVER_IP, SERVER_PORT);
        if (!tcpClient.connect(SERVER_IP, SERVER_PORT))
        {
            Serial.println("TCP connect failed");
            return false;
        }
        Serial.println("TCP connected");
    }
    return true;
}