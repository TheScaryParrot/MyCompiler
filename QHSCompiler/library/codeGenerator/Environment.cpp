#pragma once

#include <map>

#include "Callable.cpp"

class Environment
{
   public:
    void AddCallable(std::string name, Callable* callable);
    Callable* GetCallable(std::string name);

   private:
    std::map<std::string, Callable*> callables;
};

void Environment::AddCallable(std::string name, Callable* callable) { callables[name] = callable; }

Callable* Environment::GetCallable(std::string name) { return callables[name]; }