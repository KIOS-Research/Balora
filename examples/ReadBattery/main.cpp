#include <Arduino.h>
#include <Balora.h>

Balora node("B1");
double voltage, percentage;

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    while (!Serial.available())
    {
        ;
    }
    Serial.println("---BATTERY EXAMPLE---");
}

void loop()
{
    node.getBattery(voltage, percentage);

    Serial.printf("Voltage: %.2f V, Percentage: %.2f %\n", voltage, percentage);

    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}