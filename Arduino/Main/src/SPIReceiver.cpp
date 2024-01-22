#include "../include/SPIReceiver.hpp"

byte SPIReceiver::buffer[SPI_BUFFER_SIZE];
volatile unsigned int SPIReceiver::bufferPosition = 0;
volatile boolean SPIReceiver::messageEndFlag = false;

// SPI interrupt routine
ISR(SPI_STC_vect)
{
    // Ignore error squiggle for SPDR (SPI Data Register)
    byte incomingByte = SPDR;

    if (incomingByte == SPI_EOT)
    {
        SPIReceiver::messageEndFlag = true;
        return;
    }

    if (SPIReceiver::bufferPosition < sizeof(SPIReceiver::buffer) - 1)
    {
        SPIReceiver::buffer[SPIReceiver::bufferPosition++] = incomingByte;
    }
}

void SPIReceiver::init()
{
    pinMode(MISO, OUTPUT);

    // Ignore error squiggle for SPCR (SPI Control Register)
    SPCR = (1 << SPE)                                     // Enable SPI
           | (1 << SPIE)                                  // Enable SPI interrupt
           | (SPI_DATA_ORDER_MSB_FIRST << DORD)           // MSB first
           | (SPI_SLAVE << MSTR)                          // Set as slave
           | (SPI_CLOCK_POLARITY_IDLE_LOW << CPOL)        // SCK low when idle
           | (SPI_CLOCK_PHASE_SAMPLE_ON_LEADING << CPHA); // Sample on leading edge
}

byte *SPIReceiver::getBuffer()
{
    return buffer;
}

int SPIReceiver::getBufferAsInteger()
{
    int number = 0;
    for (size_t i = 0; i < bufferPosition; i++)
    {
        number += buffer[i] << (8 * i);
    }
    return number;
}

String SPIReceiver::getBufferAsBinary()
{
    String bufferString = "";
    for (size_t i = 0; i < bufferPosition; i++)
    {
        bufferString += String(buffer[bufferPosition - i - 1], BIN);
    }
    return bufferString;
}

String SPIReceiver::getBufferAsHexadecimal()
{
    String bufferString = "";
    for (size_t i = 0; i < bufferPosition; i++)
    {
        bufferString += String(buffer[bufferPosition - i - 1], HEX);
    }
    return bufferString;
}

String SPIReceiver::getBufferAsASCII()
{
    String bufferString = "";
    for (size_t i = 0; i < bufferPosition; i++)
    {
        bufferString += String((char) buffer[i]);
    }
    return bufferString;
}

void SPIReceiver::writeBuffer(unsigned int *data, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        buffer[i] = data[i];
    }
    bufferPosition = length;
}

void SPIReceiver::clearBuffer()
{
    for (size_t i = 0; i < bufferPosition; i++)
    {
        buffer[i] = 0;
    }
    bufferPosition = 0;
    messageEndFlag = false;
}

void SPIReceiver::printBuffer()
{
    for (size_t i = 0; i < bufferPosition; i++)
    {
        Logger::log(buffer[i], false);
        Logger::log(" ", false);
    }
    Logger::log();
}

void SPIReceiver::printBufferAsInteger()
{
    Logger::log(getBufferAsInteger());
}

void SPIReceiver::printBufferAsHexadecimal()
{
    Logger::log(getBufferAsHexadecimal());
}

void SPIReceiver::printBufferAsASCII()
{
    Logger::log(getBufferAsASCII());
}