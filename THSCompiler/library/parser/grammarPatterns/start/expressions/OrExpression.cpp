#pragma once

#include "../../IGrammarPattern.cpp"

#include "AndExpression.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class OrExpression : public IGrammarPattern
{
public:
    OrExpression();
    ~OrExpression();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static OrExpression* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::vector<AndExpression*> andExpressions;
};

OrExpression::OrExpression()
{
}

OrExpression::~OrExpression()
{
    for (AndExpression* andExpression : andExpressions)
    {
        delete andExpression;
    }
}

ELookAheadCertainties OrExpression::LookAhead(TokenList* tokens)
{
    return AndExpression::LookAhead(tokens);
}

OrExpression* OrExpression::Parse(TokenList* tokens)
{
    OrExpression* orExpression = new OrExpression();

    orExpression->andExpressions.push_back(AndExpression::Parse(tokens));

    while (tokens->IsPeekOfTokenType(ConstTokens.OR_OPERATOR_TOKEN))
    {
        tokens->Next(); // Consume OR_TOKEN
        orExpression->andExpressions.push_back(AndExpression::Parse(tokens));
    }

    return orExpression;
}

std::string OrExpression::ToString()
{
    std::string result = "";

    for (AndExpression* andExpression : andExpressions)
    {
        result += andExpression->ToString() + " || ";
    }

    return result.substr(0, result.size() - 4);
}