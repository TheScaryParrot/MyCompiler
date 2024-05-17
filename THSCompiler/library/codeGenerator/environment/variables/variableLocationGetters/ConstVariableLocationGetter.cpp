#pragma once

#include "IVariableLocationGetter.cpp"

class ConstVariableLocationGetter : public IVariableLocationGetter
{
public:
    ConstVariableLocationGetter(std::string originMemoryLocation, int offset);

    VariableLocation GetLocation(VariableLocation parentLocation) override;

private:
    VariableLocation location;
};

ConstVariableLocationGetter::ConstVariableLocationGetter(std::string originMemoryLocation, int offset)
{
    this->location = VariableLocation(originMemoryLocation, offset);
}

VariableLocation ConstVariableLocationGetter::GetLocation(VariableLocation parentLocation)
{
    return location;
}