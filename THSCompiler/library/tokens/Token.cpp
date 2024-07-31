#pragma once

#include <memory>
#include <string>

#include "characterGroups/CharacterGroup.cpp"

class Token
{
   public:
    Token(std::string tokenName) { this->tokenName = tokenName; }

    virtual bool IsThisToken(std::shared_ptr<Token> other) { return this->tokenName == other->tokenName; }
    virtual bool IsInstruction() { return false; }
    virtual bool IsCompilerInstruction() { return false; }

    virtual std::string ToString() { return tokenName; }

   protected:
    std::string tokenName;
};