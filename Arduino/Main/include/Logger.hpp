#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <Arduino.h>

#include "Defines.hpp"

class Logger
{
public:
    static void init();
    static void log();
    static void log(String message, bool newLine = true);
    static void log(int message, bool newLine = true);
    static void log(float message, bool newLine = true);
    static void log(double message, bool newLine = true);
    static void log(long message, bool newLine = true);
    static void log(unsigned int message, bool newLine = true);
    static void log(unsigned long message, bool newLine = true);
    static void log(char message, bool newLine = true);
    static void log(char *message, bool newLine = true);
    static void log(bool message, bool newLine = true);

    private:
    static void logLog(String message, bool newLine);
};

#endif // LOGGER_HPP
