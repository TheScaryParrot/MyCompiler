#pragma once

#include "../../../IGrammarPattern.cpp"
#include "../../../../../tokens/Keywords.cpp"
#include "../../../../../tokens/ConstTokens.cpp"

class TypePattern : public IGrammarPattern
{
public:
    TypePattern();
    ~TypePattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static TypePattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

    std::string type;
};

TypePattern::TypePattern()
{
}

TypePattern::~TypePattern()
{
}

ELookAheadCertainties TypePattern::LookAhead(TokenList* tokens)
{
    AbstractToken* peekToken = tokens->Peek();

    if (peekToken->IsThisToken(Keywords.VOID_KEYWORD))
    {
        delete peekToken;
        return ELookAheadCertainties::CertainlyPresent;
    }

    if (peekToken->IsThisToken(ConstTokens.CONST_IDENTIFIER_TOKEN))
    {
        delete peekToken;
        return ELookAheadCertainties::Unknown; // We don't know if this is a type or not, could be a variable name
    }

    delete peekToken;
    return ELookAheadCertainties::CertainlyNotPresent;
}