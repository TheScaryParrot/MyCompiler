#pragma once

#include <functional>
#include <map>
#include <string>

#include "../utils/Logger.cpp"
#include "Callable.cpp"
#include "ICodeGenerator.cpp"

class Environment
{
   public:
    void AddCallable(std::string name, Callable* callable);
    Callable* GetCallable(std::string name);
    void ExecuteCallable(std::string name, ICodeGenerator* codeGenerator);

   private:
    std::map<std::string, Callable*> callables;
};

void Environment::AddCallable(std::string name, Callable* callable) { callables[name] = callable; }

Callable* Environment::GetCallable(std::string name)
{
    if (callables.find(name) == callables.end())
    {
        Logger.Log("Callable " + name + " not found", Logger::ERROR);
        return nullptr;
    }

    return callables[name];
}

void Environment::ExecuteCallable(std::string name, ICodeGenerator* codeGenerator)
{
    Callable* callable = GetCallable(name);

    if (callable == nullptr)
    {
        return;
    }

    callable->Execute(codeGenerator);
}