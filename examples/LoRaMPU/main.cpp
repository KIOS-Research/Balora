/* Add:
build_flags =
    -DUSELORA=1
    -DUSEGPS=1
    -DUSEMPU=1
To platformio.ini */

#include <Arduino.h>
#include <Balora.h>

sensors_vec_t gyro;
String msg;

Balora node("B5");

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    node.initMPU(); // Uncomment For Transmitter, Comment for Receiver
    node.loraInit();
    Serial.println("------LORA and Gyroscope------");
}

void loop()
{
    gyro = node.getGyro();                                              // Uncomment For Transmitter, Comment for Receiver
    msg = String(String(node.getID()) + ", Gyro Y: " + String(gyro.y)); // Uncomment For Transmitter, Comment for Receiver
    node.loraTx(msg);                                                   // Uncomment For Transmitter, Comment for Receiver
    // msg = node.loraRx(); // Uncomment For Receiver, Comment for Transmitter
    // Serial.println(msg); // Uncomment For Receiver, Comment for Transmitter
    node.handleBattery();
    node.showBatteryState();
    delay(10);
}