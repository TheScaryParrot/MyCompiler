#pragma once

#include <string>

#include "../AbstractToken.cpp"

class NumberConstToken : public AbstractToken
{
   public:
    NumberConstToken(std::string value);
    ~NumberConstToken();

    virtual std::string ToString() override;

    std::string GetValue();

   private:
    std::string value;
};

NumberConstToken::NumberConstToken(std::string value) : AbstractToken("numberConst") { this->value = value; }

NumberConstToken::~NumberConstToken() {}

std::string NumberConstToken::ToString() { return AbstractToken::ToString() + ": " + value; }

std::string NumberConstToken::GetValue() { return value; }