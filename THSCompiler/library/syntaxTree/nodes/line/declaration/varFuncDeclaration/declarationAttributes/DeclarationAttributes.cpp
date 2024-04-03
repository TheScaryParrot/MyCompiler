#pragma once

#include "EScopes.cpp"
#include "EReadWrites.cpp"

struct DeclarationAttributes
{
    EScopes scope = EScopes::PRIVATE;
    bool isStatic = false;
    EReadWrites readWrite = EReadWrites::FULL;

public:
    std::string ToString();
};

std::string DeclarationAttributes::ToString()
{
    std::string result =  EScopesToString(scope) + " ";
    
    if (isStatic) result += "static ";

    result += EReadWritesToString(readWrite);

    return result;
}