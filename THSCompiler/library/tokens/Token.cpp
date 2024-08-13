#pragma once

#include <memory>
#include <string>

#include "characterGroups/CharacterGroup.cpp"

class Token
{
   public:
    Token(std::string tokenName, unsigned int line)
    {
        this->tokenName = tokenName;
        this->line = line;
    }

    virtual bool IsThisToken(Token& other) { return this->tokenName == other.tokenName; }
    virtual bool IsInstruction() { return false; }
    virtual bool IsCompilerInstruction() { return false; }

    unsigned int GetLine() { return line; }

    virtual std::string ToString() { return tokenName; }

   protected:
    std::string tokenName;
    unsigned int line;
};