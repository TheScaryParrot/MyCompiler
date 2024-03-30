#pragma once

#include "../PredictiveParser.hpp"

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"

ELookAheadCertainties PredictiveParser::LookAhead_Expression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
void PredictiveParser::Parse_Expression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_OrExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
void PredictiveParser::Parse_OrExpression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_AndExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
void PredictiveParser::Parse_AndExpression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_EqualExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
void PredictiveParser::Parse_EqualExpression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_EqualOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_EqualOperator(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_SumExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
void PredictiveParser::Parse_SumExpression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_SumOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.ADD_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.SUB_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_SumOperator(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_MulExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
void PredictiveParser::Parse_MulExpression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_MulOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.MUL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.DIV_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.MOD_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_MulOperator(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_UnaryExpression(TokenList* tokens)
{
    // <unaryOperator> | <value>
    if (LookAhead_UnaryOperator(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Value(tokens);
}
void PredictiveParser::Parse_UnaryExpression(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_UnaryOperator(TokenList* tokens)
{
    // NEGATE | NOT
    if (tokens->IsPeekOfTokenType(ConstTokens.NEGATE_OPERATOR_TOKEN) || tokens->IsPeekOfTokenType(ConstTokens.NOT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_UnaryOperator(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Value(TokenList* tokens)
{
    // <mutable> | <immutable>
    if (LookAhead_Mutable(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Immutable(tokens);
}
void PredictiveParser::Parse_Value(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Mutable(TokenList* tokens)
{
    // ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_Mutable(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Immutable(TokenList* tokens)
{
    // INT | FLOAT | STRING | BOOL
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_Call(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Constant(tokens);
}
void PredictiveParser::Parse_Immutable(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Call(TokenList* tokens)
{
    // ID (
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN)) return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, 1)) return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
void PredictiveParser::Parse_Call(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Constant(TokenList* tokens)
{
    // INT | STRING | <logicalConst>
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_NUMBER_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_STRING_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_LogicalConstant(tokens);
}
void PredictiveParser::Parse_Constant(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_LogicalConstant(TokenList* tokens)
{
    // TRUE | FALSE
    if (tokens->IsPeekOfTokenType(Keywords.LOGICAL_TRUE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.LOGICAL_FALSE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_LogicalConstant(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Arguments(TokenList* tokens)
{
    // <expression>? (SEPERATOR <expression>)* can be empty, therefore always unknown
    return ELookAheadCertainties::Unknown;
}
void PredictiveParser::Parse_Arguments(TokenList* tokens /*, Node*/)
{
}

