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
    node.LoraInit();
    Serial.println("------LORA TX and RX Example------");
}

void loop()
{
    node.loraTxRx(node.getID());

    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}