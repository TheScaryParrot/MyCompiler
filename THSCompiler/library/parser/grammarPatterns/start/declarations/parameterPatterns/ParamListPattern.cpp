#pragma once

#include "../../../IGrammarPattern.cpp"
#include "ParamDeclaration.cpp"

class ParamListPattern : public IGrammarPattern
{
public:
    ParamListPattern();
    ~ParamListPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ParamListPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::vector<ParamDeclaration*> paramDeclarations;
};

ParamListPattern::ParamListPattern()
{
}

ParamListPattern::~ParamListPattern()
{
    for (ParamDeclaration* paramDeclaration : paramDeclarations)
    {
        delete paramDeclaration;
    }
}

ELookAheadCertainties ParamListPattern::LookAhead(TokenList* tokens)
{
    throw "ParamList can have zero parameters, so it is kindof always present";
}

ParamListPattern* ParamListPattern::Parse(TokenList* tokens)
{
    ParamListPattern* paramListPattern = new ParamListPattern();

    if (ParamDeclaration::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        paramListPattern->paramDeclarations.push_back(ParamDeclaration::Parse(tokens));

        while (tokens->IsPeekOfTokenType(ConstTokens.SEPERATOR_TOKEN))
        {
            tokens->Next(); // Consume SEPERATOR_TOKEN

            paramListPattern->paramDeclarations.push_back(ParamDeclaration::Parse(tokens));
        }
    }

    return paramListPattern;
}

std::string ParamListPattern::ToString()
{
    std::string result = "ParamList: { ";

    for (ParamDeclaration* paramDeclaration : paramDeclarations)
    {
        result += paramDeclaration->ToString() + ", ";
    }

    result += " }";

    return result;
}