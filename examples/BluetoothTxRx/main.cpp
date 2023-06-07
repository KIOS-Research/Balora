#include <Arduino.h>
#include <Balora.h>

Balora node("B1");
String id;
String btrx;

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    node.setBTName("TestBoard");
    node.BTInit();
    Serial.println("------BLUETOOTH EXAMPLE------");
}

void loop()
{
    node.BTSend("Hello!");

    btrx = node.BTReceive();
    Serial.println("Received Message:");
    Serial.println(btrx);

    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}