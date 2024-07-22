#pragma once

#include "../../../utils/Logger.cpp"
#include "IConstVarLocation.cpp"

class FloatConstVarLocation : public IConstVarLocation
{
   private:
    float value;

   public:
    FloatConstVarLocation(float value) { this->value = value; }

    virtual IVariableLocation* Clone() override { return new FloatConstVarLocation(value); };

    virtual std::string ToAssemblyString() override { return std::to_string(value); };
};