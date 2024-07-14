#pragma once

#include "../VariableLocation.cpp"
#include "../utils/Map.cpp"
#include "IEnvironment.cpp"

class Environment : public IEnvironment
{
   private:
    Map<std::string, VariableLocation*> variables;
    Map<std::string, Type*> types;

    Map<std::string, std::string*> compilerVarStrings;
    Map<std::string, int*> compilerVarInts;

   public:
    ~Environment()
    {
        for (auto item : variables)
        {
            delete item.second;
        }
    };

    virtual Map<std::string, VariableLocation*>* GetVariableMap() override { return &variables; }
    virtual Map<std::string, Type*>* GetTypeMap() override { return &types; }

    virtual Map<std::string, std::string*>* GetCompilerVarStringMap() override { return &compilerVarStrings; }
    virtual Map<std::string, int*>* GetCompilerVarIntMap() override { return &compilerVarInts; }
};
