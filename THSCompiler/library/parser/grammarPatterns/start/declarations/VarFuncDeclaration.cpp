

#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>

#include <library/tokens/expressions/value/IdentifierToken.cpp>

/// @brief The part of a declaration that declares a variable or function. Differentiation by whether () is present. This is handled by the parser.
class VarFuncDeclaration : IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static VarFuncDeclaration* Parse(TokenList* tokens);
    std::string name;
    std::string type;
};

ELookAheadCertainties VarFuncDeclaration::LookAhead(TokenList* tokens)
{
    if (tokens->IsPeekOfType<IdentifierToken>(0)) {
        if (tokens->IsPeekOfType<IdentifierToken>(1)) {
            return ELookAheadCertainties::CertainlyPresent;
        }
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

VarFuncDeclaration* VarFuncDeclaration::Parse(TokenList* tokens)
{
    
}