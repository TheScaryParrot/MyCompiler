#pragma once

#include <string>

#include "AbstractKeywordToken.cpp"

static class Keywords {
public:
    std::shared_ptr<AbstractKeywordToken> IF_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("if"));
    std::shared_ptr<AbstractKeywordToken> ELSE_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("else"));
    std::shared_ptr<AbstractKeywordToken> ELIF_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("elif"));

    std::shared_ptr<AbstractKeywordToken> WHILE_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("while"));
    std::shared_ptr<AbstractKeywordToken> FOR_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("for"));
    std::shared_ptr<AbstractKeywordToken> BREAK_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("break"));
    std::shared_ptr<AbstractKeywordToken> CONTINUE_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("continue"));

    std::shared_ptr<AbstractKeywordToken> LOGICAL_TRUE_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("true"));
    std::shared_ptr<AbstractKeywordToken> LOGICAL_FALSE_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("false"));

    std::shared_ptr<AbstractKeywordToken> RETURN_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("return"));
    std::shared_ptr<AbstractKeywordToken> VOID_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("void"));

    std::shared_ptr<AbstractKeywordToken> CLASS_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("class"));
    std::shared_ptr<AbstractKeywordToken> PUBLIC_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("public"));
    std::shared_ptr<AbstractKeywordToken> PRIVATE_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("private"));
    std::shared_ptr<AbstractKeywordToken> PROTECTED_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("protected"));
    std::shared_ptr<AbstractKeywordToken> STATIC_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("static"));
    std::shared_ptr<AbstractKeywordToken> CONST_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("const"));
    std::shared_ptr<AbstractKeywordToken> READ_ONLY_KEYWORD = std::shared_ptr<AbstractKeywordToken>(new AbstractKeywordToken("readonly"));


    /// @brief Returns the token for the given keyword. If the keyword is not a keyword, returns nullptr.
    std::shared_ptr<AbstractKeywordToken> GetKeywordToken(std::string keyword);
}Keywords;

std::shared_ptr<AbstractKeywordToken> Keywords::GetKeywordToken(std::string keyword) {
    if (IF_KEYWORD->IsThisKeyword(keyword)) {
        return IF_KEYWORD;
    }

    if (ELSE_KEYWORD->IsThisKeyword(keyword)) {
        return ELSE_KEYWORD;
    }

    if (ELIF_KEYWORD->IsThisKeyword(keyword)) {
        return ELIF_KEYWORD;
    }

    if (WHILE_KEYWORD->IsThisKeyword(keyword)) {
        return WHILE_KEYWORD;
    }

    if (FOR_KEYWORD->IsThisKeyword(keyword)) {
        return FOR_KEYWORD;
    }

    if (BREAK_KEYWORD->IsThisKeyword(keyword)) {
        return BREAK_KEYWORD;
    }

    if (CONTINUE_KEYWORD->IsThisKeyword(keyword)) {
        return CONTINUE_KEYWORD;
    }

    if (LOGICAL_TRUE_KEYWORD->IsThisKeyword(keyword)) {
        return LOGICAL_TRUE_KEYWORD;
    }

    if (LOGICAL_FALSE_KEYWORD->IsThisKeyword(keyword)) {
        return LOGICAL_FALSE_KEYWORD;
    }

    if (RETURN_KEYWORD->IsThisKeyword(keyword)) {
        return RETURN_KEYWORD;
    }

    if (VOID_KEYWORD->IsThisKeyword(keyword)) {
        return VOID_KEYWORD;
    }

    if (CLASS_KEYWORD->IsThisKeyword(keyword)) {
        return CLASS_KEYWORD;
    }

    if (PUBLIC_KEYWORD->IsThisKeyword(keyword)) {
        return PUBLIC_KEYWORD;
    }

    if (PRIVATE_KEYWORD->IsThisKeyword(keyword)) {
        return PRIVATE_KEYWORD;
    }

    if (PROTECTED_KEYWORD->IsThisKeyword(keyword)) {
        return PROTECTED_KEYWORD;
    }

    if (STATIC_KEYWORD->IsThisKeyword(keyword)) {
        return STATIC_KEYWORD;
    }

    if (CONST_KEYWORD->IsThisKeyword(keyword)) {
        return CONST_KEYWORD;
    }

    if (READ_ONLY_KEYWORD->IsThisKeyword(keyword)) {
        return READ_ONLY_KEYWORD;
    }

    return nullptr;
}