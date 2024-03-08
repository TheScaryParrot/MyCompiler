#pragma once

#include <string>

#include "../AbstractToken.cpp"

class AbstractKeywordToken : public AbstractToken {
public:
    AbstractKeywordToken(std::string keyword);
    ~AbstractKeywordToken();

    virtual std::string ToString() override;

    virtual AbstractKeywordToken* GetNew();

    bool IsKeyword(std::string keyword);

private: 
    std::string keyword;
};

AbstractKeywordToken::AbstractKeywordToken(std::string keyword) {
    this->keyword = keyword;
}

AbstractKeywordToken::~AbstractKeywordToken() {
}

std::string AbstractKeywordToken::ToString() {
    return "Keyword: " + this->keyword;
}

bool AbstractKeywordToken::IsKeyword(std::string keyword) {
    return this->keyword == keyword;
}

AbstractKeywordToken* AbstractKeywordToken::GetNew() {
    throw "GetNew not implemented";
}