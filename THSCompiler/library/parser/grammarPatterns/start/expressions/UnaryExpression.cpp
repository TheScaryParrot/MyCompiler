#pragma once

#include "../../IGrammarPattern.cpp"

#include "operators/UnaryOperator.cpp"
#include "valuePatterns/ValuePattern.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class UnaryExpression : public IGrammarPattern
{
public:
    UnaryExpression();
    ~UnaryExpression();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static UnaryExpression* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    UnaryOperator* unaryOperator;
    ValuePattern* valuePattern;
};

UnaryExpression::UnaryExpression()
{
}

UnaryExpression::~UnaryExpression()
{
    delete unaryOperator;
    delete valuePattern;
}

ELookAheadCertainties UnaryExpression::LookAhead(TokenList* tokens)
{
    if (UnaryOperator::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        return CertainlyPresent;
    }
    
    return ValuePattern::LookAhead(tokens);
}

UnaryExpression* UnaryExpression::Parse(TokenList* tokens)
{
    UnaryExpression* unaryExpression = new UnaryExpression();

    unaryExpression->unaryOperator = UnaryOperator::Parse(tokens);
    unaryExpression->valuePattern = ValuePattern::Parse(tokens);

    return unaryExpression;
}

std::string UnaryExpression::ToString()
{
    return unaryOperator->ToString() + valuePattern->ToString();
}