#pragma once

#include "types/Type.cpp"
#include "varLocation/IVariableLocation.cpp"

class Variable
{
   public:
    Variable(IVariableLocation* location, Type* type, bool isFinal)
    {
        this->location = location;
        this->type = type;
        this->isFinal = isFinal;
    }

    IVariableLocation* location;
    Type* type;
    bool isFinal;

    bool IsInline() { return location->IsInline(); }
};