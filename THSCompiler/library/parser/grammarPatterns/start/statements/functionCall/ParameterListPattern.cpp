#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class ParameterListPattern : public IGrammarPattern
{
public:
    ParameterListPattern();
    ~ParameterListPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ParameterListPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;
};