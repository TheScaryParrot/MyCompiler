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
    AbstractToken* Peek(int offset);

    template <typename T> bool IsPeekOfType(int offset)
    {
        if (Peek(offset) == nullptr) {
            return false;
        }

        return typeid(*Peek(offset)) == typeid(T);
    };

    bool HasNext();

    std::string ToString();

private:
    std::vector<AbstractToken*> tokens;
    unsigned int readIndex = 0;
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

bool TokenList::HasNext() {
    return readIndex < tokens.size();
}

std::string TokenList::ToString() {
    std::string result = "";
    for (int i = 0; i < tokens.size(); i++) {
        result += tokens[i]->ToString() + "\n";
    }
    return result;
}