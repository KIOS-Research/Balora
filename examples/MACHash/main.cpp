#include <Arduino.h>
#include <Balora.h>

Balora node("B1");
String macAd;
String hash;

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    Serial.println("------MAC & HASH EXAMPLE------");
    macAd = node.getMac();
    hash = node.getHash();
    Serial.print("MAC Address: ");
    Serial.println(macAd);
    Serial.print("Hash: ");
    Serial.println(hash);
}

void loop()
{
    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}