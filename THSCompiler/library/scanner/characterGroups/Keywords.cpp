#pragma once

#include <string>

#include "../../tokens/AbstractToken.cpp"

static class Keywords {
public:
    /// @brief Returns the token for the given keyword. If the keyword is not a keyword, returns nullptr.
    static AbstractToken* GetKeywordToken(std::string keyword);

}Keywords;

AbstractToken* Keywords::GetKeywordToken(std::string keyword) {
    if (keyword == "if")
    {
        //TODO: Return if token
    }

    if (keyword == "else")
    {
        //TODO: Return else token
    }
    
    if (keyword == "elif")
    {
        //TODO: Return elif token
    }

    if (keyword == "while")
    {
        //TODO: Return while token
    }

    if (keyword == "for")
    {
        //TODO: Return for token
    }
    
    if (keyword == "class")
    {
        //TODO: Return class token
    }

    if (keyword == "public")
    {
        //TODO: Return public token
    }

    if (keyword == "private")
    {
        //TODO: Return private token
    }

    return nullptr;
}