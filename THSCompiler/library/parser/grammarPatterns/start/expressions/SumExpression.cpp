#pragma once

#include "../../IGrammarPattern.cpp"

#include "operators/SumOperator.cpp" 
#include "MulExpression.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class SumExpression : public IGrammarPattern
{
public:
    SumExpression();
    ~SumExpression();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static SumExpression* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::vector<MulExpression*> mulExpressions;
};

SumExpression::SumExpression()
{
}

SumExpression::~SumExpression()
{
    for (MulExpression* mulExpression : mulExpressions)
    {
        delete mulExpression;
    }
}

ELookAheadCertainties SumExpression::LookAhead(TokenList* tokens)
{
    return MulExpression::LookAhead(tokens);
}

SumExpression* SumExpression::Parse(TokenList* tokens)
{
    SumExpression* sumExpression = new SumExpression();

    sumExpression->mulExpressions.push_back(MulExpression::Parse(tokens));

    while (SumOperator::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        // Parse the operator
        sumExpression->mulExpressions.push_back(MulExpression::Parse(tokens));
    }

    return sumExpression;
}

std::string SumExpression::ToString()
{
    std::string str = "";

    for (MulExpression* mulExpression : mulExpressions)
    {
        str += mulExpression->ToString() + " SUM_OPERATOR ";
    }

    return str;
}