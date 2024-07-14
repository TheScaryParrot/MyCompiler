#pragma once

#include <map>

#include "../VariableLocation.cpp"

class Environment
{
   private:
    std::map<std::string, VariableLocation*> variables;

    std::map<std::string, std::string> compilerVarStrings;
    std::map<std::string, int> compilerVarInts;

   public:
    ~Environment()
    {
        for (auto item : variables)
        {
            delete item.second;
        }
    };

    VariableLocation* GetVariableLocation(std::string name) { return variables[name]; };

    std::string GetCompilerVarString(std::string name) { return compilerVarStrings[name]; };
    int GetCompilerVarInt(std::string name) { return compilerVarInts[name]; };
};
