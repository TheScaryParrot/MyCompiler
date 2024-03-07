#pragma once

class AbstractToken {
public:
    AbstractToken();
    ~AbstractToken();

    virtual std::string ToString();
};

AbstractToken::AbstractToken() {
}

AbstractToken::~AbstractToken() {
}

std::string AbstractToken::ToString() {
    return "AbstractToken";
}