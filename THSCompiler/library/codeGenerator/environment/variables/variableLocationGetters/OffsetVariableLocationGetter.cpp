#pragma once

#include "IVariableLocationGetter.cpp"

class OffsetVariableLocationGetter : public IVariableLocationGetter
{
   public:
    OffsetVariableLocationGetter(int offset);

    VariableLocation GetLocation(VariableLocation parentLocation) override;

   private:
    int offset;
};

OffsetVariableLocationGetter::OffsetVariableLocationGetter(int offset) { this->offset = offset; }

VariableLocation OffsetVariableLocationGetter::GetLocation(VariableLocation parentLocation)
{
    parentLocation.AddToOffset(offset);
    return parentLocation;
}