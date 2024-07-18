#pragma once

#include "../../utils/Logger.cpp"
#include "IVariableLocation.cpp"

class LabelVarLocation : public IVariableLocation
{
   private:
    std::string base;

   public:
    LabelVarLocation(std::string base) { this->base = base; }

    virtual std::string GetBase() { return base; }
    virtual void SetBase(std::string base) { this->base = base; }

    virtual int GetOffset()
    {
        Logger.Log("LabelVarLocation does not have offset", Logger.ERROR);
        return 0;
    }
    virtual void SetOffset(int offset) { Logger.Log("LabelVarLocation does not have offset", Logger.ERROR); }
    /// @brief Adds increment to the offset; increment can be negative
    virtual void IncrementOffset(int increment) { Logger.Log("LabelVarLocation does not have offset", Logger.ERROR); }

    virtual IVariableLocation* Clone() { return new LabelVarLocation(base); }
};