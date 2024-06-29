#pragma once

#include <string>

#include "AbstractToken.cpp"

class AbstractKeywordToken : public AbstractToken
{
   public:
    AbstractKeywordToken(std::string keyword);
    ~AbstractKeywordToken();

    virtual bool IsThisToken(std::shared_ptr<AbstractToken> other) override;
    virtual std::string ToString() override;

    bool IsThisKeyword(std::string keyword);

    virtual bool IsKeyword() override;  // returns true

   private:
    std::string keyword;
};

AbstractKeywordToken::AbstractKeywordToken(std::string keyword) : AbstractToken("keyword") { this->keyword = keyword; }

AbstractKeywordToken::~AbstractKeywordToken() {}

bool AbstractKeywordToken::IsThisToken(std::shared_ptr<AbstractToken> other)
{
    return AbstractToken::IsThisToken(other) &&
           this->IsThisKeyword(std::dynamic_pointer_cast<AbstractKeywordToken>(other)->keyword);
}

std::string AbstractKeywordToken::ToString() { return AbstractToken::ToString() + ":" + this->keyword; }

bool AbstractKeywordToken::IsThisKeyword(std::string keyword) { return this->keyword == keyword; }

bool AbstractKeywordToken::IsKeyword() { return true; }