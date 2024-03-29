#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class EqualOperator : public IGrammarPattern
{
public:
    EqualOperator();
    ~EqualOperator();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static EqualOperator* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string operatorSymbol;
};

EqualOperator::EqualOperator()
{
}

EqualOperator::~EqualOperator()
{
}

ELookAheadCertainties EqualOperator::LookAhead(TokenList* tokens)
{
    AbstractToken* peekToken = tokens->Peek();

    if (peekToken->IsThisToken(ConstTokens.EQUAL_OPERATOR_TOKEN) ||
        peekToken->IsThisToken(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN) ||
        peekToken->IsThisToken(ConstTokens.LESS_THAN_OPERATOR_TOKEN) ||
        peekToken->IsThisToken(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN) ||
        peekToken->IsThisToken(ConstTokens.GREATER_THAN_OPERATOR_TOKEN) ||
        peekToken->IsThisToken(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN))
    {
        delete peekToken;
        return ELookAheadCertainties::CertainlyPresent;
    }

    delete peekToken;
    return ELookAheadCertainties::CertainlyNotPresent;
}

EqualOperator* EqualOperator::Parse(TokenList* tokens)
{
    AbstractToken* token = tokens->Next();

    EqualOperator* equalOperator = new EqualOperator();

    if (token->IsThisToken(ConstTokens.EQUAL_OPERATOR_TOKEN))
    {
        equalOperator->operatorSymbol = "==";
    }
    else if (token->IsThisToken(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN))
    {
        equalOperator->operatorSymbol = "!=";
    }
    else if (token->IsThisToken(ConstTokens.LESS_THAN_OPERATOR_TOKEN))
    {
        equalOperator->operatorSymbol = "<";
    }
    else if (token->IsThisToken(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN))
    {
        equalOperator->operatorSymbol = "<=";
    }
    else if (token->IsThisToken(ConstTokens.GREATER_THAN_OPERATOR_TOKEN))
    {
        equalOperator->operatorSymbol = ">";
    }
    else if (token->IsThisToken(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN))
    {
        equalOperator->operatorSymbol = ">=";
    }
    else
    {
        delete equalOperator;
        throw "Invalid token for EqualOperator. Did you forget to call LookAhead?";
    }

    delete token;
    return equalOperator;
}

std::string EqualOperator::ToString()
{
    return operatorSymbol;
}