#pragma once

#include "../../../utils/Logger.cpp"
#include "../IVariableLocation.cpp"

class BoolConstVarLocation : public IVariableLocation
{
   private:
    bool value;

   public:
    BoolConstVarLocation(bool value) { this->value = value; }

    virtual bool IsInline() { return true; };

    virtual IVariableLocation* Clone() { return new BoolConstVarLocation(value); };

    virtual std::string ToAssemblyString() { return std::to_string(value); };
};