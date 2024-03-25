#pragma once

#include <string>

#include "AbstractKeywordToken.cpp"

static class Keywords {
public:
    AbstractKeywordToken IF_KEYWORD = AbstractKeywordToken("if");
    AbstractKeywordToken ELSE_KEYWORD = AbstractKeywordToken("else");
    AbstractKeywordToken ELIF_KEYWORD = AbstractKeywordToken("elif");

    AbstractKeywordToken WHILE_KEYWORD = AbstractKeywordToken("while");
    AbstractKeywordToken FOR_KEYWORD = AbstractKeywordToken("for");
    AbstractKeywordToken BREAK_KEYWORD = AbstractKeywordToken("break");
    AbstractKeywordToken CONTINUE_KEYWORD = AbstractKeywordToken("continue");

    AbstractKeywordToken LOGICAL_TRUE_KEYWORD = AbstractKeywordToken("true");
    AbstractKeywordToken LOGICAL_FALSE_KEYWORD = AbstractKeywordToken("false");

    AbstractKeywordToken RETURN_KEYWORD = AbstractKeywordToken("return");
    AbstractKeywordToken VOID_KEYWORD = AbstractKeywordToken("void");

    AbstractKeywordToken CLASS_KEYWORD = AbstractKeywordToken("class");
    AbstractKeywordToken PUBLIC_KEYWORD = AbstractKeywordToken("public");
    AbstractKeywordToken PRIVATE_KEYWORD = AbstractKeywordToken("private");
    AbstractKeywordToken PROTECTED_KEYWORD = AbstractKeywordToken("protected");
    AbstractKeywordToken STATIC_KEYWORD = AbstractKeywordToken("static");
    AbstractKeywordToken CONST_KEYWORD = AbstractKeywordToken("const");
    AbstractKeywordToken READ_ONLY_KEYWORD = AbstractKeywordToken("readonly");


    /// @brief Returns the token for the given keyword. If the keyword is not a keyword, returns nullptr.
    AbstractKeywordToken* GetKeywordToken(std::string keyword);
}Keywords;

AbstractKeywordToken* Keywords::GetKeywordToken(std::string keyword) {
    if (IF_KEYWORD.IsThisKeyword(keyword)) {
        return &IF_KEYWORD;
    }

    if (ELSE_KEYWORD.IsThisKeyword(keyword)) {
        return &ELSE_KEYWORD;
    }

    if (ELIF_KEYWORD.IsThisKeyword(keyword)) {
        return &ELIF_KEYWORD;
    }

    if (WHILE_KEYWORD.IsThisKeyword(keyword)) {
        return &WHILE_KEYWORD;
    }

    if (FOR_KEYWORD.IsThisKeyword(keyword)) {
        return &FOR_KEYWORD;
    }

    if (BREAK_KEYWORD.IsThisKeyword(keyword)) {
        return &BREAK_KEYWORD;
    }

    if (CONTINUE_KEYWORD.IsThisKeyword(keyword)) {
        return &CONTINUE_KEYWORD;
    }

    if (LOGICAL_TRUE_KEYWORD.IsThisKeyword(keyword)) {
        return &LOGICAL_TRUE_KEYWORD;
    }

    if (LOGICAL_FALSE_KEYWORD.IsThisKeyword(keyword)) {
        return &LOGICAL_FALSE_KEYWORD;
    }

    if (RETURN_KEYWORD.IsThisKeyword(keyword)) {
        return &RETURN_KEYWORD;
    }

    if (VOID_KEYWORD.IsThisKeyword(keyword)) {
        return &VOID_KEYWORD;
    }

    if (CLASS_KEYWORD.IsThisKeyword(keyword)) {
        return &CLASS_KEYWORD;
    }

    if (PUBLIC_KEYWORD.IsThisKeyword(keyword)) {
        return &PUBLIC_KEYWORD;
    }

    if (PRIVATE_KEYWORD.IsThisKeyword(keyword)) {
        return &PRIVATE_KEYWORD;
    }

    if (PROTECTED_KEYWORD.IsThisKeyword(keyword)) {
        return &PROTECTED_KEYWORD;
    }

    if (STATIC_KEYWORD.IsThisKeyword(keyword)) {
        return &STATIC_KEYWORD;
    }

    if (CONST_KEYWORD.IsThisKeyword(keyword)) {
        return &CONST_KEYWORD;
    }

    if (READ_ONLY_KEYWORD.IsThisKeyword(keyword)) {
        return &READ_ONLY_KEYWORD;
    }

    return nullptr;
}