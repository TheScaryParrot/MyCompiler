#pragma once

#include "../../../syntaxTree/nodes/line/declaration/varFuncDeclaration/declarationAttributes/ESyntaxTreeScopes.cpp"
#include "EScopes.cpp"

struct DeclarationAttributes
{
   public:
    DeclarationAttributes() = default;
    DeclarationAttributes(EScopes scope, bool isFinal, bool isInline);
    DeclarationAttributes(ESyntaxTreeScopes scope, bool isFinal, bool isInline);

    EScopes scope = EScopes::PRIVATE;
    bool isFinal = false;
    bool isInline = false;
};

DeclarationAttributes::DeclarationAttributes(EScopes scope, bool isFinal, bool isInline)
{
    this->scope = scope;
    this->isFinal = isFinal;
    this->isInline = isInline;
}

DeclarationAttributes::DeclarationAttributes(ESyntaxTreeScopes scope, bool isFinal, bool isInline)
{
    switch (scope)
    {
        case ESyntaxTreeScopes::PUBLIC:
            this->scope = EScopes::PUBLIC;
            break;
        case ESyntaxTreeScopes::PROTECTED:
            this->scope = EScopes::PROTECTED;
            break;
        case ESyntaxTreeScopes::PRIVATE:
            this->scope = EScopes::PRIVATE;
            break;
    }

    this->isFinal = isFinal;
    this->isInline = isInline;
}
