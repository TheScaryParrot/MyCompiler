#pragma once

#include "../../IGrammarPattern.cpp"
#include "VarFuncDeclaration.cpp"

#include "../../../../tokens/ConstTokens.cpp"

class FuncDeclaration : IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static FuncDeclaration* Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration);

    virtual std::string ToString() override;

private:
    std::string name;
    std::string returnType;
    // Body* body;
};

/// @brief Checks whether the next tokens are a function declaration. Assumes that varFuncDeclaration has already been parsed(consumed)
ELookAheadCertainties FuncDeclaration::LookAhead(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN) ? ELookAheadCertainties::CertainlyPresent : ELookAheadCertainties::CertainlyNotPresent;
}

FuncDeclaration* FuncDeclaration::Parse(TokenList* tokens, VarFuncDeclaration* varFuncDeclaration)
{
    FuncDeclaration* funcDeclaration = new FuncDeclaration();

    funcDeclaration->returnType = varFuncDeclaration->type;
    funcDeclaration->name = varFuncDeclaration->name;
    // Parse scope of varFuncDeclaration

    tokens->Next(); // Consume (
    // Parse parameters

    tokens->Next(); // Consume )

    // Parse body

    return funcDeclaration;
}

std::string FuncDeclaration::ToString()
{
    return "function declaration: " + returnType + " " + name + "()";
}