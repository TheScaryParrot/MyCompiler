#include "CustomInstructionBase.hpp"

CustomInstructonBase::CustomInstructonBase(std::string instructionName, unsigned int argumentCount)
{
    this->instructionName = instructionName;
    this->argumentCount = argumentCount;
}

std::string CustomInstructonBase::GetAssemblyCode(unsigned int line, std::string precedingSpaces, std::vector<std::string> arguments, std::string comment)
{
    return precedingSpaces + "HiIIIIIII";
}

bool CustomInstructonBase::CheckValidUsage(unsigned int line, std::vector<std::string> arguments, std::string comment)
{
    if (arguments.size() != this->argumentCount)
    {
        std::cout << "Invalid argument count for instruction " << this->instructionName << " in line " + std::to_string(line) + "\n";
        return false;
    }

    return true;
}

bool CustomInstructonBase::IsLineCustomInstruction(std::string line)
{
    return GetInstructionName(line) == this->instructionName;
}