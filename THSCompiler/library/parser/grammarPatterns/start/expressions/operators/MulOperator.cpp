#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class MulOperator : public IGrammarPattern
{
public:
    MulOperator();
    ~MulOperator();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static MulOperator* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string operatorSymbol;
};

MulOperator::MulOperator()
{
}

MulOperator::~MulOperator()
{
}

ELookAheadCertainties MulOperator::LookAhead(TokenList* tokens)
{
    AbstractToken* peekToken = tokens->Peek();

    if (peekToken->IsThisToken(ConstTokens.MUL_OPERATOR_TOKEN) || peekToken->IsThisToken(ConstTokens.DIV_OPERATOR_TOKEN) || peekToken->IsThisToken(ConstTokens.MOD_OPERATOR_TOKEN))
    {
        delete peekToken;
        return ELookAheadCertainties::CertainlyPresent;
    }

    delete peekToken;
    return ELookAheadCertainties::CertainlyNotPresent;
}

MulOperator* MulOperator::Parse(TokenList* tokens)
{
    AbstractToken* token = tokens->Next();

    MulOperator* mulOperator = new MulOperator();

    if (token->IsThisToken(ConstTokens.MUL_OPERATOR_TOKEN))
    {
        mulOperator->operatorSymbol = "*";
    }
    else if (token->IsThisToken(ConstTokens.DIV_OPERATOR_TOKEN))
    {
        mulOperator->operatorSymbol = "/";
    }
    else if (token->IsThisToken(ConstTokens.MOD_OPERATOR_TOKEN))
    {
        mulOperator->operatorSymbol = "%";
    }
    else
    {
        delete token;
        delete mulOperator;
        throw "Invalid token for MulOperator. Did you forget to call LookAhead?";
    }

    delete token;
    return mulOperator;
}

std::string MulOperator::ToString()
{
    return operatorSymbol;
}