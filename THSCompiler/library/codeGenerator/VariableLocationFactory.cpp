#pragma once

#include "VariableLocation.cpp"

static class VariableLocationFactory
{
   public:
    static VariableLocation* CreateVariableLocation(std::string base, int offset, Type* type)
    {
        return new VariableLocation(base, offset, type);
    }

    static VariableLocation* CreateVariableLocation(std::string base, Type* type)
    {
        return new VariableLocation(base, 0, type);
    }

    static VariableLocation* CreateVariableLocation(int offset, Type* type)
    {
        return new VariableLocation("", offset, type);
    }

    static VariableLocation* CreateVariableLocation(Type* type) { return new VariableLocation("", 0, type); }

    /// @brief New VariableLocation with base of owner, type of property and offset of owner + property; used for
    /// relative access (eg. properties)
    static VariableLocation* CreateRelativeVariableLocation(VariableLocation* owner, VariableLocation* property)
    {
        return new VariableLocation(owner->GetBase(), owner->GetOffset() + property->GetOffset(), property->GetType());
    }
} VariableLocationFactory;