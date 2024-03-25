#pragma once

#include <string>

#include "AbstractToken.cpp"

class AbstractKeywordToken : public AbstractToken {
public:
    AbstractKeywordToken(std::string keyword);
    ~AbstractKeywordToken();

    virtual bool IsThisToken(AbstractToken* other) override;
    virtual std::string ToString() override;

    bool IsThisKeyword(std::string keyword);

private: 
    std::string keyword;
};

AbstractKeywordToken::AbstractKeywordToken(std::string keyword) : AbstractToken("keyword"){
    this->keyword = keyword;
}

AbstractKeywordToken::~AbstractKeywordToken() {
}

bool AbstractKeywordToken::IsThisToken(AbstractToken* other) {
    return AbstractToken::IsThisToken(other) && this->IsThisKeyword(((AbstractKeywordToken*)other)->keyword);
}

std::string AbstractKeywordToken::ToString() {
    return AbstractToken::ToString() + ":" + this->keyword;
}

bool AbstractKeywordToken::IsThisKeyword(std::string keyword) {
    return this->keyword == keyword;
}