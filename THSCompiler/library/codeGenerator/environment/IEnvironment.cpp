#pragma once

#include <string>

#include "../utils/Map.cpp"
#include "../varLocation/IVariableLocation.cpp"

class IEnvironment
{
   public:
    virtual Map<std::string, IVariableLocation*>* GetVariableMap() = 0;
    virtual Map<std::string, Type*>* GetTypeMap() = 0;

    virtual Map<std::string, std::string*>* GetCompilerVarStringMap() = 0;
    virtual Map<std::string, int*>* GetCompilerVarIntMap() = 0;

    virtual Type* GetNumConstType() = 0;
    virtual void SetNumConstType(Type* type) = 0;
};