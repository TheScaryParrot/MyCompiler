#pragma once

#include "IFunctionCallCode.cpp"
#include "../../assembly/AssemblyInstructionLine.cpp"
#include "../../assembly/instructions/AssemblyInstructions.cpp"

class CallInstructionFuncionCallCode : public IFunctionCallCode
{
public:
    CallInstructionFuncionCallCode(std::string functionName);

    virtual AssemblyCode* GenerateFunctionCallCode() override;

private:
    std::string functionName;
};

CallInstructionFuncionCallCode::CallInstructionFuncionCallCode(std::string functionName)
{
    this->functionName = functionName;
}

AssemblyCode* CallInstructionFuncionCallCode::GenerateFunctionCallCode()
{
    AssemblyCode* code = new AssemblyCode();

    AssemblyInstructionLine* callInstruction = (new AssemblyInstructionLine(AssemblyInstructions::CALL))->AddArgument(functionName);

    code->AddLine(std::shared_ptr<AssemblyInstructionLine>(callInstruction));

    return code;
}

