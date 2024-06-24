#pragma once

#include <string>

#include "../AbstractToken.cpp"

class StringConstToken : public AbstractToken
{
   public:
    StringConstToken(std::string value);
    ~StringConstToken();

    virtual std::string ToString() override;

    std::string GetValue();

   private:
    std::string value;
};

StringConstToken::StringConstToken(std::string value) : AbstractToken("stringConst") { this->value = value; }

StringConstToken::~StringConstToken() {}

std::string StringConstToken::ToString() { return AbstractToken::ToString() + ": " + value; }

std::string StringConstToken::GetValue() { return value; }