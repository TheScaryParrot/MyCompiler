#pragma once

#include "../../../assembly/AssemblyCode.cpp"

/// @brief Interface for generating function call code
class IFunctionCallCode
{
public:
    virtual AssemblyCode* GenerateFunctionCallCode() = 0;
};