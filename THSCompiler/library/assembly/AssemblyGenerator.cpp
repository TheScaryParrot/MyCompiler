#pragma once

#include "../codeGenerator/environment/funcVars/variables/Variable.cpp"
#include "../codeGenerator/environment/jumpLabels/JumpLabel.cpp"
#include "AssemblyCode.cpp"
#include "AssemblyInstructionLine.cpp"
#include "AssemblyLabelLine.cpp"
#include "instructions/AssemblyInstructions.cpp"

static class AssemblyGenerator
{
   public:
    AssemblyCode* GenerateReturnInstruction();
    AssemblyCode* GenerateCallInstruction(std::string functionName);

    /// @brief Code to generate a label; label can be JumpLabel, functionLabel or any other label
    AssemblyCode* GenerateLabel(std::string label);

    AssemblyCode* GenerateJumpToJumpLabel(JumpLabel* jumpLabel);

    const std::string LABEL_MANGLING_TOKEN = "-";

} AssemblyGenerator;

AssemblyCode* AssemblyGenerator::GenerateReturnInstruction()
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    return assemblyCode->AddLine(std::make_shared<AssemblyInstructionLine>(AssemblyInstructions::RET));
}

AssemblyCode* AssemblyGenerator::GenerateCallInstruction(std::string functionName)
{
    AssemblyInstructionLine* callInstruction = new AssemblyInstructionLine(AssemblyInstructions::CALL);
    callInstruction->AddArgument(functionName);

    AssemblyCode* code = new AssemblyCode();
    return code->AddLine(std::shared_ptr<AssemblyInstructionLine>(callInstruction));
}

AssemblyCode* AssemblyGenerator::GenerateLabel(std::string label)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    return assemblyCode->AddLine(std::make_shared<AssemblyLabelLine>(label));
}

AssemblyCode* AssemblyGenerator::GenerateJumpToJumpLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    AssemblyInstructionLine* jumpLine =
        (new AssemblyInstructionLine(AssemblyInstructions::JMP))->AddArgument(jumpLabel->GetName());
    return assemblyCode->AddLine(std::shared_ptr<AssemblyInstructionLine>(jumpLine));
}