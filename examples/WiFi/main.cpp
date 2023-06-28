/* Add:
build_flags =
    -DUSEWIFI=1
To platformio.ini */

#include <Arduino.h>
#include <Balora.h>

Balora node("B1");
String id;

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    Serial.println("------WiFi EXAMPLE------");
    node.initWiFiClient("TestSSID", "TestPW");
}

void loop()
{
    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}