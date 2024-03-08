#pragma once

#include "../AbstractKeywordToken.cpp"

class WhileKeyword : public AbstractKeywordToken {
public:
    WhileKeyword();
    ~WhileKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

WhileKeyword::WhileKeyword() : AbstractKeywordToken("while") {
}

WhileKeyword::~WhileKeyword() {
}

AbstractKeywordToken* WhileKeyword::GetNew() {
    return new WhileKeyword();
}