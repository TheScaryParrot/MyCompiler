#pragma once

#include <memory>
#include <string>
#include <vector>

#include "AbstractToken.cpp"

class TokenList
{
   public:
    TokenList();
    ~TokenList();

    void AddToken(std::shared_ptr<AbstractToken> token);
    unsigned int GetSize();

    template <typename T>
    std::shared_ptr<T> Next()
    {
        return std::dynamic_pointer_cast<T>(Next());
    }

    std::shared_ptr<AbstractToken> Next();

    std::shared_ptr<AbstractToken> Peek(int offset = 0);
    bool IsPeekOfTokenType(std::shared_ptr<AbstractToken> other, int offset = 0);

    bool HasNext(int offset = 0);

    std::string ToString();

   private:
    std::vector<std::shared_ptr<AbstractToken>> tokens = std::vector<std::shared_ptr<AbstractToken>>();
    unsigned int readIndex = 0;
};

TokenList::TokenList() {}

TokenList::~TokenList()
{
    // Not needed due to shared_ptr
    /*for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == nullptr) {
            continue;
        }

        delete tokens[i];
        tokens[i] = nullptr;
    }*/
}

void TokenList::AddToken(std::shared_ptr<AbstractToken> token) { tokens.push_back(token); }

unsigned int TokenList::GetSize() { return tokens.size(); }

std::shared_ptr<AbstractToken> TokenList::Next()
{
    if (HasNext())
    {
        return tokens[readIndex++];
    }

    return nullptr;
}

std::shared_ptr<AbstractToken> TokenList::Peek(int offset)
{
    if (readIndex + offset < 0 || readIndex + offset >= GetSize())
    {
        return nullptr;
    }

    return tokens[readIndex + offset];
}

bool TokenList::IsPeekOfTokenType(std::shared_ptr<AbstractToken> other, int offset)
{
    if (!HasNext(offset))
    {
        return false;
    }

    return Peek(offset)->IsThisToken(other);
}

bool TokenList::HasNext(int offset) { return readIndex + offset < tokens.size(); }

std::string TokenList::ToString()
{
    std::string result = "";
    for (int i = 0; i < tokens.size(); i++)
    {
        result += tokens[i]->ToString() + "\n";
    }
    return result;
}