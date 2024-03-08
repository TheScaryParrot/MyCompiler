#pragma once

#include "../AbstractKeywordToken.cpp"

class ElifKeyword : public AbstractKeywordToken {
public:
    ElifKeyword();
    ~ElifKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

ElifKeyword::ElifKeyword() : AbstractKeywordToken("elif") {
}

ElifKeyword::~ElifKeyword() {
}

AbstractKeywordToken* ElifKeyword::GetNew() {
    return new ElifKeyword();
}