#ifndef SPI_RECEIVER_HPP
#define SPI_RECEIVER_HPP

#include <Arduino.h>
#include <SPI.h>

#include "Defines.hpp"

class SPIReceiver
{
public:
    static byte buffer[];
    static volatile unsigned int bufferPosi;
    static volatile boolean messageEndFlag;

    static void initSPIReceiver();
    static byte *getBuffer();
    static int getBufferAsInteger();
    static String getBufferAsBinary();
    static String getBufferAsHexadecimal();
    static String getBufferAsASCII();
    static void writeBuffer(unsigned int *data, size_t length);
    static void clearBuffer();
    // static void onSPIDataReceived();

    static void printBuffer();
    static void printBufferAsInteger();
    // static void printBufferAsBinary();
    static void printBufferAsHexadecimal();
    static void printBufferAsASCII();
};
#endif // SPI_RECEIVER_HPP
