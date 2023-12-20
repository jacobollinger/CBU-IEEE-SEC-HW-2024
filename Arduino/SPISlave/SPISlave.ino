#include "include/SPIReceiver.hpp"

void setup()
{
    Serial.begin(115200);
    SPIReceiver::initSPIReceiver();
    Serial.println("Initialized\tEOT: " + String(SPI_EOT));
}

void loop()
{
    if (SPIReceiver::messageEndFlag)
    {
        Serial.println("Message received");
        Serial.println("Buffer size: " + String(SPIReceiver::bufferPosi));
        Serial.print("Buffer: ");
        SPIReceiver::printBuffer();
        Serial.print("Int: ");
        SPIReceiver::printBufferAsInteger();
        Serial.print("Hex: ");
        SPIReceiver::printBufferAsHexadecimal();
        Serial.print("UTF-8: ");
        SPIReceiver::printBufferAsASCII();


        Serial.println();
        SPIReceiver::clearBuffer();
    }
}