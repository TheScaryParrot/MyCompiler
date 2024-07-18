#pragma once

#include <string>

class IVariableLocation
{
   public:
    virtual std::string GetBase() = 0;
    virtual void SetBase(std::string base) = 0;

    virtual int GetOffset() = 0;
    virtual void SetOffset(int offset) = 0;
    /// @brief Adds increment to the offset; increment can be negative
    virtual void IncrementOffset(int increment) = 0;

    virtual IVariableLocation* Clone() = 0;
};