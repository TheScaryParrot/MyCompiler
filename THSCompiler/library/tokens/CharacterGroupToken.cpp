#pragma once

#include "Token.cpp"

class CharacterGroupToken : public Token
{
   public:
    CharacterGroupToken(std::string tokenName, CharacterGroup& characterGroup);
    ~CharacterGroupToken();

    unsigned int Match(char first, char second);

   private:
    // TODO: Use more efficient way to store characterGroup (pointer or reference)
    CharacterGroup characterGroup;
};

CharacterGroupToken::CharacterGroupToken(std::string tokenName, CharacterGroup& characterGroup) : Token(tokenName)
{
    this->characterGroup = characterGroup;
}

CharacterGroupToken::~CharacterGroupToken() {}

unsigned int CharacterGroupToken::Match(char first, char second) { return characterGroup.Match(first, second); }