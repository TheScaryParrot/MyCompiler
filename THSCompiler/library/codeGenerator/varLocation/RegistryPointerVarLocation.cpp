#pragma once

#include "IVariableLocation.cpp"

class RegistryPointerVarLocation : public IVariableLocation
{
   private:
    std::string registry;
    int offset;

   public:
    RegistryPointerVarLocation(std::string registry, int offset)
    {
        this->registry = registry;
        this->offset = offset;
    }

    std::string GetRegistry() { return registry; }
    void SetRegistry(std::string registry) { this->registry = registry; }

    int GetOffset() { return offset; }
    void SetOffset(int offset) { this->offset = offset; }
    /// @brief Adds increment to the offset; increment can be negative
    void IncrementOffset(int increment) { offset += increment; }

    virtual bool IsInline() override { return false; }

    virtual IVariableLocation* Clone() override { return new RegistryPointerVarLocation(registry, offset); }

    virtual std::string ToAssemblyString() override { return "[" + registry + " + " + std::to_string(offset) + "]"; }
};