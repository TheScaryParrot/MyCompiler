#pragma once

#include "AbstractStatement.cpp"

class IfStatement : public AbstractStatement
{
public:
    IfStatement();
    ~IfStatement();

    std::string GetCompiledString(std::vector<std::string> arguments) override;
};

IfStatement::IfStatement() : AbstractStatement("if")
{
}

IfStatement::~IfStatement()
{
}

std::string IfStatement::GetCompiledString(std::vector<std::string> arguments)
{
    if (arguments.size() < 2)
    {
        throw "If statement requires at least 2 arguments";
    }

    if (arguments[0] != "(") {throw "If statement requires ( at the beginning";}

    std::string compare1 = arguments[1];

    if (arguments[2] == ")")
    {
        // CONTINUE HERE
    }
}
