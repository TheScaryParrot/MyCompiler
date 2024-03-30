#pragma once

#include "../PredictiveParser.hpp"

ELookAheadCertainties PredictiveParser::LookAhead_Line(TokenList* tokens)
{
    if (LookAhead_Declaration(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Statement(tokens);
}

CodeLineNode* PredictiveParser::Parse_Line(TokenList* tokens)
{
    if (LookAhead_Declaration(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        return new CodeLineNode(Parse_Declaration(tokens));
    }
    tokens->Next(); // Consume the token
    return new CodeLineNode(nullptr); // TODO: Implement Statement Node
}