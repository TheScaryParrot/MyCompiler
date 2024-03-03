#pragma once

#include <string>
#include <vector>

class CodeLine {
public:
    CodeLine(std::string instruction, std::vector<std::string> arguments);
    ~CodeLine();
    
    std::string ToString();

    std::string instruction;
    std::vector<std::string> arguments;
};

CodeLine::CodeLine(std::string instruction, std::vector<std::string> arguments)
{
    this->instruction = instruction;
    this->arguments = arguments;
}

CodeLine::~CodeLine()
{
}

std::string CodeLine::ToString()
{
    std::string result = instruction;

    for (std::string argument : arguments)
    {
        result += " " + argument;
    }

    return result;
}