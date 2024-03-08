#pragma once

#include "../AbstractKeywordToken.cpp"

class IfKeyword : public AbstractKeywordToken {
public:
    IfKeyword();
    ~IfKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

IfKeyword::IfKeyword() : AbstractKeywordToken("if") {
}

IfKeyword::~IfKeyword() {
}

AbstractKeywordToken* IfKeyword::GetNew() {
    return new IfKeyword();
}