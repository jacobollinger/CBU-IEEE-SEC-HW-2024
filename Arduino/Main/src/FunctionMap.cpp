#include "../include/FunctionMap.hpp"

FunctionMap::Function *FunctionMap::functions = nullptr;
int FunctionMap::functionCount = 0;

void FunctionMap::init()
{
    functions = new Function[0];
    functionCount = 0;
}

void FunctionMap::addFunction(const char *name, void (*function)(const char *args[]))
{
    Function *newFunctions = new Function[functionCount + 1];
    for (int i = 0; i < functionCount; i++)
    {
        newFunctions[i] = functions[i];
    }
    newFunctions[functionCount].name = name;
    newFunctions[functionCount].function = function;
    functionCount++;
    delete[] functions;
    functions = newFunctions;
}

void FunctionMap::addFunctions(const Function *newFunctions, int count)
{
    Logger::log("Size of newFunctions: ", false);
    Logger::log(sizeof(newFunctions));
    for (int i = 0; i < count; i++)
    {
        Logger::log("Adding function: ", false);
        Logger::log((String)newFunctions[i].name);
        addFunction(newFunctions[i].name, newFunctions[i].function);
    }
}

void FunctionMap::callFunction(const char *name, const char *args[])
{
    for (int i = 0; i < functionCount; i++)
    {
        if (strcmp(functions[i].name, name) == 0)
        {
            Logger::log("Calling function: ", false);
            Logger::log((String)functions[i].name);
            functions[i].function(args);
            return;
        }
    }
}
