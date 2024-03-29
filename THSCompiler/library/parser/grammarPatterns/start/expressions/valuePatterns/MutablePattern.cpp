#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class MutablePattern : public IGrammarPattern
{
public:
    MutablePattern();
    ~MutablePattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static MutablePattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string mutableValue;
};

MutablePattern::MutablePattern()
{
}

MutablePattern::~MutablePattern()
{
}

ELookAheadCertainties MutablePattern::LookAhead(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN))
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

MutablePattern* MutablePattern::Parse(TokenList* tokens)
{
    MutablePattern* mutablePattern = new MutablePattern();

    mutablePattern->mutableValue = ((IdentifierToken*)tokens->Next())->GetValue();

    return mutablePattern;
}

std::string MutablePattern::ToString()
{
    return mutableValue;
}
