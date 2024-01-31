#pragma once

#include <iostream>
#include <string>

#include "Helper.cpp"

class CustomInstructonBase
{
private:
    std::string instructionName;
    unsigned int argumentCount;

public:
    CustomInstructonBase(std::string instructionName, unsigned int argumentCount);

    virtual std::string GetAssemblyCode(unsigned int line, std::string precedingSpaces, std::vector<std::string> arguments, std::string comment);

    bool CheckValidUsage(unsigned int line, std::vector<std::string> arguments, std::string comment);

    bool IsLineCustomInstruction(std::string line);
};