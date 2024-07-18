#pragma once

#include <string>

class IVariableLocation
{
   public:
    virtual bool IsInline() = 0;

    virtual IVariableLocation* Clone() = 0;

    virtual std::string ToAssemblyString() = 0;
};