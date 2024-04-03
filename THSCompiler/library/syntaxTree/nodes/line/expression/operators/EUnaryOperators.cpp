#pragma once

enum EUnaryOperators
{
    NEGATE,
    NOT
};

std::string EUnaryOperatorsToString(EUnaryOperators unaryOperator)
{
    switch(unaryOperator)
    {
        case NEGATE: return "-";
        case NOT: return "!";
    }

    throw "Couldn't convert EUnaryOperators to String in EUnaryOperatorsToString(). Did you forget to update EUnaryOperatorsToString()";
}