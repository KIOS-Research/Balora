# Balora

## Balora IoT Board Library

The Balora IoT Platform Library is a comprehensive library developed for the Balora IoT platform, which combines the power of LoRa, Bluetooth, WiFi, IMU, Battery, and the ESP32-PICO-D4 MCU. This library provides a unified interface and a set of convenient functions to simplify the development of IoT applications using the Balora custom board.

## Dependencies (Automatically imported on PlatformIO)

- [Sparkfun MAX1704x Fuel Gauge Arduino Library](https://github.com/sparkfun/SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library)
- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [RadioLib](https://github.com/jgromes/RadioLib)
- [Adafruit MPU6050](https://github.com/adafruit/Adafruit_MPU6050)
- [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)
- [ESP32Time](https://github.com/fbiego/ESP32Time)
- [BluetoothSerial](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial)

## Hardware Supported

The supported PCB design will be included in the PCB folder of the repository. This library should be able to work with any ESP32 based board that includes the following:

- Semtech SX1268 LoRa Module
- Adafruit MPU6050 IMU
- Quectel L80-R GNSS Module
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

| Function                                              | Description                                                                            |
| ----------------------------------------------------- | -------------------------------------------------------------------------------------- |
| Balora node("node id");                               | Initializes core modules and sets the node id.                                         |
| node.begin();                                         | Initializes all modules on board                                                       |
| node.initWiFiClient("SSID","PASSWORD");               | Initializes the WiFi Client with the given SSID and Password (Build Flag: -DUSEWIFI=1) |
| node.initMPU();                                       | Initializes MPU6050 (Build Flag: -DUSEMPU=1)                                           |
| node.setLowPowerCPU();                                | Sets MCU frequency to 80MHz                                                            |
| node.setHighPowerCPU();                               | Sets MCU frequency to 240MHz                                                           |
| node.initSD();                                        | Initializes SD Module (Build Flag: -DUSESD=1)                                          |
| node.loraTx("message");                               | LoRa Transmission Function (Build Flag: -DUSELORA=1 and -DUSEGPS=1)                    |
| String loraMsg = node.loraRx();                       | Returns LoRa Received String (Build Flag: -DUSELORA=1 and -DUSEGPS=1)                  |
| node.logBattery();                                    | Logs the battery level to the SD card (time, voltage, percentage)                      |
| node.writeToSD("message");                            | Writes given message to SD. (Build Flag: -DUSESD=1)                                    |
| node.handleBattery();                                 | REQUIRED ON LOOP to send board to deep sleep if battery < 25%                          |
| node.showBatteryState();                              | REQUIRED ON LOOP to display the battery level with NEOPIXELS                           |
| node.setPath("/log_path.txt");                        | Set SD Logging Path (default: "/log.txt") (Build Flag: -DUSESD=1)                      |
| String nodeID = node.getID();                         | Returns the ID of the node                                                             |
| node.getBattery(double& voltage, double& percentage); | Returns by reference the voltage and percentage of the battery                         |
| sensors_vec_t accel = node.getAccel();                | Returns the Accelerometer vector (see Example: IMU Data) (Build Flag: -DUSEMPU=1)      |
| sensors_vec_t gyro = node.getGyro();                  | Returns the Gyroscope vector (see Example: IMU Data) (Build Flag: -DUSEMPU=1)          |
| String macAd = node.getMac();                         | Returns the MAC address of the node                                                    |
| String nodeHash = node.getHash();                     | Returns the Hash of the MAC address                                                    |
| node.initBT("BTName");                                        | Initialize Bluetooth Serial Communication (Build Flag: -DUSEBT=1)                      |
| String btMsg = node.btRx();                      | Return String from Bluetooth Serial (Build Flag: -DUSEBT=1)                            |
| node.btTx("Message");                               | Send Message via Bluetooth Serial (Build Flag: -DUSEBT=1)                              |

## Usage

To save flash memory, preprocessor directives have been implemented. These directives must be included in the build flags of `platformio.ini`. Notice that the Bluetooth and WiFi implementations take up a large amount of the flash memory due to the driver libraries. All the function descriptions include the required build flags. Example environment to use MPU and LoRa:

```ini
[env:debugEnv]
build_type = debug
platform = espressif32
board = pico32
framework = arduino
lib_deps = https://github.com/KIOS-Research/Balora.git
monitor_speed = 115200
upload_speed = 921600
build_flags =
    -DUSEMPU=1
    -DUSELORA=1
    -DUSEGPS=1
```

## Important note about Battery Management

It is critical for the user to always include the `node.begin()` function to initialize the Battery Management module and always use `node.handleBattery()` and `node.showBatteryState()` in the loop function to avoid damaging the battery.

## Bluetooth Communication

The Bluetooth communication is achieved with the BluetoothSerial library that utilizes the Android Bluetooth Terminal
[app](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal).

## PCB

The [Gerber](https://github.com/KIOS-Research/Balora/tree/master/gerber) files can be used to manufacture the specific Balora PCB Design.
<img src="https://github.com/KIOS-Research/Balora/blob/master/images/balora_front.png?raw=true" width="500"/>
<img src="https://github.com/KIOS-Research/Balora/blob/master/images/balora_back.png?raw=true" width="500"/>

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
