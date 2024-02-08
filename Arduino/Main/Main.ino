#include "./include/Defines.hpp"
#include "./include/FunctionMap.hpp"
#include "./include/Logger.hpp"
#include "./include/SPIReceiver.hpp"

void setup()
{
    Logger::init();

    Logger::log("Setting up FunctionMap");
    FunctionMap::init();
    // TODO: Add functions from other modules
    
    Logger::log("Starting SPI Slave");
    SPIReceiver::init();
    Logger::log("Initialized.\tEOT: ", false);
    Logger::log(SPI_EOT);
    Logger::log("Buffer size: ", false);
    Logger::log(SPI_BUFFER_SIZE);
}

void loop()
{
    if (SPIReceiver::messageEndFlag)
    {
        logBuffer();

        String buffer = SPIReceiver::getBufferAsASCII();
        
        // TODO: Execute command from buffer

        SPIReceiver::clearBuffer();
    }
}

void logBuffer()
{
    Logger::log("Message received");
    Logger::log("Buffer size: ", false);
    Logger::log(SPIReceiver::bufferPosition);
    Logger::log("Buffer: ", false);
    SPIReceiver::printBuffer();
    Logger::log("Int: ", false);
    SPIReceiver::printBufferAsInteger();
    Logger::log("Hex: ", false);
    SPIReceiver::printBufferAsHexadecimal();
    Logger::log("UTF-8: ", false);
    SPIReceiver::printBufferAsASCII();
    Logger::log();
}