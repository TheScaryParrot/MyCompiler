#pragma once

#include <string>
#include <vector>

class CodeLine {
public:
    CodeLine(int lineNumber);
    CodeLine(std::string instruction, std::vector<std::string> arguments, int lineNumber);
    ~CodeLine();
    
    void AddString(std::string string);
    
    std::string ToString();

    bool IsEmpty() {return instruction == "" && arguments.size() == 0;}

    std::string instruction;
    std::vector<std::string> arguments;

    int lineNumber;
};

CodeLine::CodeLine(int lineNumber)
{
    this->lineNumber = lineNumber;
}

CodeLine::CodeLine(std::string instruction, std::vector<std::string> arguments, int lineNumber)
{
    this->instruction = instruction;
    this->arguments = arguments;
    this->lineNumber = lineNumber;
}

CodeLine::~CodeLine()
{
}

void CodeLine::AddString(std::string string)
{
    if (string == "") return;

    if (instruction == "")
    {
        instruction = string;
        return;
    }
    
    arguments.push_back(string);
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

