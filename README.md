# Balora

## Balora IoT Board Library

The library includes all the basic components needed to function the BaLoRa IoT Board.

## Dependencies

- [Sparkfun MAX1704x Fuel Gauge Arduino Library](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library)
- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [RadioLib v4.6.0](https://github.com/jgromes/RadioLib)
- [Adafruit MPU6050](https://github.com/adafruit/Adafruit_MPU6050)
- [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)
- [ESP32Time](https://github.com/fbiego/ESP32Time)
- [BluetoothSerial](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial)
- [ROSSerial](https://github.com/frankjoshua/rosserial_arduino_lib)

## Hardware Supported

The supported PCB design will be included in the PCB folder of the repository. This library should be able to work with any ESP32 based board that includes the following:

- Semtech SX1268 LoRa Module
- Adafruit MPU6050 IMU
- to be added

## Usage

### Creating Balora object

```c++
Balora node("node id"); // Initializes all modules and sets the node id.
```

### Functions

Initializes all modules on board

```c++
node.begin();
```

Initializes the WiFi Client with the given SSID and Password

```c++
node.initWiFiClient("SSID","PASSWORD");
```

Initializes ROS subscribe and publish PENDING

```c++
node.rosInit();
```

Sets MCU frequency to 80MHz

```c++
node.setLowPowerCPU();
```

Sets MCU frequency to 240MHz

```c++
node.setHighPowerCPU();
```

Crude mesh LoRa communication (see section: LoRa Communication)

```c++
node.loraTxRx("message");
```

Logs the battery level to the SD card (time, voltage, percentage)

```c++
node.logBattery();
```

Writes given message to SD.

```c++
node.writeToSD("message");
```

REQUIRED ON LOOP to send board to deep sleep if battery < 25%

```c++
node.handleBattery();
```

REQUIRED ON LOOP to display the battery level with NEOPIXELS

```c++
node.showBatteryState();
```

Set SD Logging Path (default: "/log.txt")

```c++
node.setPath("/log_path.txt");
```

Returns the ID of the node

```c++
String nodeID = node.getID();
```

Returns by reference the voltage and percentage of the battery

```c++
node.getBattery(double& voltage, double& percentage);
```

Returns the Accelerometer vector (see Example: IMU Data)

```c++
sensors_vec_t accel = node.getAccel();
```

Returns the Gyroscope vector (see Example: IMU Data)

```c++
sensors_vec_t gyro = node.getGyro();
```

Returns the MAC address of the node

```c++
String macAd = node.getMac();
```

Returns the Hash of the MAC address

```c++
String nodeHash = node.hash();
```

LoRa Reception and Publish to ROS Topic

```c++
loraReceiverPublisher();
```

LoRa and ROS Receive-Publish and Transmit-Subscribe

```c++
loraRos("message");
```

Initialize Bluetooth Serial Communication

```c++
node.BTInit();
```

Set Bluetooth Broadcast Name (default: NodeID)

```c++
node.setBTName("Name");
```

Return String from Bluetooth Serial

```c++
String btMsg = node.BTReceive();
```

Send Message via Bluetooth Serial

```c++
node.BTSend("Message");
```

## LoRa Communication

The LoRa mesh implementation is carried out by assigning a timeslot to each of the nodes. The node number defines the time slot. Each slot is assigned per second. Example: Node B3 is assigned the 3rd second slot.
