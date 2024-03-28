#pragma once

#include <string>

#include "../AbstractToken.cpp"

class StringConst : public AbstractToken {

public:
    StringConst(std::string value);
    ~StringConst();

    virtual std::string ToString() override;
    
    std::string GetValue();

private:
    std::string value;
};

StringConst::StringConst(std::string value) : AbstractToken("stringConst"){
    this->value = value;
}

StringConst::~StringConst() {
}

std::string StringConst::ToString() {
    return AbstractToken::ToString() + ": " + value;
}   

std::string StringConst::GetValue() {
    return value;
}