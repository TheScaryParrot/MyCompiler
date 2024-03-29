#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class SumOperator : public IGrammarPattern
{
public:
    SumOperator();
    ~SumOperator();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static SumOperator* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string operatorSymbol;
};

SumOperator::SumOperator()
{
}

SumOperator::~SumOperator()
{
}

ELookAheadCertainties SumOperator::LookAhead(TokenList* tokens)
{
    AbstractToken* peekToken = tokens->Peek();

    if (peekToken->IsThisToken(ConstTokens.ADD_OPERATOR_TOKEN) || peekToken->IsThisToken(ConstTokens.SUB_OPERATOR_TOKEN))
    {
        delete peekToken;
        return ELookAheadCertainties::CertainlyPresent;
    }

    delete peekToken;
    return ELookAheadCertainties::CertainlyNotPresent;
}

SumOperator* SumOperator::Parse(TokenList* tokens)
{
    AbstractToken* token = tokens->Next();

    SumOperator* sumOperator = new SumOperator();

    if (token->IsThisToken(ConstTokens.ADD_OPERATOR_TOKEN))
    {
        sumOperator->operatorSymbol = "+";
    }
    else if (token->IsThisToken(ConstTokens.SUB_OPERATOR_TOKEN))
    {
        sumOperator->operatorSymbol = "-";
    }
    else
    {
        delete token;
        delete sumOperator;
        throw "Invalid token for SumOperator. Did you forget to call LookAhead?";
    }

    delete token;
    return sumOperator;
}

std::string SumOperator::ToString()
{
    return operatorSymbol;
}