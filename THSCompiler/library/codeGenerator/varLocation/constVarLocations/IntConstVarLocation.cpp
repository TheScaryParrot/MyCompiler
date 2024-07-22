#pragma once

#include "../../../utils/Logger.cpp"
#include "IConstVarLocation.cpp"

class IntConstVarLocation : public IConstVarLocation
{
   private:
    int value;

   public:
    IntConstVarLocation(int value) { this->value = value; }

    virtual IVariableLocation* Clone() override { return new IntConstVarLocation(value); };

    virtual std::string ToAssemblyString() override { return std::to_string(value); };
};