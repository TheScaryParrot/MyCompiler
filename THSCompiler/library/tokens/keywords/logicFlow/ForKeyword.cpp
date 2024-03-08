#pragma once

#include "../AbstractKeywordToken.cpp"

class ForKeyword : public AbstractKeywordToken {
public:
    ForKeyword();
    ~ForKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

ForKeyword::ForKeyword() : AbstractKeywordToken("for") {
}

ForKeyword::~ForKeyword() {
}

AbstractKeywordToken* ForKeyword::GetNew() {
    return new ForKeyword();
}