#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>

class StatementPattern : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static StatementPattern* Parse(TokenList* tokens);
};