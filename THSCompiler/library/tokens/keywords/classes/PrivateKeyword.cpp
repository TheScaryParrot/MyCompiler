#pragma once

#include "../AbstractKeywordToken.cpp"

class PrivateKeyword : public AbstractKeywordToken {
public:
    PrivateKeyword();
    ~PrivateKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

PrivateKeyword::PrivateKeyword() : AbstractKeywordToken("private") {
}

PrivateKeyword::~PrivateKeyword() {
}

AbstractKeywordToken* PrivateKeyword::GetNew() {
    return new PrivateKeyword();
}