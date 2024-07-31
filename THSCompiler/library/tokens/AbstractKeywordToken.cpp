#pragma once

#include <string>

#include "Token.cpp"

class AbstractKeywordToken : public Token
{
   public:
    AbstractKeywordToken(std::string keyword) : Token("keyword") { this->keyword = keyword; }

    virtual bool IsThisToken(std::shared_ptr<Token> other) override
    {
        return this->Token::IsThisToken(other) && this->IsThisKeyword(std::dynamic_pointer_cast<AbstractKeywordToken>(other)->keyword);
    }
    virtual std::string ToString() override { return Token::ToString() + ":" + this->keyword; }

    bool IsThisKeyword(std::string keyword) { return this->keyword == keyword; }

    virtual bool IsInstruction() override { return true; }

   private:
    std::string keyword;
};