# Balora

## Balora IoT Board Library

The Balora IoT Platform Library is a comprehensive library developed for the Balora IoT platform, which combines the power of LoRa, Bluetooth, WiFi, IMU, Battery, and the ESP32-PICO-D4 MCU. This library provides a unified interface and a set of convenient functions to simplify the development of IoT applications using the Balora custom board.

## Dependencies (Automatically imported on PlatformIO)

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
- GPS Module (TBD)
- Adafruit NeoPixels (x2)
- microSD Reader
- Sparkfun MAX17048 Battery Monitoring IC

## Installation

Add the following line to your `platformio.ini` file:

`lib_deps = https://github.com/KIOS-Research/Balora.git`

OR

- Clone the Repository: `git clone https://github.com/KIOS-Research/Balora.git`
- Add the library to you PlatformIO Project: `platformio lib install /path/to/Balora`
- Include the library to your project `#include <Balora.h>`

## Functions

| Function                                              | Description                                                       |
| ----------------------------------------------------- | ----------------------------------------------------------------- |
| Balora node("node id");                               | Initializes core modules and sets the node id.                    |
| node.begin();                                         | Initializes all modules on board                                  |
| node.initWiFiClient("SSID","PASSWORD");               | Initializes the WiFi Client with the given SSID and Password      |
| node.rosInit();                                       | Initializes ROS subscribe and publish PENDING                     |
| node.setLowPowerCPU();                                | Sets MCU frequency to 80MHz                                       |
| node.setHighPowerCPU();                               | Sets MCU frequency to 240MHz                                      |
| node.loraTxRx("message");                             | Crude mesh LoRa communication (see section: LoRa Communication)   |
| node.logBattery();                                    | Logs the battery level to the SD card (time, voltage, percentage) |
| node.writeToSD("message");                            | Writes given message to SD.                                       |
| node.handleBattery();                                 | REQUIRED ON LOOP to send board to deep sleep if battery < 25%     |
| node.showBatteryState();                              | REQUIRED ON LOOP to display the battery level with NEOPIXELS      |
| node.setPath("/log_path.txt");                        | Set SD Logging Path (default: "/log.txt")                         |
| String nodeID = node.getID();                         | Returns the ID of the node                                        |
| node.getBattery(double& voltage, double& percentage); | Returns by reference the voltage and percentage of the battery    |
| sensors_vec_t accel = node.getAccel();                | Returns the Accelerometer vector (see Example: IMU Data)          |
| sensors_vec_t gyro = node.getGyro();                  | Returns the Gyroscope vector (see Example: IMU Data)              |
| String macAd = node.getMac();                         | Returns the MAC address of the node                               |
| String nodeHash = node.hash();                        | Returns the Hash of the MAC address                               |
| node.loraReceiverPublisher();                         | LoRa Reception and Publish to ROS Topic                           |
| node.loraRos("message");                              | LoRa and ROS Receive-Publish and Transmit-Subscribe               |
| node.setBTName("Name");                               | Set Bluetooth Broadcast Name (default: BaloraID)                  |
| node.BTInit();                                        | Initialize Bluetooth Serial Communication                         |
| String btMsg = node.BTReceive();                      | Return String from Bluetooth Serial                               |
| node.BTSend("Message");                               | Send Message via Bluetooth Serial                                 |

## LoRa Communication

The LoRa mesh implementation is carried out by assigning a timeslot to each of the nodes. The node number defines the time slot. Each slot is assigned per second. Example: Node B3 is assigned the 3rd second slot.

## Contributing

Everyone is welcome to participate in this project. Whether you are helping others to resolve issues, reporting a new issue that hasn't yet been discovered, suggesting a new feature that would benefit your workflow, or writing code (or tests, or scripts, or ...), we value your time and effort.

The path for contribution starts with the [Issues](https://github.com/KIOS-Research/Balora/issues). You can create a new issue in case you discover a new bug or you have a useful suggestion that you’d like to be implemented. If you want to contribute code, fork this repo to your own account. Make your commits on your dev branch (or one based on dev). Once you are finished, you can open a Pull Request to test the code and discuss merging your changes back into the community repository.

## License

The Balora IoT Platform Library is open-source software licensed under the [EUPL License](https://github.com/KIOS-Research/Balora/blob/master/LICENSE.md).

## Contributors

### The library was developed by

- [Theodosis Pasiali](https://www.linkedin.com/in/theodosis-pasiali/)
- [Maria Karatzia](https://www.linkedin.com/in/maria-karatzia/)
- [Panagiotis Kolios](https://www.kios.ucy.ac.cy/pkolios/)

### PCB Design by

- [Odysseas Economides](https://www.linkedin.com/in/odysseas-economides/)
