#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Token.cpp"

class TokenList
{
   public:
    void AddToken(std::shared_ptr<Token> token);
    unsigned int GetSize();

    template <typename T>
    std::shared_ptr<T> Next()
    {
        return std::dynamic_pointer_cast<T>(Next());
    }

    std::shared_ptr<Token> Next();

    std::shared_ptr<Token> Peek(int offset = 0);
    bool IsPeekOfTokenType(std::shared_ptr<Token> other, int offset = 0);

    bool HasNext(int offset = 0);

    std::string ToString();

   private:
    // TODO: Make this use a queue instead of a vector
    std::vector<std::shared_ptr<Token>> tokens = std::vector<std::shared_ptr<Token>>();
    unsigned int readIndex = 0;
};

void TokenList::AddToken(std::shared_ptr<Token> token) { tokens.push_back(token); }

unsigned int TokenList::GetSize() { return tokens.size(); }

std::shared_ptr<Token> TokenList::Next()
{
    if (HasNext())
    {
        return tokens[readIndex++];
    }

    return nullptr;
}

std::shared_ptr<Token> TokenList::Peek(int offset)
{
    if (readIndex + offset < 0 || readIndex + offset >= GetSize())
    {
        return nullptr;
    }

    return tokens[readIndex + offset];
}

bool TokenList::IsPeekOfTokenType(std::shared_ptr<Token> other, int offset)
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