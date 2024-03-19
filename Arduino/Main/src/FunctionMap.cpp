#include "../include/FunctionMap.hpp"

FunctionMap::Function *FunctionMap::functions = nullptr;
int FunctionMap::functionCount = 0;

void FunctionMap::init()
{
    functions = new Function[0];
    functionCount = 0;
}

void FunctionMap::addFunction(String name, void (*function)(String *args))
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
        Logger::log(newFunctions[i].name);
        addFunction(newFunctions[i].name, newFunctions[i].function);
    }
}

void FunctionMap::callFunction(String name, String *args)
{
    for (int i = 0; i < functionCount; i++)
    {
        if (functions[i].name == name)
        {
            String log = "Calling function: ";
            log += name;
            log += " with args: ";
            for (int j = 0; j < sizeof(args); j++)
            {
                log += args[j];
                log += " ";
            }
            Logger::log(log);

            functions[i].function(args);
            return;
        }
    }

    String log = "Function not found: " + name;
    Logger::log(log);
}
