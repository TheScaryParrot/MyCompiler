#pragma once

#include <string>

#include "AbstractKeywordToken.cpp"

static class Keywords {
public:
    // Deletion of the pointers is handled by TokenList.cpp. Because for NotConstTokens, we need to delete all instances of them

    AbstractKeywordToken* IF_KEYWORD = new AbstractKeywordToken("if");
    AbstractKeywordToken* ELSE_KEYWORD = new AbstractKeywordToken("else");
    AbstractKeywordToken* ELIF_KEYWORD = new AbstractKeywordToken("elif");

    AbstractKeywordToken* WHILE_KEYWORD = new AbstractKeywordToken("while");
    AbstractKeywordToken* FOR_KEYWORD = new AbstractKeywordToken("for");
    AbstractKeywordToken* BREAK_KEYWORD = new AbstractKeywordToken("break");
    AbstractKeywordToken* CONTINUE_KEYWORD = new AbstractKeywordToken("continue");

    AbstractKeywordToken* LOGICAL_TRUE_KEYWORD = new AbstractKeywordToken("true");
    AbstractKeywordToken* LOGICAL_FALSE_KEYWORD = new AbstractKeywordToken("false");

    AbstractKeywordToken* RETURN_KEYWORD = new AbstractKeywordToken("return");
    AbstractKeywordToken* VOID_KEYWORD = new AbstractKeywordToken("void");

    AbstractKeywordToken* CLASS_KEYWORD = new AbstractKeywordToken("class");
    AbstractKeywordToken* PUBLIC_KEYWORD = new AbstractKeywordToken("public");
    AbstractKeywordToken* PRIVATE_KEYWORD = new AbstractKeywordToken("private");
    AbstractKeywordToken* PROTECTED_KEYWORD = new AbstractKeywordToken("protected");
    AbstractKeywordToken* STATIC_KEYWORD = new AbstractKeywordToken("static");
    AbstractKeywordToken* CONST_KEYWORD = new AbstractKeywordToken("const");
    AbstractKeywordToken* READ_ONLY_KEYWORD = new AbstractKeywordToken("readonly");


    /// @brief Returns the token for the given keyword. If the keyword is not a keyword, returns nullptr.
    AbstractKeywordToken* GetKeywordToken(std::string keyword);
}Keywords;

AbstractKeywordToken* Keywords::GetKeywordToken(std::string keyword) {
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