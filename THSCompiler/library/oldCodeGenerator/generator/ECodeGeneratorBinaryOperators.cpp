#pragma once

#include <string>

enum ECodeGeneratorBinaryOperators
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    ASSIGN
};

std::string GetOperationFunctionName(ECodeGeneratorBinaryOperators binaryOperator)
{
    switch (binaryOperator)
    {
        case ADD:
            return "Add";
        case SUB:
            return "Sub";
        case MUL:
            return "Mul";
        case DIV:
            return "Div";
        case MOD:
            return "Mod";
        case ASSIGN:
            return "Assign";
        default:
            return "";
    }
}
