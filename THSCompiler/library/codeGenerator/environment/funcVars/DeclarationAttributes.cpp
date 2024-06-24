#pragma once

#include "EScopes.cpp"

struct DeclarationAttributes
{
   public:
    EScopes scope = EScopes::PRIVATE;
    bool isFinal = false;
    bool isInline = false;
};