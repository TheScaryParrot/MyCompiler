#pragma once

#include <vector>
#include <string>

#include "AbstractToken.cpp"

class TokenList {
public:
    TokenList();
    ~TokenList();

    void AddToken(AbstractToken* token);
    unsigned int GetSize();

    AbstractToken* Next();
    AbstractToken* Peek(int offset = 0);
    bool IsPeekOfTokenType(AbstractToken& other, int offset = 0);

    bool HasNext(int offset = 0);

    std::string ToString();

private:
    std::vector<AbstractToken*> tokens = std::vector<AbstractToken*>();
    unsigned int readIndex = 0;
};

TokenList::TokenList() {
}

TokenList::~TokenList() {
    for (int i = 0; i < tokens.size(); i++) {
        delete tokens[i];
    }
}

void TokenList::AddToken(AbstractToken* token) {
    tokens.push_back(token);
}

unsigned int TokenList::GetSize() {
    return tokens.size();
}

AbstractToken* TokenList::Next() {
    if (HasNext()) {
        return tokens[readIndex++];
    }
    return nullptr;
}

AbstractToken* TokenList::Peek(int offset) {
    if (readIndex + offset < 0 || readIndex + offset >= GetSize()) {
        return nullptr;
    }

    return tokens[readIndex + offset];
}

bool TokenList::IsPeekOfTokenType(AbstractToken& other, int offset) {
    if (!HasNext(offset)) {
        return false;
    }

    return Peek(offset)->IsThisToken(other);
}

bool TokenList::HasNext(int offset) {
    return readIndex + offset < tokens.size();
}

std::string TokenList::ToString() {
    std::string result = "";
    for (int i = 0; i < tokens.size(); i++) {
        result += tokens[i]->ToString() + "\n";
    }
    return result;
}