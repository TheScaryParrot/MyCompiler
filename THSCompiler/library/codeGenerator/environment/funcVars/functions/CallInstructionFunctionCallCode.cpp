#pragma once

#include "../../../../assembly/AssemblyGenerator.cpp"
#include "IFunctionCallCode.cpp"

class CallInstructionFunctionCallCode : public IFunctionCallCode
{
   public:
    CallInstructionFunctionCallCode(std::string functionName);

    virtual AssemblyCode* GenerateFunctionCallCode() override;

   private:
    std::string functionName;
};

CallInstructionFunctionCallCode::CallInstructionFunctionCallCode(std::string functionName)
{
    this->functionName = functionName;
}

AssemblyCode* CallInstructionFunctionCallCode::GenerateFunctionCallCode()
{
    return AssemblyGenerator.GenerateCallInstruction(functionName);
}
