#pragma once

#include "ESyntaxTreeScopes.cpp"

struct SyntaxTreeDeclarationAttributes
{
    ESyntaxTreeScopes scope = ESyntaxTreeScopes::PRIVATE;
    bool isStatic = false;
    // EReadWrites readWrite = EReadWrites::FULL; deprecated replaced by final and inline
    bool isFinal = false;
    bool isInline = false;

   public:
    std::string ToString();
};

std::string SyntaxTreeDeclarationAttributes::ToString()
{
    std::string result = EScopesToString(scope) + " ";

    if (isStatic) result += "static ";
    if (isFinal) result += "final ";
    if (isInline) result += "inline ";

    return result;
}