#pragma once

#include <library/parser/grammarPatterns/IGrammarPattern.cpp>
#include "ClassDeclaration.cpp"

class DeclarationPattern : public IGrammarPattern
{
public:
    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static DeclarationPattern* Parse(TokenList* tokens);

private:
    ClassDeclaration* classDeclaration;
};

ELookAheadCertainties DeclarationPattern::LookAhead(TokenList* tokens)
{
    if (ClassDeclaration::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    // VAR DECLARATION
    // FUNCTION DECLARATION

    return ELookAheadCertainties::CertainlyNotPresent;
}

DeclarationPattern* DeclarationPattern::Parse(TokenList* tokens)
{
    DeclarationPattern* declarationPattern = new DeclarationPattern();

    if (ClassDeclaration::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        declarationPattern->classDeclaration = ClassDeclaration::Parse(tokens);
        return declarationPattern;
    }

    delete declarationPattern;
    return nullptr;
}