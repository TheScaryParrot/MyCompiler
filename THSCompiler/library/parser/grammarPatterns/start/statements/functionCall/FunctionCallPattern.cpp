#pragma once

#include "../../../IGrammarPattern.cpp"

#include "ParameterListPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class FunctionCallPattern : public IGrammarPattern
{
public:
    FunctionCallPattern();
    ~FunctionCallPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static FunctionCallPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string function;
    ParameterListPattern* parameterListPattern;
};

FunctionCallPattern::FunctionCallPattern()
{
}

FunctionCallPattern::~FunctionCallPattern()
{
    delete parameterListPattern;
}

ELookAheadCertainties FunctionCallPattern::LookAhead(TokenList* tokens)
{
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN))
    {
        return CertainlyNotPresent;
    }

    if (!tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN))
    {
        return CertainlyNotPresent;
    }

    return CertainlyPresent;
}

FunctionCallPattern* FunctionCallPattern::Parse(TokenList* tokens)
{
    FunctionCallPattern* functionCallPattern = new FunctionCallPattern();

    functionCallPattern->function = ((IdentifierToken*)tokens->Next())->GetValue(); // Consume function name

    tokens->Next(); // Consume "("

    functionCallPattern->parameterListPattern = ParameterListPattern::Parse(tokens);

    tokens->Next(); // Consume ")"

    return functionCallPattern;
}
