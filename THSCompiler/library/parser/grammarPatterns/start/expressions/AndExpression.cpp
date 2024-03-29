#pragma once

#include "../../IGrammarPattern.cpp"

#include "EqualExpression.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class AndExpression : public IGrammarPattern
{
public:
    AndExpression();
    ~AndExpression();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static AndExpression* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::vector<EqualExpression*> equalExpressions;
};

AndExpression::AndExpression()
{
}

AndExpression::~AndExpression()
{
    for (EqualExpression* equalExpression : equalExpressions)
    {
        delete equalExpression;
    }
}

ELookAheadCertainties AndExpression::LookAhead(TokenList* tokens)
{
    return EqualExpression::LookAhead(tokens);
}

AndExpression* AndExpression::Parse(TokenList* tokens)
{
    AndExpression* andExpression = new AndExpression();

    andExpression->equalExpressions.push_back(EqualExpression::Parse(tokens));

    while (tokens->IsPeekOfTokenType(ConstTokens.AND_OPERATOR_TOKEN))
    {
        tokens->Next(); // Consume AND_TOKEN
        andExpression->equalExpressions.push_back(EqualExpression::Parse(tokens));
    }

    return andExpression;
}

std::string AndExpression::ToString()
{
    std::string result = "";

    for (EqualExpression* equalExpression : equalExpressions)
    {
        result += equalExpression->ToString() + " && ";
    }

    return result;
}
