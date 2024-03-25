#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>
#include "VarFuncDeclaration.cpp"

#include <library/tokens/expressions/value/IdentifierToken.cpp>

class VarDeclaration : IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static VarDeclaration* Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration);

private:
    std::string name;
    std::string type;
    // Expression* expression;
};

ELookAheadCertainties VarDeclaration::LookAhead(TokenList* tokens)
{
    
}

VarDeclaration* VarDeclaration::Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration)
{
    VarDeclaration* varDeclaration = new VarDeclaration();

    varDeclaration->type = varFuncDeclaration->type;
    varDeclaration->name = varFuncDeclaration->name;
    
    // CONSUME EXPRESSION

    return varDeclaration;
}