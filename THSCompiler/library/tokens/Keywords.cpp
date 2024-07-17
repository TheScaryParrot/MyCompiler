#pragma once

#include <string>

#include "AbstractKeywordToken.cpp"

static class Keywords
{
   public:
    std::shared_ptr<AbstractKeywordToken> IF_KEYWORD = std::make_shared<AbstractKeywordToken>("if");
    std::shared_ptr<AbstractKeywordToken> ELSE_KEYWORD = std::make_shared<AbstractKeywordToken>("else");
    std::shared_ptr<AbstractKeywordToken> ELIF_KEYWORD = std::make_shared<AbstractKeywordToken>("elif");

    std::shared_ptr<AbstractKeywordToken> WHILE_KEYWORD = std::make_shared<AbstractKeywordToken>("while");
    std::shared_ptr<AbstractKeywordToken> FOR_KEYWORD = std::make_shared<AbstractKeywordToken>("for");
    std::shared_ptr<AbstractKeywordToken> BREAK_KEYWORD = std::make_shared<AbstractKeywordToken>("break");
    std::shared_ptr<AbstractKeywordToken> CONTINUE_KEYWORD = std::make_shared<AbstractKeywordToken>("continue");

    std::shared_ptr<AbstractKeywordToken> LOGICAL_TRUE_KEYWORD = std::make_shared<AbstractKeywordToken>("true");
    std::shared_ptr<AbstractKeywordToken> LOGICAL_FALSE_KEYWORD = std::make_shared<AbstractKeywordToken>("false");

    std::shared_ptr<AbstractKeywordToken> RETURN_KEYWORD = std::make_shared<AbstractKeywordToken>("return");
    std::shared_ptr<AbstractKeywordToken> VOID_KEYWORD = std::make_shared<AbstractKeywordToken>("void");

    std::shared_ptr<AbstractKeywordToken> FINAL_KEYWORD = std::make_shared<AbstractKeywordToken>("final");
    std::shared_ptr<AbstractKeywordToken> INLINE_KEYWORD = std::make_shared<AbstractKeywordToken>("inline");

    std::shared_ptr<AbstractKeywordToken> TYPEDEF_KEYWORD = std::make_shared<AbstractKeywordToken>("typedef");

    /// @brief Returns the token for the given keyword. If the keyword is not a keyword, returns nullptr.
    std::shared_ptr<AbstractKeywordToken> GetKeywordToken(std::string keyword);
} Keywords;

std::shared_ptr<AbstractKeywordToken> Keywords::GetKeywordToken(std::string keyword)
{
    if (IF_KEYWORD->IsThisKeyword(keyword))
    {
        return IF_KEYWORD;
    }

    if (ELSE_KEYWORD->IsThisKeyword(keyword))
    {
        return ELSE_KEYWORD;
    }

    if (ELIF_KEYWORD->IsThisKeyword(keyword))
    {
        return ELIF_KEYWORD;
    }

    if (WHILE_KEYWORD->IsThisKeyword(keyword))
    {
        return WHILE_KEYWORD;
    }

    if (FOR_KEYWORD->IsThisKeyword(keyword))
    {
        return FOR_KEYWORD;
    }

    if (BREAK_KEYWORD->IsThisKeyword(keyword))
    {
        return BREAK_KEYWORD;
    }

    if (CONTINUE_KEYWORD->IsThisKeyword(keyword))
    {
        return CONTINUE_KEYWORD;
    }

    if (LOGICAL_TRUE_KEYWORD->IsThisKeyword(keyword))
    {
        return LOGICAL_TRUE_KEYWORD;
    }

    if (LOGICAL_FALSE_KEYWORD->IsThisKeyword(keyword))
    {
        return LOGICAL_FALSE_KEYWORD;
    }

    if (RETURN_KEYWORD->IsThisKeyword(keyword))
    {
        return RETURN_KEYWORD;
    }

    if (VOID_KEYWORD->IsThisKeyword(keyword))
    {
        return VOID_KEYWORD;
    }

    if (FINAL_KEYWORD->IsThisKeyword(keyword))
    {
        return FINAL_KEYWORD;
    }

    if (INLINE_KEYWORD->IsThisKeyword(keyword))
    {
        return INLINE_KEYWORD;
    }

    if (TYPEDEF_KEYWORD->IsThisKeyword(keyword))
    {
        return TYPEDEF_KEYWORD;
    }

    return nullptr;
}