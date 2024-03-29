#pragma once

#include "../../../IGrammarPattern.cpp"

class ConstPattern : public IGrammarPattern
{
public:
    ConstPattern();
    ~ConstPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ConstPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;
};