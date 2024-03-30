#pragma once

#include "EScopes.cpp"
#include "EReadWrites.cpp"

struct DeclarationAttributes
{
    EScopes scope;
    bool isStatic;
    EReadWrites readWrite;
};