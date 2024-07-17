#pragma once

#include <string>

#include "Token.cpp"

class TokenWithValue : public Token
{
   public:
    TokenWithValue(std::string tokenName, std::string value) : Token(tokenName) { this->value = value; };

    virtual std::string ToString() override { return Token::ToString() + ": " + value; };

    std::string GetValue() { return value; };

    TokenWithValue* Clone(std::string value) { return new TokenWithValue(this->tokenName, value); };

   private:
    std::string value;
};