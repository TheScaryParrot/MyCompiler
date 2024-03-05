#pragma once

#include <vector>
#include <string>

class AbstractStatement  
{
public:
    AbstractStatement(std::string instruction);
    ~AbstractStatement();

    bool IsMatch(std::string instruction);

    virtual std::string GetCompiledString(std::vector<std::string> arguments);

private:
    std::string instruction;
};

AbstractStatement::AbstractStatement(std::string instruction)
{
    this->instruction = instruction;
}

AbstractStatement::~AbstractStatement()
{
}

std::string AbstractStatement::GetCompiledString(std::vector<std::string> arguments)
{
    throw "GetCompiledString not implemented";
}

bool AbstractStatement::IsMatch(std::string instruction)
{
    return this->instruction == instruction;
}
