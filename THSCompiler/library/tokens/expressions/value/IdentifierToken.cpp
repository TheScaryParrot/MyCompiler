#pragma once

#include <library/tokens/AbstractToken.cpp>
#include <string>

class IdentifierToken : public AbstractToken {

public:
    IdentifierToken(std::string value);
    ~IdentifierToken();

    std::string GetValue();

private:

    std::string value;
};

IdentifierToken::IdentifierToken(std::string value) {
    this->value = value;
}

IdentifierToken::~IdentifierToken() {
}

std::string IdentifierToken::GetValue() {
    return value;
}