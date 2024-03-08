#pragma once

#include "../AbstractKeywordToken.cpp"

class ElseKeyword : public AbstractKeywordToken {
public:
    ElseKeyword();
    ~ElseKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

ElseKeyword::ElseKeyword() : AbstractKeywordToken("else") {
}

ElseKeyword::~ElseKeyword() {
}

AbstractKeywordToken* ElseKeyword::GetNew() {
    return new ElseKeyword();
}