#pragma once

#include "../../../utils/Logger.cpp"
#include "../IVariableLocation.cpp"

class FloatConstVarLocation : public IVariableLocation
{
   private:
    float value;

   public:
    FloatConstVarLocation(float value) { this->value = value; }

    virtual bool IsInline() { return true; };

    virtual IVariableLocation* Clone() { return new FloatConstVarLocation(value); };

    virtual std::string ToAssemblyString() { return std::to_string(value); };
};