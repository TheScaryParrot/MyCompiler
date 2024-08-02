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
    ~Environment()
    {
        for (auto const& callable : callables)
        {
            delete callable.second;
        }
    }

    void AddCallable(std::string name, Callable* callable) { callables[name] = callable; }
    Callable* GetCallable(std::string name)
    {
        if (callables.find(name) == callables.end())
        {
            return nullptr;
        }

        return callables[name];
    }
    void ExecuteCallable(std::string name, ICodeGenerator* codeGenerator)
    {
        Callable* callable = GetCallable(name);

        if (callable == nullptr)
        {
            return;
        }

        callable->Execute(codeGenerator);
    }

   private:
    std::map<std::string, Callable*> callables;
};