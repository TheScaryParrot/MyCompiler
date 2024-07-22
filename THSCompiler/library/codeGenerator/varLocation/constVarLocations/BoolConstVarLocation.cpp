#pragma once

#include "../../../utils/Logger.cpp"
#include "IConstVarLocation.cpp"

class BoolConstVarLocation : public IConstVarLocation
{
   private:
    bool value;

   public:
    BoolConstVarLocation(bool value) { this->value = value; }

    virtual IVariableLocation* Clone() override { return new BoolConstVarLocation(value); };

    virtual std::string ToAssemblyString() override { return std::to_string(value); };
};