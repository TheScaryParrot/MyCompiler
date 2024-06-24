#pragma once

#include <string>

#include "../AbstractToken.cpp"

class IdentifierToken : public AbstractToken
{
   public:
    IdentifierToken(std::string value);
    ~IdentifierToken();

    virtual std::string ToString() override;

    std::string GetValue();

   private:
    std::string value;
};

IdentifierToken::IdentifierToken(std::string value) : AbstractToken("identifier") { this->value = value; }

IdentifierToken::~IdentifierToken() {}

std::string IdentifierToken::ToString() { return AbstractToken::ToString() + ": " + value; }

std::string IdentifierToken::GetValue() { return value; }