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

    IVariableLocationGetter* GenerateNumberConst(std::string number);
    IVariableLocationGetter* GenerateStringConst(std::string str);
    IVariableLocationGetter* GenerateLogicConst(bool logic);

} AssemblyGenerator;

AssemblyCode* AssemblyGenerator::GenerateReturnInstruction()
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    return assemblyCode->AddLine(new AssemblyInstructionLine(AssemblyInstructions::RET));
}

AssemblyCode* AssemblyGenerator::GenerateCallInstruction(std::string functionName)
{
    AssemblyInstructionLine* callInstruction = new AssemblyInstructionLine(AssemblyInstructions::CALL);
    callInstruction->AddArgument(functionName);

    AssemblyCode* code = new AssemblyCode();
    return code->AddLine(callInstruction);
}

AssemblyCode* AssemblyGenerator::GenerateLabel(std::string label)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    return assemblyCode->AddLine(new AssemblyLabelLine(label));
}

AssemblyCode* AssemblyGenerator::GenerateJumpToJumpLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    AssemblyInstructionLine* jumpLine = new AssemblyInstructionLine(AssemblyInstructions::JMP);
    jumpLine->AddArgument(jumpLabel->GetName());
    return assemblyCode->AddLine(jumpLine);
}

IVariableLocationGetter* AssemblyGenerator::GenerateNumberConst(std::string number)
{
    // TODO: Return inline variable location getter
    return nullptr;
}

IVariableLocationGetter* AssemblyGenerator::GenerateStringConst(std::string str)
{
    // TODO: Return inline variable location getter
    // This will probably need access to assemblyCode object as it will need to write the string into the data section
    return nullptr;
}

IVariableLocationGetter* AssemblyGenerator::GenerateLogicConst(bool logic)
{
    // TODO: Return inline variable location getter
    return nullptr;
}
