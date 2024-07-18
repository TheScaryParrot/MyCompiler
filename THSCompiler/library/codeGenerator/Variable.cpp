#pragma once

#include "types/Type.cpp"
#include "varLocation/IVariableLocation.cpp"

class Variable
{
   public:
    Variable(IVariableLocation* location, Type* type, bool isInline, bool isFinal)
    {
        this->location = location;
        this->type = type;
        this->isInline = isInline;
        this->isFinal = isFinal;
    }

    IVariableLocation* location;
    Type* type;
    bool isInline;
    bool isFinal;
};