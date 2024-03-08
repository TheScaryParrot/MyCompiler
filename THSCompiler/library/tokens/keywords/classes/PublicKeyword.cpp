#pragma once

#include "../AbstractKeywordToken.cpp"

class PublicKeyword : public AbstractKeywordToken {
public:
    PublicKeyword();
    ~PublicKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

PublicKeyword::PublicKeyword() : AbstractKeywordToken("public") {
}

PublicKeyword::~PublicKeyword() {
}

AbstractKeywordToken* PublicKeyword::GetNew() {
    return new PublicKeyword();
}