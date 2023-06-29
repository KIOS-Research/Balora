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
#if USEGPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
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
    Balora(String id);

    void begin(void);
    String getID(void);
    void setLowPowerCPU(void);
    void setHighPowerCPU(void);
    void showBatteryState(void);
    void handleBattery(void);
    void getBattery(double &v, double &perc);
    String getMac(void);
    String getHash(void);
    void setTimeOffset(int offset);
#if USEWIFI
    void initWiFiClient(const char *wssid, const char *pass);
#endif

#if USEMPU == 1
    void MPUInit(void);
    sensors_vec_t getAccel(void);
    sensors_vec_t getGyro(void);
#endif
#if USELORA
    void LoraInit(void);
    void loraTxRx(String mess);
#endif
#if USESD
    void SDInit(void);
    void logBattery(void);
    void writeToSD(String msg);
    void setPath(String path);
#endif

#if USEBT
    void BTInit(String btName);
    String BTReceive(void);
    void BTSend(String msg);
#endif
};

#endif // BALORA_H
