#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "../../../assembly/instructions/AssemblyInstructions.cpp"
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
    AssemblyCode* code = new AssemblyCode();

    AssemblyInstructionLine* callInstruction =
        (new AssemblyInstructionLine(AssemblyInstructions::CALL))->AddArgument(functionName);

    code->AddLine(std::shared_ptr<AssemblyInstructionLine>(callInstruction));

    return code;
}
