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
    ~Environment();

    void AddCallable(std::string name, Callable* callable);
    Callable* GetCallable(std::string name);
    void ExecuteCallable(std::string name, ICodeGenerator* codeGenerator);

   private:
    std::map<std::string, Callable*> callables;
};

Environment::~Environment()
{
    for (auto const& callable : callables)
    {
        delete callable.second;
    }
}

void Environment::AddCallable(std::string name, Callable* callable) { callables[name] = callable; }

Callable* Environment::GetCallable(std::string name)
{
    if (callables.find(name) == callables.end())
    {
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