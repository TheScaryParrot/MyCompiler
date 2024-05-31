#pragma once

#include "IFunctionCallCode.cpp"

class InlineFunctionCallCode : public IFunctionCallCode
{
public:
    InlineFunctionCallCode(AssemblyCode* functionCode);

    virtual AssemblyCode* GenerateFunctionCallCode() override;

private:
    AssemblyCode* functionCode;
};

InlineFunctionCallCode::InlineFunctionCallCode(AssemblyCode* functionCode)
{
    this->functionCode = functionCode;
}

AssemblyCode* InlineFunctionCallCode::GenerateFunctionCallCode()
{
    return functionCode;
}