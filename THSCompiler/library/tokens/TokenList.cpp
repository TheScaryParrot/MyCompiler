#pragma once

#include <vector>
#include <string>

#include "AbstractToken.cpp"

class TokenList {
public:
    TokenList();
    ~TokenList();

    void AddToken(AbstractToken* token);
    int GetSize();

    std::string ToString();

private:
    std::vector<AbstractToken*> tokens;
};

TokenList::TokenList() {
    tokens = std::vector<AbstractToken*>();
}

TokenList::~TokenList() {
    tokens.clear();
}

void TokenList::AddToken(AbstractToken* token) {
    tokens.push_back(token);
}

int TokenList::GetSize() {
    return tokens.size();
}

std::string TokenList::ToString() {
    std::string result = "";
    for (int i = 0; i < tokens.size(); i++) {
        result += tokens[i]->ToString() + "\n";
    }
    return result;
}