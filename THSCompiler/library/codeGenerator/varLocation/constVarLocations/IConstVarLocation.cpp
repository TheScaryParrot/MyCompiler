#pragma once

#include "../IVariableLocation.cpp"

class IConstVarLocation : public IVariableLocation
{
    virtual bool IsInline() override { return true; };
};