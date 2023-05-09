#include "Balora.h"

// SD Card SPI Pins
#define SD_MISO 19
#define SD_MOSI 23
#define SD_SCLK 18
#define SD_CS 25

// Baudrates for GPS and ROS/Serial
#define GPS_BAUD 9600
#define SERIAL_BAUD 115200

#define PIN 26      // NeoPixels Pin Number
#define NUMPIXELS 2 // Number of NeoPixels

#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP 60 * 2 // Deep Sleep 2 mins

#define LORA_TXEN_PIN 2  // SX1268 TX enable pin
#define LORA_RXEN_PIN 15 // SX1268 RX enable pin

// SX1268 LoRa Module SPI pins
#define LORA_CS 5
#define LORA_IRQ 14
#define LORA_RST 12
#define LORA_GPIO 27

SPIClass sdSPI(HSPI);

SX1268 radio = new Module(LORA_CS, LORA_IRQ, LORA_RST, LORA_GPIO);
Adafruit_MPU6050 mpu;
SFE_MAX1704X lipo(MAX1704X_MAX17048);
ESP32Time rtc(7200); // GMT+2 Offset
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

TinyGPSPlus gps;

String ID;
String ID_numb;

String message = "null";
int transmit_sec;
String pathSD = "/log.txt";

volatile bool receivedFlag = false;
volatile bool enableInterrupt = true;
volatile bool flag = false;

double vltg, perc;

const char *ssid;
const char *password;

// ROS Serial library dependencies
ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher pub("LAPTOP", &str_msg);

void messageCb(const std_msgs::String &msg)
{
    message = msg.data;
    flag = true;
}
ros::Subscriber<std_msgs::String> sub("/loremetry", &messageCb);

// Global Functions
void MPUInit(void)
{
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("File Written");
    }
    else
    {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\n", path);
    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        Serial.println("Message appended");
    }
    else
    {
        Serial.println("Append Failed");
    }
    file.close();
}
void SDInit()
{
    sdSPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, sdSPI))
    {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached.");
        return;
    }
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD init failed");
        return;
    }
    File file = SD.open(pathSD.c_str());
    if (!file)
    {
        Serial.println("File doesn't exist. Creating..");
        writeFile(SD, pathSD.c_str(), "begin\r\n");
    }
    else
    {
        Serial.println("File already exists");
    }
    file.close();
}
void setFlag(void)
{
    if (!enableInterrupt)
    {
        return;
    }
    receivedFlag = true;
}
void LoraInitialization(void)
{
    int state = radio.begin(434.0, 125.0, 9, 7, SX126X_SYNC_WORD_PRIVATE, 10, 8, 0, false);
    radio.setRfSwitchPins(26, 2);
    radio.setDio1Action(setFlag);
}
void batteryInit() // working
{
    if (lipo.begin() == false)
    {
        Serial.println(F("MAX17048 not detected. Please check wiring. Freezing."));
        while (1)
            ;
    }
    lipo.quickStart();
    lipo.setThreshold(20);
}

void print_wakeup_reason(void)
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Wakeup caused by touchpad");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Wakeup caused by ULP program");
        break;
    default:
        Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
        break;
    }
}

Balora::Balora(String id) // working
{
    ID = id;
    ID_numb = ID.substring(1, 2);
};

void Balora::begin(void)
{
    Wire.begin();
    // Serial.begin(SERIAL_BAUD);
    // // Serial1.begin(GPS_BAUD);
    mpu.begin();
    MPUInit();
    // LoraInitialization();
    batteryInit();
    showBatteryState();
    SDInit();
    pixels.begin();
    pixels.clear();

}

void Balora::setLowPowerCPU(void)
{
    Serial.println("Setting CPU to 80MHz");
    setCpuFrequencyMhz(80);
}
void Balora::setHighPowerCPU(void)
{
    Serial.println("Setting CPU to 240MHz");
    setCpuFrequencyMhz(240);
}
void Balora::loraTxRx(String mess)
{
    message = mess;
    transmit_sec = (transmit_sec + gps.time.second() + 1) % 60;
    String sec = String(transmit_sec);
    if (flag && sec.endsWith(ID_numb))
    {
        flag = false;
        String transmit_msg = String(String(ID) + "," + String(message));
        int state = radio.transmit(transmit_msg);
    }
    else
    {
        unsigned int i = 0;
        String str;
        int state = radio.receive(str);
        String msg = String(String(str) + "," + String(radio.getRSSI()) + "," + String(radio.getSNR()));
    }
}
void Balora::loraRos(String mess)
{
    message = mess;
    transmit_sec = (transmit_sec + gps.time.second() + 1) % 60;
    String sec = String(transmit_sec);
    if (flag && sec.endsWith(ID_numb))
    {
        flag = false;
        String transmit_msg = String(String(ID) + "," + String(message));
        int state = radio.transmit(transmit_msg);
    }
    else
    {
        unsigned int i = 0;
        String str;
        int state = radio.receive(str);
        String msg = String(String(str) + "," + String(radio.getRSSI()) + "," + String(radio.getSNR()));

        if (!str.length() == i)
        {
            const char *c = msg.c_str();
            str_msg.data = c;
            pub.publish(&str_msg);
        }
    }
    nh.spinOnce();
}
void Balora::logBattery(void)
{
    double voltage = lipo.getVoltage();
    double soc = lipo.getSOC();
    double alert = lipo.getAlert();
    String bat = String(String(rtc.getTime()) + "," + String(voltage) + "," + String(soc) + "\r\n");
    writeToSD(bat);
}
void Balora::writeToSD(String msg)
{
    appendFile(SD, pathSD.c_str(), msg.c_str());
}
void Balora::handleBattery(void)
{
    double soc = lipo.getSOC();
    if (soc < 25)
    {
        Serial.print("Battery percentage less than 25%, going into deep sleep: ");
        Serial.print(soc); // Print the battery state of charge
        Serial.println(" %");

        // Turn OFF LoRa
        digitalWrite(LORA_TXEN_PIN, LOW);
        digitalWrite(LORA_RXEN_PIN, LOW);

        pixels.clear();
        pixels.show();

        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

        Serial.println("Going to sleep now");
        Serial.flush();
        esp_deep_sleep_start();
    }
}
void Balora::setPath(String path)
{
    pathSD = path;
}

sensors_vec_t Balora::getAccel() {
    sensors_event_t a,g,temp;
    mpu.getEvent(&a,&g,&temp);

    return a.acceleration;
}

sensors_vec_t Balora::getGyro() {
    sensors_event_t a,g,temp;
    mpu.getEvent(&a,&g,&temp);

    return g.gyro;
}
void Balora::initWiFiClient(const char *wssid, const char *pass)
{
    ssid = wssid;
    password = pass;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}
void Balora::rosInit()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        ;
    }
    nh.initNode();
    nh.advertise(pub);
    nh.subscribe(sub);
}
String Balora::getID() // working
{
    return ID;
}
void Balora::showBatteryState()
{
    double soc = lipo.getSOC();
    if (soc < 50)
        pixels.setPixelColor(1, pixels.Color(25, 0, 0));
    else if (soc < 50)
        pixels.setPixelColor(1, pixels.Color(25, 12, 0));
    else if (soc < 75)
        pixels.setPixelColor(1, pixels.Color(25, 25, 0));
    else if (soc < 99)
        pixels.setPixelColor(1, pixels.Color(0, 25, 0));
    else
        pixels.setPixelColor(1, pixels.Color(0, 25, 0));
    pixels.show();
}

void Balora::getBattery(double &v, double &perc)
{
    v = lipo.getVoltage();
    perc = lipo.getSOC();
}

String Balora::getMac(){
    String mac = String(WiFi.macAddress());
    return mac;
}