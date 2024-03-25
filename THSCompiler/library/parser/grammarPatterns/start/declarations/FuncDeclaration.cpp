#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>
#include "VarFuncDeclaration.cpp"

#include <library/tokens/expressions/value/IdentifierToken.cpp>

class FuncDeclaration : IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static FuncDeclaration* Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration);

private:
    std::string name;
    std::string returnType;
    // Body* body;
};

/// @brief Checks whether the next tokens are a function declaration. Assumes that varFuncDeclaration has already been parsed(consumed)
ELookAheadCertainties FuncDeclaration::LookAhead(TokenList* tokens)
{
    // Check if the next token is a (
}

FuncDeclaration* FuncDeclaration::Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration)
{
    FuncDeclaration* funcDeclaration = new FuncDeclaration();

    funcDeclaration->returnType = varFuncDeclaration->type;
    funcDeclaration->name = varFuncDeclaration->name;

    tokens->Next(); // Consume (
    // Parse parameters

    tokens->Next(); // Consume )

    // Parse body

    return funcDeclaration;
}