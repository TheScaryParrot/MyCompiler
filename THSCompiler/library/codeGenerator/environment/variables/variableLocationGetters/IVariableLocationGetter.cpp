#pragma once

#include "VariableLocation.cpp"

class IVariableLocationGetter
{
public:
    virtual VariableLocation GetLocation(VariableLocation parentLocation) = 0;
};