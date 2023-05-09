# Balora
Balora IoT Board Library UPDATEME

The library includes all the basic components needed to function the BaLoRa IoT Board.

## Dependencies
 * [Sparkfun MAX1704x Fuel Gauge Arduino Library](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library)
 * [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
 * [RadioLib v4.6.0](https://github.com/jgromes/RadioLib)
 * [Adafruit MPU6050](https://github.com/adafruit/Adafruit_MPU6050)
 * [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)
 * [ESP32Time](https://github.com/fbiego/ESP32Time)
 * [ROSSerial](https://github.com/frankjoshua/rosserial_arduino_lib)
 
 ## Hardware Supported 
TBD
 
 ## Usage
 ### Creating Balora object
 
```
Balora node("node id"); // Initializes all modules and sets the node id. (default: "B0")
```
### Functions

Initializes all modules on board with their corresponding pins
```
node.begin();
```
Sets MCU frequency to 80MHz
```
node.setLowPowerCPU(); 
```
Sets MCU frequency to 240MHz
```
node.setHighPowerCPU(); 
```
Crude mesh LoRa communication (see section: LoRa Communication)
```
node.loraTxRx("message"); 
```
Set WiFi SSID and Password
```
node.setWifi(&SSID,&PASSWORD);
```
Initialize ROS with WiFi
```
node.rosInit();
```
Crude mesh LoRa with ROS
```
node.loraRos("message");
```
Logs the battery level to the SD card (time, voltage, percentage)
```
node.logBattery();
```
Returns MPU values for accelerometer
```
node.getAccel(&aX,&aY,&aZ);
```
Returns MPU values for gyroscope
```
node.getGyro(&gX,&gY,&gZ);
```
Writes given message to SD.
```
node.writeToSD("message"); 
```
REQUIRED ON LOOP to send board to deep sleep if battery < 25%
```
node.handleBattery();
```
Sets the file path for SD write (default: "/log.txt")
```
node.setPath("/path.txt"); 
```

## LoRa Communication
The LoRa mesh implementation is carried out by assigning a timeslot to each of the nodes. The node number defines the time slot. Each slot is assigned per second. Example: Node B3 is assigned the 3rd second slot. 
