#pragma once

#include <string>

class AssemblyInstruction
{
public:
    AssemblyInstruction() = default;
    AssemblyInstruction(std::string instruction);
    std::string ToString();

private:
    std::string instruction;
};

AssemblyInstruction::AssemblyInstruction(std::string instruction)
{
    this->instruction = instruction;
}

std::string AssemblyInstruction::ToString()
{
    return instruction;
}