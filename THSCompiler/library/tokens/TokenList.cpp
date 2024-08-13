#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Token.cpp"

class TokenList
{
   public:
    ~TokenList()
    {
        for (auto token : tokens)
        {
            delete token;
        }
    }

    void AddToken(Token* token) { tokens.push_back(token); }
    unsigned int GetSize() { return tokens.size(); }

    template <typename T>
    T* Next()
    {
        return dynamic_cast<T*>(Next());
    }

    Token* Next()
    {
        if (HasNext())
        {
            return tokens[readIndex++];
        }

        return nullptr;
    }

    Token* Peek(int offset = 0)
    {
        if (readIndex + offset < 0 || readIndex + offset >= GetSize())
        {
            return nullptr;
        }

        return tokens[readIndex + offset];
    }
    bool IsPeekOfTokenType(Token& other, int offset = 0)
    {
        if (!HasNext(offset))
        {
            return false;
        }

        return Peek(offset)->IsThisToken(other);
    }

    bool HasNext(int offset = 0) { return readIndex + offset < tokens.size(); }

    std::string ToString()
    {
        std::string result = "";
        for (int i = 0; i < tokens.size(); i++)
        {
            result += tokens[i]->ToString() + "\n";
        }
        return result;
    }

   private:
    // TODO: Maybe a better data structure for this as there is a lot of adding
    std::vector<Token*> tokens;
    unsigned int readIndex = 0;
};