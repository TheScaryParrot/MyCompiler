#pragma once

#include "../../IGrammarPattern.cpp"
#include "ClassDeclaration.cpp"
#include "VarFuncDeclaration.cpp"
#include "FuncDeclaration.cpp"
#include "VarDeclaration.cpp"

class DeclarationPattern : public IGrammarPattern
{
public:
    DeclarationPattern();
    ~DeclarationPattern();

    static ELookAheadCertainties LookAhead(TokenList* tokens);
    static DeclarationPattern* Parse(TokenList* tokens);

    virtual std::string ToString() override;

private:
    ClassDeclaration* classDeclaration = nullptr;
    FuncDeclaration* funcDeclaration = nullptr;
    VarDeclaration* varDeclaration = nullptr;
};

DeclarationPattern::DeclarationPattern()
{
}

DeclarationPattern::~DeclarationPattern()
{
    delete classDeclaration;
    delete funcDeclaration;
    delete varDeclaration;
}

ELookAheadCertainties DeclarationPattern::LookAhead(TokenList* tokens)
{
    if (ClassDeclaration::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        return ELookAheadCertainties::CertainlyPresent;
    }

    return VarFuncDeclaration::LookAhead(tokens);
}

DeclarationPattern* DeclarationPattern::Parse(TokenList* tokens)
{
    DeclarationPattern* declarationPattern = new DeclarationPattern();

    if (ClassDeclaration::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        declarationPattern->classDeclaration = ClassDeclaration::Parse(tokens);
        return declarationPattern;
    }

    VarFuncDeclaration* varFuncDeclaration = VarFuncDeclaration::Parse(tokens);

    if (FuncDeclaration::LookAhead(tokens) == ELookAheadCertainties::CertainlyPresent) {
        declarationPattern->funcDeclaration = FuncDeclaration::Parse(tokens, varFuncDeclaration);
        delete varFuncDeclaration;
        return declarationPattern;
    }

    declarationPattern->varDeclaration = VarDeclaration::Parse(tokens, varFuncDeclaration);
    delete varFuncDeclaration;
    return declarationPattern;

    delete declarationPattern;
    throw "Could not parse declaration. Did you run LookAhead before Parse?";
}

std::string DeclarationPattern::ToString()
{
    if (classDeclaration != nullptr) {
        return classDeclaration->ToString();
    }

    if (funcDeclaration != nullptr) {
        return funcDeclaration->ToString();
    }

    return varDeclaration->ToString();
}