#pragma once

#include "IVariableLocation.cpp"

class RegistryVarLocation : public IVariableLocation
{
   private:
    std::string registry;
    int offset;

   public:
    RegistryVarLocation(std::string registry, int offset)
    {
        this->registry = registry;
        this->offset = offset;
    }

    virtual std::string GetBase() override { return registry; };
    virtual void SetBase(std::string base) override { registry = base; };

    virtual int GetOffset() override { return offset; };
    virtual void SetOffset(int offset) override { this->offset = offset; };
    /// @brief Adds increment to the offset; increment can be negative
    virtual void IncrementOffset(int increment) override { offset += increment; };

    virtual IVariableLocation* Clone() override { return new RegistryVarLocation(registry, offset); };
};