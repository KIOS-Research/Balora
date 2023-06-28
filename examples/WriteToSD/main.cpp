/*Add:
build_flags =
    -DUSESD=1
To platformio.ini */

#include <Arduino.h>
#include <Balora.h>

Balora node("B1");

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.SDInit();
    node.setLowPowerCPU();
    node.setPath("/testFile.txt");
    Serial.println("------LOG TO SD EXAMPLE------");
}

void loop()
{
    node.writeToSD("Test\n");

    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}