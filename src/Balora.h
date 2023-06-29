#ifndef BALORA_H
#define BALORA_H

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <ESP32Time.h>
#include <WiFi.h>
#if USELORA
#include <RadioLib.h>
#endif
#if USEMPU
#include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
#endif
#if USEGPS
#include <TinyGPS++.h>
#endif
#if USESD
#include <SD.h>

#include "FS.h"
#endif

#if USEBT
#include <BluetoothSerial.h>
#endif

class Balora
{
public:
    // constructor
    Balora(String id); // working

    void begin(void);
    String getID(void);                       // working
    void setLowPowerCPU(void);                // working
    void setHighPowerCPU(void);               // working
    void showBatteryState(void);              // working
    void handleBattery(void);                 // working
    void getBattery(double &v, double &perc); // working
    String getMac(void);                      // working
    String getHash(void);
#if USEWIFI
    void initWiFiClient(const char *wssid, const char *pass); // working
#endif
// // void rosInit(void);                                       // pending
#if USEMPU == 1
    void MPUInit(void);           // working
    sensors_vec_t getAccel(void); // need definition of sensors_vec_t on main file, works
    sensors_vec_t getGyro(void);  // need definition of sensors_vec_t on main file, works
#endif
#if USELORA
    void LoraInit(void);        // pending
    void loraTxRx(String mess); // pending
#endif
#if USESD
    void SDInit(void);          // working
    void logBattery(void);      // seems to work, need to verify the sd contents
    void writeToSD(String msg); // working, if card is hot-ejected must restart to continue
    void setPath(String path);  // working
#endif

    // working
// // void loraReceiverPublisher(void); // pending
// // void loraRos(String mess);        // pending
// // void setBTName(String btName); // working
#if USEBT
    void BTInit(String btName); // working
    String BTReceive(void);     // working
    void BTSend(String msg);    // working
#endif
};

#endif // BALORA_H
