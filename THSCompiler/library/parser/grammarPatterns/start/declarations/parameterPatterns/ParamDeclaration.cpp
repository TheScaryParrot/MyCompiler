#pragma once

#include "../../../IGrammarPattern.cpp"

#include "../../../../../tokens/ConstTokens.cpp"

class ParamDeclaration : public IGrammarPattern
{
public:
    ParamDeclaration();
    ~ParamDeclaration();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static ParamDeclaration* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    std::string type;
    std::string name;
};

ParamDeclaration::ParamDeclaration()
{
}

ParamDeclaration::~ParamDeclaration()
{
}

ELookAheadCertainties ParamDeclaration::LookAhead(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1))
    {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

ParamDeclaration* ParamDeclaration::Parse(TokenList* tokens)
{
    ParamDeclaration* paramDeclaration = new ParamDeclaration();

    paramDeclaration->type = ((IdentifierToken*)tokens->Next())->GetValue();
    paramDeclaration->name = ((IdentifierToken*)tokens->Next())->GetValue();

    return paramDeclaration;
}

std::string ParamDeclaration::ToString()
{
    return type + " " + name;
}