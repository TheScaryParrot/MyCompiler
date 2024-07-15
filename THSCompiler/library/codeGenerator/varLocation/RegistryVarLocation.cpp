#pragma once

#include "IVariableLocation.cpp"

class RegistryVarLocation : public IVariableLocation
{
   private:
    std::string registry;
    int offset;
    Type* type;

   public:
    RegistryVarLocation(std::string registry, int offset, Type* type)
    {
        this->registry = registry;
        this->offset = offset;
        this->type = type;
    }

    virtual std::string GetBase() override { return registry; };
    virtual void SetBase(std::string base) override { registry = base; };

    virtual int GetOffset() override { return offset; };
    virtual void SetOffset(int offset) override { this->offset = offset; };
    /// @brief Adds increment to the offset; increment can be negative
    virtual void IncrementOffset(int increment) override { offset += increment; };

    virtual Type* GetType() override { return type; };
    virtual void SetType(Type* type) override { this->type = type; };

    virtual IVariableLocation* Copy() override { return new RegistryVarLocation(registry, offset, type); };
    virtual IVariableLocation* ConstructionFromRelAccessBase(IVariableLocation* base) override { return this; };
};