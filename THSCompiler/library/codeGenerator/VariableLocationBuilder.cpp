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

    /// @brief New VariableLocation with base of loc1, type of loc2 and offset of loc1 + loc2; used for relative access
    /// (eg. properties)
    static VariableLocation* CreateVariableLocation(VariableLocation* loc1, VariableLocation* loc2)
    {
        return new VariableLocation(loc1->GetBase(), loc1->GetOffset() + loc2->GetOffset(), loc2->GetType());
    }
} VariableLocationFactory;