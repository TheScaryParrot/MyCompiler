#pragma once

#include <string>

#include "../Type.cpp"

class IVariableLocation
{
   public:
    virtual std::string GetBase() = 0;
    virtual void SetBase(std::string base) = 0;

    virtual int GetOffset() = 0;
    virtual void SetOffset(int offset) = 0;
    /// @brief Adds increment to the offset; increment can be negative
    virtual void IncrementOffset(int increment) = 0;

    virtual Type* GetType() = 0;
    virtual void SetType(Type* type) = 0;

    virtual IVariableLocation* Copy() = 0;
    /// @brief Construct var location from a base for a relative access (eg. properties)
    virtual IVariableLocation* ConstructionFromRelAccessBase(IVariableLocation* base) = 0;
};