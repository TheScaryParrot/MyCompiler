#pragma once

#include "../PredictiveParser.hpp"

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"

ELookAheadCertainties PredictiveParser::LookAhead_Statement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.STATEMENT_END_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_Body(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_Assignment(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_KeywordStatement(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_Call(tokens);
}
void PredictiveParser::Parse_Statement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_Assignment(TokenList* tokens)
{
    if (LookAhead_Mutable(tokens) != ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyNotPresent;

    return LookAhead_AssignOperator(tokens);
}
void PredictiveParser::Parse_Assignment(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_AssignOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.DECREMENT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_ValueAssignOperator(tokens);
}
void PredictiveParser::Parse_AssignOperator(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ValueAssignOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.MOD_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_ValueAssignOperator(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_KeywordStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.IF_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.RETURN_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.WHILE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.FOR_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.BREAK_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.CONTINUE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_KeywordStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_IfStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.IF_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_IfStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ElifStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.ELIF_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_ElifStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ElseStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.ELSE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_ElseStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ReturnStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.RETURN_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_ReturnStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_WhileStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.WHILE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_WhileStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ForStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.FOR_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_ForStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_BreakStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.BREAK_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_BreakStatement(TokenList* tokens /*, Node*/)
{
}

ELookAheadCertainties PredictiveParser::LookAhead_ContinueStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.CONTINUE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_ContinueStatement(TokenList* tokens /*, Node*/)
{
}

