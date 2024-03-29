#pragma once

#include "../../IGrammarPattern.cpp"

#include "OrExpression.cpp"

class ExpressionPattern : public IGrammarPattern
{
public:
    ExpressionPattern();
    ~ExpressionPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ExpressionPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    OrExpression* orExpression;
};

ExpressionPattern::ExpressionPattern()
{
}

ExpressionPattern::~ExpressionPattern()
{
    delete orExpression;
}

ELookAheadCertainties ExpressionPattern::LookAhead(TokenList* tokens)
{
    return OrExpression::LookAhead(tokens);
}

ExpressionPattern* ExpressionPattern::Parse(TokenList* tokens)
{
    ExpressionPattern* expressionPattern = new ExpressionPattern();
    expressionPattern->orExpression = OrExpression::Parse(tokens);
    return expressionPattern;
}

std::string ExpressionPattern::ToString()
{
    return "Expression: " + orExpression->ToString();
}