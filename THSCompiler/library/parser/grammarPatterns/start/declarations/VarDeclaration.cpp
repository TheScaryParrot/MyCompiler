#pragma once

#include "../../IGrammarPattern.cpp"
#include "VarFuncDeclaration.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class VarDeclaration : IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static VarDeclaration* Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration);

    virtual std::string ToString() override;

private:
    std::string name;
    std::string type;
    // Expression* expression;
};

ELookAheadCertainties VarDeclaration::LookAhead(TokenList* tokens)
{
    return ELookAheadCertainties::CertainlyPresent;
}

VarDeclaration* VarDeclaration::Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration)
{
    VarDeclaration* varDeclaration = new VarDeclaration();

    varDeclaration->type = varFuncDeclaration->type;
    varDeclaration->name = varFuncDeclaration->name;
    //Parse scope of varFuncDeclaration
    
    // CONSUME EXPRESSION

    return varDeclaration;
}

std::string VarDeclaration::ToString()
{
    return "var declaration: " + type + " " + name;
}