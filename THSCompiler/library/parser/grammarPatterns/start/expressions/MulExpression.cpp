#pragma once

#include "../../IGrammarPattern.cpp"

#include "operators/MulOperator.cpp"
#include "UnaryExpression.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class MulExpression : public IGrammarPattern
{
public:
    MulExpression();
    ~MulExpression();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static MulExpression* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::vector<UnaryExpression*> unaryExpressions;
};

MulExpression::MulExpression()
{
}

MulExpression::~MulExpression()
{
    for (UnaryExpression* unaryExpression : unaryExpressions)
    {
        delete unaryExpression;
    }
}

ELookAheadCertainties MulExpression::LookAhead(TokenList* tokens)
{
    return UnaryExpression::LookAhead(tokens);
}

MulExpression* MulExpression::Parse(TokenList* tokens)
{
    MulExpression* mulExpression = new MulExpression();

    mulExpression->unaryExpressions.push_back(UnaryExpression::Parse(tokens));

    while (MulOperator::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        // Parse the operator
        mulExpression->unaryExpressions.push_back(UnaryExpression::Parse(tokens));
    }

    return mulExpression;
}

std::string MulExpression::ToString()
{
    std::string str = "";
    for (UnaryExpression* unaryExpression : unaryExpressions)
    {
        str += unaryExpression->ToString() + " MUL_EXPRESSION ";
    }
    return str;
}