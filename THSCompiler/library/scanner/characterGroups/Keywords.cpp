#pragma once

#include <string>

#include "../../tokens/AbstractToken.cpp"
#include "../../tokens/keywords/logicFlow/IfKeyword.cpp"
#include "../../tokens/keywords/logicFlow/ElseKeyword.cpp"
#include "../../tokens/keywords/logicFlow/ElifKeyword.cpp"
#include "../../tokens/keywords/logicFlow/WhileKeyword.cpp"
#include "../../tokens/keywords/logicFlow/ForKeyword.cpp"
#include "../../tokens/keywords/classes/ClassKeyword.cpp"
#include "../../tokens/keywords/classes/PublicKeyword.cpp"
#include "../../tokens/keywords/classes/PrivateKeyword.cpp"

static class Keywords {
public:
    /// @brief Returns the token for the given keyword. If the keyword is not a keyword, returns nullptr.
    static AbstractToken* GetKeywordToken(std::string keyword);

private:
    static AbstractKeywordToken* keywords[8];
}Keywords;

AbstractKeywordToken* Keywords::keywords[8] = {
    new IfKeyword(),
    new ElseKeyword(),
    new ElifKeyword(),
    new WhileKeyword(),
    new ForKeyword(),
    new ClassKeyword(),
    new PublicKeyword(),
    new PrivateKeyword()
};

AbstractToken* Keywords::GetKeywordToken(std::string keyword) {
    for (AbstractKeywordToken* keywordToken : keywords) {
        if (keywordToken->IsKeyword(keyword)) {
            return keywordToken;
        }
    }

    return nullptr;
}