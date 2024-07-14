#pragma once

#include <string>

#include "../VariableLocation.cpp"
#include "../utils/Map.cpp"

class IEnvironment
{
   public:
    virtual Map<std::string, VariableLocation*>* GetVariableMap() = 0;
    virtual Map<std::string, Type*>* GetTypeMap() = 0;

    virtual Map<std::string, std::string*>* GetCompilerVarStringMap() = 0;
    virtual Map<std::string, int*>* GetCompilerVarIntMap() = 0;
};