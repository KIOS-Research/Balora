/* Add:
build_flags =
    -DUSELORA=1
    -DUSESD=1
To platformio.ini */

#include <Arduino.h>
#include <Balora.h>

String msg;
// String rx; // Uncomment For Transmitter, Comment for Receiver

Balora node("B4");

void setup()
{
    Serial.begin(115200);
    node.begin();
    node.setLowPowerCPU();
    node.loraInit();
    node.setPath("/Lora_rx.txt");
    node.initSD();
    Serial.println("------LORA and SD------");
}

void loop()
{
    // msg = String(String(node.getID()) + "\n"); // Uncomment For Transmitter, Comment for Receiver
    // node.loraTx(msg);                          // Uncomment For Transmitter, Comment for Receiver
    // rx = node.loraRx();                        // Uncomment For Transmitter, Comment for Receiver
    // if (rx.startsWith("A"))                    // Uncomment For Transmitter, Comment for Receiver
    // {                                          // Uncomment For Transmitter, Comment for Receiver
    //   Serial.println(rx);                      // Uncomment For Transmitter, Comment for Receiver
    // }                                          // Uncomment For Transmitter, Comment for Receiver

    msg = node.loraRx();     // Uncomment For Receiver, Comment for Transmitter
    if (msg.startsWith("B")) // Uncomment For Receiver, Comment for Transmitter
    {                        // Uncomment For Receiver, Comment for Transmitter
        Serial.println(msg); // Uncomment For Receiver, Comment for Transmitter
        node.writeToSD(msg); // Uncomment For Receiver, Comment for Transmitter
        node.loraTx("ACK");  // Uncomment For Receiver, Comment for Transmitter
    }                        // Uncomment For Receiver, Comment for Transmitter
    node.handleBattery();
    node.showBatteryState();
    // delay(1000); // Uncomment for Transmitter, Comment for Receiver
}