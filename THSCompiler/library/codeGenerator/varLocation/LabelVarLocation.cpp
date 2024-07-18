#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class LabelVarLocation : public IVariableLocation
{
   private:
    std::string label;

   public:
    LabelVarLocation(std::string label) { this->label = label; }

    virtual bool IsInline() override { return false; }

    virtual IVariableLocation* Clone() override { return new LabelVarLocation(label); }

    virtual std::string ToAssemblyString() override { return label; }
};