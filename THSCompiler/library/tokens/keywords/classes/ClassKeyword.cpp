#pragma once

#include "../AbstractKeywordToken.cpp"

class ClassKeyword : public AbstractKeywordToken {
public:
    ClassKeyword();
    ~ClassKeyword();

    virtual AbstractKeywordToken* GetNew() override;
};

ClassKeyword::ClassKeyword() : AbstractKeywordToken("class") {
}

ClassKeyword::~ClassKeyword() {
}

AbstractKeywordToken* ClassKeyword::GetNew() {
    return new ClassKeyword();
}