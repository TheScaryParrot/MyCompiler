#pragma once

#include <map>

#include "../InputFile.cpp"
#include "AbstractStatement.cpp"

// This is a map of jump operators to their corresponding assembly operators, they are inverted because it jumps if condition is not met
std::map<std::string, std::string> JUMP_OPERATORS = {
    {"==", "jne"},
    {"!=", "je"},
    {"<", "jge"},
    {">", "jle"},
    {"<=", "jg"},
    {">=", "jl"}
};

class IfStatement : public AbstractStatement
{
public:
    IfStatement();
    ~IfStatement();

    std::string GetCompiledString(std::vector<std::string> arguments) override;

private:
    std::string CompileBody();
};

IfStatement::IfStatement() : AbstractStatement("if")
{
}

IfStatement::~IfStatement()
{
}

std::string IfStatement::GetCompiledString(std::vector<std::string> arguments)
{
    if (arguments[0] != "(") {return "If statement requires ( at the beginning. Now it is: " + arguments[0];}

    std::string compare1 = arguments[1];
    std::string jumpOperator = "";
    std::string compare2 = "";

    if (arguments[2] == ")")
    {
        jumpOperator = JUMP_OPERATORS["=="];
        compare2 = "1";
    }
    else
    {
        jumpOperator = JUMP_OPERATORS[arguments[2]];
        compare2 = arguments[3];

        if (arguments[4] != ")") {return "If statement requires ) at the end. Now it is: " + arguments[4];}
    }

    if (arguments[arguments.size() - 1] != "{") {return "If statement requires { at the end. Now it is: " + arguments[arguments.size() - 1];}

    // Compile the body of the if statement, but this requires cirucular dependency, so AAAAAAAHH

    return "cmp " + compare1 + ", " + compare2 + "\n" + jumpOperator + " else";
}
