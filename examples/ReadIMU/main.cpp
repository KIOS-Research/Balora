#include <Arduino.h>
#include <Balora.h>

Balora node("B1");
sensors_vec_t accel, gyro;

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.MPUInit();
    node.setLowPowerCPU();
    Serial.println("------IMU EXAMPLE------");
}

void loop()
{
    accel = node.getAccel();
    gyro = node.getGyro();

    Serial.println("-----Accelerometer-----");
    Serial.println(String("X: " + String(accel.x) + ", Y: " + String(accel.y) + " , Z: " + String(accel.z)));

    Serial.println("-------Gyroscope-------");
    Serial.println(String("X: " + String(gyro.x) + ", Y: " + String(gyro.y) + " , Z: " + String(gyro.z)));

    node.handleBattery();
    node.showBatteryState();
    delay(1000);
}