#pragma once

#include <string>
#include <vector>

#include "../codeGenerator/environment/funcVars/variables/VariableLocation.cpp"
#include "IAssemblyLine.cpp"
#include "instructions/AssemblyInstruction.cpp"

class AssemblyInstructionLine : public IAssemblyLine
{
   public:
    AssemblyInstructionLine(AssemblyInstruction instruction);

    AssemblyInstructionLine* AddArgument(std::string argument);

    virtual std::string ToString() override;

   private:
    AssemblyInstruction instruction;
    std::vector<std::string> arguments;
};

AssemblyInstructionLine::AssemblyInstructionLine(AssemblyInstruction instruction) { this->instruction = instruction; }

AssemblyInstructionLine* AssemblyInstructionLine::AddArgument(std::string argument)
{
    arguments.push_back(argument);
    return this;
}

std::string AssemblyInstructionLine::ToString()
{
    std::string result = instruction.ToString() + " ";

    if (arguments.size() <= 0) return result;

    result += arguments.front();

    for (size_t i = 1; i < arguments.size(); i++)
    {
        result += ", " + arguments[i];
    }

    return result;
}