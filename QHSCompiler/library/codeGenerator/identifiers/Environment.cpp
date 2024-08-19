#pragma once

#include <functional>
#include <map>
#include <string>

#include "../utils/Logger.cpp"
#include "Identifier.cpp"

class Environment
{
   public:
    ~Environment()
    {
        for (auto const& identifier : identifiers)
        {
            delete identifier.second;
        }
    }

    void AddIdentifier(std::string name, Identifier* identifier) { identifiers[name] = identifier; }
    Identifier* GetIdentifier(std::string name)
    {
        if (identifiers.find(name) == identifiers.end())
        {
            return nullptr;
        }

        return identifiers[name];
    }

   private:
    std::map<std::string, Identifier*> identifiers;
};