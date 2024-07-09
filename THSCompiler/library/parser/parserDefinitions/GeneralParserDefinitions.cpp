#pragma once

#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_Line(TokenList* tokens)
{
    return LookAhead_Declaration(tokens) || LookAhead_Statement(tokens);
}

AbstractLineNode* PredictiveParser::Parse_Line(TokenList* tokens)
{
    if (LookAhead_Declaration(tokens))
    {
        return Parse_Declaration(tokens);
    }

    return Parse_Statement(tokens);
}