#pragma once

#include <string>

#include "characterGroups/CharacterGroup.cpp"

class AbstractToken {
public:
    AbstractToken(std::string tokenName, CharacterGroup* characterGroup = nullptr);
    virtual ~AbstractToken();

    virtual bool IsThisToken(AbstractToken& other);
    virtual bool IsInCharacterGroup(std::string character);

    virtual std::string ToString();

private:
    std::string tokenName;
    CharacterGroup* characterGroup;
};

AbstractToken::AbstractToken(std::string tokenName, CharacterGroup* characterGroup) {
    this->tokenName = tokenName;
    this->characterGroup = characterGroup;
}

AbstractToken::~AbstractToken() {
}

bool AbstractToken::IsThisToken(AbstractToken& other)
{
    return this->tokenName == other.tokenName;
}

bool AbstractToken::IsInCharacterGroup(std::string character) {
    if (characterGroup == nullptr) {
        return false;
    }

    return characterGroup->Contains(character);
}

std::string AbstractToken::ToString() {
    return tokenName;
}