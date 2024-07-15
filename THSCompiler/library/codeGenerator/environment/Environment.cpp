#pragma once

#include "../utils/Map.cpp"
#include "../varLocation/IVariableLocation.cpp"
#include "IEnvironment.cpp"

class Environment : public IEnvironment
{
   private:
    Map<std::string, IVariableLocation*> variables;
    Map<std::string, Type*> types;

    Map<std::string, std::string*> compilerVarStrings;
    Map<std::string, int*> compilerVarInts;

    Type* numConstType = nullptr;

   public:
    ~Environment()
    {
        for (auto item : variables)
        {
            delete item.second;
        }
    };

    virtual Map<std::string, IVariableLocation*>* GetVariableMap() override { return &variables; }
    virtual Map<std::string, Type*>* GetTypeMap() override { return &types; }

    virtual Map<std::string, std::string*>* GetCompilerVarStringMap() override { return &compilerVarStrings; }
    virtual Map<std::string, int*>* GetCompilerVarIntMap() override { return &compilerVarInts; }

    virtual Type* GetNumConstType() override { return numConstType; }
    virtual void SetNumConstType(Type* type) override { numConstType = type; }
};
