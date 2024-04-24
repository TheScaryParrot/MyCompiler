#pragma once

#include <string>
#include <memory>

#include "characterGroups/CharacterGroup.cpp"

class AbstractToken {
public:
    AbstractToken(std::string tokenName);
    virtual ~AbstractToken();

    virtual bool IsThisToken(std::shared_ptr<AbstractToken> other);
    virtual bool IsKeyword(); // returns false

    virtual std::string ToString();

private:
    std::string tokenName;
};

AbstractToken::AbstractToken(std::string tokenName) {
    this->tokenName = tokenName;
}

AbstractToken::~AbstractToken() {
}

bool AbstractToken::IsThisToken(std::shared_ptr<AbstractToken> other)
{
    return this->tokenName == other->tokenName;
}

bool AbstractToken::IsKeyword() {
    return false;
}


std::string AbstractToken::ToString() {
    return tokenName;
}