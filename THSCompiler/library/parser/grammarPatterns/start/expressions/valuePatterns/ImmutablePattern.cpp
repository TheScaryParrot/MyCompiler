#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

#include "../ExpressionPattern.cpp"
#include "ConstPattern.cpp"
#include "../../statements/functionCall/FunctionCallPattern.cpp"


class ImmutablePattern : public IGrammarPattern
{
public:
    ImmutablePattern();
    ~ImmutablePattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ImmutablePattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    ConstPattern* constPattern;
    FunctionCallPattern* functionCallPattern;
    ExpressionPattern* expressionPattern; // "( expression )"
};

ImmutablePattern::ImmutablePattern()
{
}

ImmutablePattern::~ImmutablePattern()
{
}

ELookAheadCertainties ImmutablePattern::LookAhead(TokenList* tokens)
{
    if (ConstPattern::LookAhead(tokens) == CertainlyPresent)
    {
        return CertainlyPresent;
    }
    else if (FunctionCallPattern::LookAhead(tokens) == CertainlyPresent)
    {
        return CertainlyPresent;
    }
    else if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN))
    {
        return CertainlyPresent;
    }
    else
    {
        return CertainlyNotPresent;
    }
}

ImmutablePattern* ImmutablePattern::Parse(TokenList* tokens)
{
    ImmutablePattern* immutablePattern = new ImmutablePattern();

    if (ConstPattern::LookAhead(tokens) == CertainlyPresent)
    {
        immutablePattern->constPattern = ConstPattern::Parse(tokens);
        return immutablePattern;
    }
    else if (FunctionCallPattern::LookAhead(tokens) == CertainlyPresent)
    {
        immutablePattern->functionCallPattern = FunctionCallPattern::Parse(tokens);
        return immutablePattern;
    }
    else if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN))
    {
        tokens->Next(); // Consume (
        immutablePattern->expressionPattern = ExpressionPattern::Parse(tokens);
        tokens->Next(); // Consume )
        return immutablePattern;
    }

    delete immutablePattern;
    throw "ImmutablePattern::Parse: Invalid pattern. Did you forget to call LookAhead?";
}