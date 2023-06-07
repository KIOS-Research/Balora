#ifndef BALORA_H
#define BALORA_H

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
#include <Adafruit_NeoPixel.h>
#include <RadioLib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include <SD.h>
#include <SPI.h>
#include "FS.h"
#include <ESP32Time.h>
#include <WiFi.h>
// #include <ros.h>
// #include <std_msgs/String.h>
#include <BluetoothSerial.h>

class Balora
{
public:
    // constructor
    Balora(String id); // working

    void begin(void);
    void initWiFiClient(const char *wssid, const char *pass); // working
    // void rosInit(void);                                       // pending
    void setLowPowerCPU(void);                // working
    void setHighPowerCPU(void);               // working
    void loraTxRx(String mess);               // pending
    void logBattery(void);                    // seems to work, need to verify the sd contents
    void writeToSD(String msg);               // working, if card is hot-ejected must restart to continue
    void showBatteryState(void);              // working
    void handleBattery(void);                 // working
    void setPath(String path);                // working
    String getID(void);                       // working
    void getBattery(double &v, double &perc); // working
    sensors_vec_t getAccel(void);             // need definition of sensors_vec_t on main file, works
    sensors_vec_t getGyro(void);              // need definition of sensors_vec_t on main file, works
    String getMac(void);                      // working
    String hash(void);                        // working
    // void loraReceiverPublisher(void); // pending
    // void loraRos(String mess);        // pending
    void setBTName(String btName); // working
    void BTInit(void);             // working
    String BTReceive(void);        // working
    void BTSend(String msg);       // working
};

#endif // BALORA_H
