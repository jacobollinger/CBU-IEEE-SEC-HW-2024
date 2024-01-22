#include "../include/Logger.hpp"

void Logger::init()
{
#if DEBUG
    Serial.begin(BAUDRATE);
    Serial.println("Starting SPI Slave");
#endif
}

void Logger::log()
{
    logLog("", true);
}

void Logger::log(String message, bool newLine = true)
{
    logLog(message, newLine);
}

void Logger::log(int message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(float message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(double message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(long message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(unsigned int message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(unsigned long message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(char message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(char *message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::log(bool message, bool newLine = true)
{
    logLog(String(message), newLine);
}

void Logger::logLog(String message, bool newLine)
{
#if DEBUG
    if (newLine)
    {
        Serial.println(message);
    }
    else
    {
        Serial.print(message);
    }
#endif
}
