#pragma once

#include "../PredictiveParser.hpp"

ELookAheadCertainties PredictiveParser::LookAhead_Line(TokenList* tokens)
{
    if (LookAhead_Declaration(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Statement(tokens);
}

AbstractLineNode* PredictiveParser::Parse_Line(TokenList* tokens)
{
    if (LookAhead_Declaration(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        return Parse_Declaration(tokens);
    }
    
    tokens->Next(); // Consume the token
    return nullptr; // TODO: Implement Statement Node
}