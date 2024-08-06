#pragma once

#include <functional>
#include <map>
#include <string>

#include "../utils/Logger.cpp"
#include "ICallable.cpp"

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

    void AddCallable(std::string name, ICallable* callable) { callables[name] = callable; }
    ICallable* GetCallable(std::string name)
    {
        if (callables.find(name) == callables.end())
        {
            return nullptr;
        }

        return callables[name];
    }

   private:
    std::map<std::string, ICallable*> callables;
};