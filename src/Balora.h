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
#endif
// #if USEGPS
// #include <TinyGPS++.h>
// #include <SoftwareSerial.h>
// #endif
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
    Balora(String id);

    void begin(void);
    String getID(void);
    void setLowPowerCPU(void);
    void setHighPowerCPU(void);
    void showBatteryState(void);
    void handleBattery(void);
    void getBattery(double &v, double &perc);
    String getMac(void);
    String getHashMac(void);
    void setTimeOffset(int offset);

    void setLedColor(int color);
    void setLedBrightess(int br);
    void showLed(void);

#if USEWIFI
    void initWiFiClient(const char *wssid, const char *pass);
#endif

#if USEMPU
    void initMPU(void);
    sensors_vec_t getAccel(void);
    sensors_vec_t getGyro(void);
#endif
#if USELORA
    void loraInit(void);
    void loraTx(String mess);
    String loraRx(void);
    float getLoraRSSI(void);
    float getLoraSNR(void);
#endif
#if USESD
    void initSD(void);
    void logBattery(void);
    void writeToSD(String msg);
    void setPath(String path);
#endif

#if USEBT
    void initBT(String btName);
    String btRx(void);
    void btTx(String msg);
#endif
};

#endif // BALORA_H
