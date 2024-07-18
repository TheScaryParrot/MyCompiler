#pragma once

#include "../../../utils/Logger.cpp"
#include "../IVariableLocation.cpp"

class IntConstVarLocation : public IVariableLocation
{
   private:
    int value;

   public:
    IntConstVarLocation(int value) { this->value = value; }

    virtual bool IsInline() { return true; };

    virtual IVariableLocation* Clone() { return new IntConstVarLocation(value); };

    virtual std::string ToAssemblyString() { return std::to_string(value); };
};