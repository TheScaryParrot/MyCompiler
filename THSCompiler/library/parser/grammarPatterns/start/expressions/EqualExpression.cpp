#pragma once

#include "../../IGrammarPattern.cpp"

#include "SumExpression.cpp"
#include "operators/EqualOperator.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class EqualExpression : public IGrammarPattern
{
public:
    EqualExpression();
    ~EqualExpression();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static EqualExpression* Parse(TokenList* tokens);

    virtual std::string ToString() override;
private:
    std::vector<SumExpression*> sumExpressions;
};

EqualExpression::EqualExpression()
{
}

EqualExpression::~EqualExpression()
{
    for (SumExpression* sumExpression : sumExpressions)
    {
        delete sumExpression;
    }
}

ELookAheadCertainties EqualExpression::LookAhead(TokenList* tokens)
{
    return SumExpression::LookAhead(tokens);
}

EqualExpression* EqualExpression::Parse(TokenList* tokens)
{
    EqualExpression* equalExpression = new EqualExpression();

    equalExpression->sumExpressions.push_back(SumExpression::Parse(tokens));

    while (EqualOperator::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        // IMPLEMENT THE EQUAL OPERATOR PATTERN
        equalExpression->sumExpressions.push_back(SumExpression::Parse(tokens));
    }

    return equalExpression;
}

std::string EqualExpression::ToString()
{
    std::string str = "";

    for (SumExpression* sumExpression : sumExpressions)
    {
        str += sumExpression->ToString() + " EQUAL_OPERATOR ";
    }

    return str;
}
