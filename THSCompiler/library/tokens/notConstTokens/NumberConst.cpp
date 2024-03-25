#pragma once

#include "../AbstractToken.cpp"
#include <string>

class NumberConst : public AbstractToken {

public:
    NumberConst(std::string value);
    ~NumberConst();

    virtual std::string ToString() override;

    std::string GetValue();

private:
    std::string value;
};

NumberConst::NumberConst(std::string value) : AbstractToken("numberConst"){
    this->value = value;
}

NumberConst::~NumberConst() {
}

std::string NumberConst::ToString() {
    return AbstractToken::ToString() + ": " + value;
}

std::string NumberConst::GetValue() {
    return value;
}