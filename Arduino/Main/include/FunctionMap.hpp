#ifndef FUNCTION_MAP_HPP
#define FUNCTION_MAP_HPP

#include <string.h>

#include "Logger.hpp"

class FunctionMap
{
public:
    struct Function
    {
        String name;
        void (*function)(String *args);
    };

    static void init();
    static void addFunction(String name, void (*function)(String *args));
    static void addFunctions(const Function *functions, int count);
    static void callFunction(String name, String *args);

private:
    static Function *functions;
    static int functionCount;
};

#endif // FUNCTION_MAP_HPP
