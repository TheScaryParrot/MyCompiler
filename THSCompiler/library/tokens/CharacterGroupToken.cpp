#pragma once

#include "AbstractToken.cpp"

class CharacterGroupToken : public AbstractToken {
public:
    CharacterGroupToken(std::string tokenName, CharacterGroup& characterGroup);
    ~CharacterGroupToken();

    unsigned int Match(char first, char second);

private:
    //TODO: Use more efficient way to store characterGroup (pointer or reference)
    CharacterGroup characterGroup;
};

CharacterGroupToken::CharacterGroupToken(std::string tokenName, CharacterGroup& characterGroup) : AbstractToken(tokenName) {
    this->characterGroup = characterGroup;
}

CharacterGroupToken::~CharacterGroupToken() {
}

unsigned int CharacterGroupToken::Match(char first, char second)
{
    return characterGroup.Match(first, second);
}