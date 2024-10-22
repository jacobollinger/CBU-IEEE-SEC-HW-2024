#include "../include/Logger.hpp"

char Logger::lastChar = '\0';

void Logger::init()
{
#if DEBUG
    Serial.begin(BAUDRATE);
    lastChar = '\n';
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
        Serial.print("LOG: ");
        Serial.println(message);
    }
    else
    {
        if (lastChar == '\n')
            Serial.print("LOG: ");
        Serial.print(message);
    }

    lastChar = message[message.length() - 1];
#endif
}
