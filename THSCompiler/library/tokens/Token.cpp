#pragma once

#include <memory>
#include <string>

#include "characterGroups/CharacterGroup.cpp"

class Token
{
   public:
    Token(std::string tokenName);
    virtual ~Token();

    virtual bool IsThisToken(std::shared_ptr<Token> other);
    virtual bool IsKeyword();  // returns false

    virtual std::string ToString();

   protected:
    std::string tokenName;
};

Token::Token(std::string tokenName) { this->tokenName = tokenName; }

Token::~Token() {}

bool Token::IsThisToken(std::shared_ptr<Token> other) { return this->tokenName == other->tokenName; }

bool Token::IsKeyword() { return false; }

std::string Token::ToString() { return tokenName; }