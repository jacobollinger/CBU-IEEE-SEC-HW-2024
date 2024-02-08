#ifndef FUNCTION_MAP_HPP
#define FUNCTION_MAP_HPP

#include <string.h>

#include "Logger.hpp"

class FunctionMap
{
public:
    struct Function
    {
        const char *name;
        void (*function)(const char *args[]);
    };

    static void init();
    static void addFunction(const char *name, void (*function)(const char *args[]));
    static void addFunctions(const Function *functions, int count);
    static void callFunction(const char *name, const char *args[]);

private:
    static Function *functions;
    static int functionCount;
};

#endif // FUNCTION_MAP_HPP
