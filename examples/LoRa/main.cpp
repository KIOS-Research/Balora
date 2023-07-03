/* Add:
build_flags =
    -DUSELORA=1
    -DUSEGPS=1
To platformio.ini */

#include <Arduino.h>
#include <Balora.h>

Balora node("B1");

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    node.loraInit();
    Serial.println("------LORA TX and RX Example------");
}

void loop()
{
    Serial.println(node.loraRx());
    // node.loraTx("Message");
    node.handleBattery();
    node.showBatteryState();
    delay(10);
    // delay(1000);
}
