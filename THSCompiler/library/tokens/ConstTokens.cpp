#pragma once

#include "CharacterGroupToken.cpp"
#include "characterGroups/CharacterGroups.cpp"
#include "notConstTokens/IdentifierToken.cpp"
#include "notConstTokens/NumberConstToken.cpp"
#include "notConstTokens/StringConstToken.cpp"

static class ConstTokens
{
   public:
    std::shared_ptr<CharacterGroupToken> PARENTHESIS_OPEN_TOKEN =
        std::make_shared<CharacterGroupToken>("parenthesisOpen", CharacterGroups.PARENTHESIS_OPEN);
    std::shared_ptr<CharacterGroupToken> PARENTHESIS_CLOSE_TOKEN =
        std::make_shared<CharacterGroupToken>("parenthesisClose", CharacterGroups.PARENTHESIS_CLOSE);
    std::shared_ptr<CharacterGroupToken> BRACES_OPEN_TOKEN =
        std::make_shared<CharacterGroupToken>("bodyOpen", CharacterGroups.BRACES_OPEN);
    std::shared_ptr<CharacterGroupToken> BRACES_CLOSE_TOKEN =
        std::make_shared<CharacterGroupToken>("bodyClose", CharacterGroups.BRACES_CLOSE);
    std::shared_ptr<CharacterGroupToken> BRACKETS_OPEN_TOKEN =
        std::make_shared<CharacterGroupToken>("bracketsOpen", CharacterGroups.BRACKETS_OPEN);
    std::shared_ptr<CharacterGroupToken> BRACKETS_CLOSE_TOKEN =
        std::make_shared<CharacterGroupToken>("bracketsClose", CharacterGroups.BRACKETS_CLOSE);
    std::shared_ptr<CharacterGroupToken> SEPARATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("separator", CharacterGroups.SEPARATOR);

    /* ----- Const version of Not Constant Tokens (IdentifierToken, NumberToken, StringToken...) -----
        Their main usage is for their IsThisToken method. Which cannot be used static*/
    std::shared_ptr<IdentifierToken> CONST_IDENTIFIER_TOKEN = std::make_shared<IdentifierToken>("");
    std::shared_ptr<NumberConstToken> CONST_NUMBER_TOKEN = std::make_shared<NumberConstToken>("");
    std::shared_ptr<StringConstToken> CONST_STRING_TOKEN = std::make_shared<StringConstToken>("");

} ConstTokens;