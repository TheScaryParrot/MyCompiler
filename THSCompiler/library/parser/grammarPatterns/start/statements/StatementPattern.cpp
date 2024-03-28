#pragma once

#include "../../IGrammarPattern.cpp"

class StatementPattern : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static StatementPattern* Parse(TokenList* tokens);
};

ELookAheadCertainties StatementPattern::LookAhead(TokenList* tokens)
{
    return ELookAheadCertainties::CertainlyNotPresent;
}

StatementPattern* StatementPattern::Parse(TokenList* tokens)
{
    return nullptr;
}