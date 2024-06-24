#pragma once

#include "EScopes.cpp"

struct DeclarationAttributes
{
    EScopes scope = EScopes::PRIVATE;
    bool isStatic = false;
    // EReadWrites readWrite = EReadWrites::FULL; deprecated replaced by final and inline
    bool isFinal = false;
    bool isInline = false;

   public:
    std::string ToString();
};

std::string DeclarationAttributes::ToString()
{
    std::string result = EScopesToString(scope) + " ";

    if (isStatic) result += "static ";
    if (isFinal) result += "final ";
    if (isInline) result += "inline ";

    return result;
}