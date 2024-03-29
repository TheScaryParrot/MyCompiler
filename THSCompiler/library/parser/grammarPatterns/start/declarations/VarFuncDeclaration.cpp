#pragma once

#include "../../IGrammarPattern.cpp"

#include "declarationPatterns/ScopeDeclarationPattern.cpp"
#include "declarationPatterns/ReadWriteDeclarationPattern.cpp"

#include "../../../../tokens/ConstTokens.cpp"
#include "../../../../tokens/Keywords.cpp"

/// @brief The part of a declaration that declares a variable or function. Differentiation by whether () is present. This is handled by the parser.
class VarFuncDeclaration : IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static VarFuncDeclaration* Parse(TokenList* tokens);

    virtual std::string ToString() override;

    std::string name;
    std::string type;
};

ELookAheadCertainties VarFuncDeclaration::LookAhead(TokenList* tokens)
{
    if (ScopeDeclarationPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    // Static keyword is ambigious to Class Declaration. But for performance reasons we assume that Class Declaration has already been checked for.
    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD)) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    if (ReadWriteDeclarationPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN, 1)) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return ELookAheadCertainties::CertainlyNotPresent;
}

VarFuncDeclaration* VarFuncDeclaration::Parse(TokenList* tokens)
{
    VarFuncDeclaration* varFuncDeclaration = new VarFuncDeclaration();

    // TODO: Implement scope and stuff
    if (ScopeDeclarationPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        ScopeDeclarationPattern::Parse(tokens);
    }

    if (tokens->IsPeekOfTokenType(Keywords.STATIC_KEYWORD)) {
        tokens->Next();
    }

    if (ReadWriteDeclarationPattern::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        ReadWriteDeclarationPattern::Parse(tokens);
    }

    varFuncDeclaration->type = ((IdentifierToken*)tokens->Next())->GetValue();
    varFuncDeclaration->name = ((IdentifierToken*)tokens->Next())->GetValue();

    return varFuncDeclaration;
}

std::string VarFuncDeclaration::ToString()
{
    return "varFuncDeclaration: " + type + " " + name;
}