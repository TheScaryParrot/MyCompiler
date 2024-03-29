#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class UnaryOperator : public IGrammarPattern
{
public:
    UnaryOperator();
    ~UnaryOperator();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static UnaryOperator* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string unaryOperator;
};

UnaryOperator::UnaryOperator()
{
}

UnaryOperator::~UnaryOperator()
{
}

ELookAheadCertainties UnaryOperator::LookAhead(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.NEGATE_OPERATOR_TOKEN) || tokens->IsPeekOfTokenType(ConstTokens.NOT_OPERATOR_TOKEN))
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

UnaryOperator* UnaryOperator::Parse(TokenList* tokens)
{
    UnaryOperator* unaryOperator = new UnaryOperator();

    AbstractToken* token = tokens->Next();

    if (token->IsThisToken(ConstTokens.NEGATE_OPERATOR_TOKEN))
    {
        unaryOperator->unaryOperator = "-";
    }
    else if (token->IsThisToken(ConstTokens.NOT_OPERATOR_TOKEN))
    {
        unaryOperator->unaryOperator = "!";
    }
    else
    {
        delete token;
        delete unaryOperator;
        return nullptr;
    }

    delete token;
    return unaryOperator;
}

std::string UnaryOperator::ToString()
{
    return unaryOperator;
}