#pragma once

#include "../codeGenerator/environment/jumpLabels/JumpLabel.cpp"

#include "AssemblyCode.cpp"
#include "AssemblyLabelLine.cpp"
#include "AssemblyInstructionLine.cpp"
#include "instructions/AssemblyInstructions.cpp"

static class AssemblyGenerator
{
public:
    AssemblyCode* GenerateReturnInstruction();

    AssemblyCode* GenerateLabel(JumpLabel* jumpLabel);
    AssemblyCode* GenerateJumpToLabel(JumpLabel* jumpLabel);

}AssemblyGenerator;

AssemblyCode* AssemblyGenerator::GenerateReturnInstruction()
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    return assemblyCode->AddLine(std::make_shared<AssemblyInstructionLine>(AssemblyInstructions::RET));
}

AssemblyCode* AssemblyGenerator::GenerateLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    return assemblyCode->AddLine(std::make_shared<AssemblyLabelLine>(jumpLabel->GetName()));
}

AssemblyCode* AssemblyGenerator::GenerateJumpToLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    AssemblyInstructionLine* jumpLine = (new AssemblyInstructionLine(AssemblyInstructions::JMP))->AddArgument(jumpLabel->GetName());
    return assemblyCode->AddLine(std::shared_ptr<AssemblyInstructionLine>(jumpLine));
}