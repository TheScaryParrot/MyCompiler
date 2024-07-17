#pragma once

#include "CharacterGroupToken.cpp"
#include "TokenWithValue.cpp"
#include "characterGroups/CharacterGroups.cpp"

static class Tokens
{
   public:
    std::shared_ptr<CharacterGroupToken> STATEMENT_END_TOKEN = std::make_shared<CharacterGroupToken>("statementEnd", CharacterGroups.STATEMENT_END);
    std::shared_ptr<CharacterGroupToken> PARENTHESIS_OPEN_TOKEN =
        std::make_shared<CharacterGroupToken>("parenthesisOpen", CharacterGroups.PARENTHESIS_OPEN);
    std::shared_ptr<CharacterGroupToken> PARENTHESIS_CLOSE_TOKEN =
        std::make_shared<CharacterGroupToken>("parenthesisClose", CharacterGroups.PARENTHESIS_CLOSE);
    std::shared_ptr<CharacterGroupToken> BODY_OPEN_TOKEN = std::make_shared<CharacterGroupToken>("bracesOpen", CharacterGroups.BRACES_OPEN);
    std::shared_ptr<CharacterGroupToken> BODY_CLOSE_TOKEN = std::make_shared<CharacterGroupToken>("bracesClose", CharacterGroups.BRACES_CLOSE);
    std::shared_ptr<CharacterGroupToken> SEPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("seperator", CharacterGroups.SEPERATOR);

    std::shared_ptr<CharacterGroupToken> EQUAL_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("equalOperator", CharacterGroups.EQUAL_OPERATOR);
    std::shared_ptr<CharacterGroupToken> NOT_EQUAL_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("notEqualOperator", CharacterGroups.NOT_EQUAL_OPERATOR);
    std::shared_ptr<CharacterGroupToken> LESS_THAN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("lessThanOperator", CharacterGroups.LESS_THAN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> GREATER_THAN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("greaterThanOperator", CharacterGroups.GREATER_THAN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> LESS_THAN_OR_EQUAL_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("lessThanOrEqualOperator", CharacterGroups.LESS_THAN_OR_EQUAL_OPERATOR);
    std::shared_ptr<CharacterGroupToken> GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("greaterThanOrEqualOperator", CharacterGroups.GREATER_THAN_OR_EQUAL_OPERATOR);

    std::shared_ptr<CharacterGroupToken> ADD_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("addOperator", CharacterGroups.ADD_OPERATOR);
    std::shared_ptr<CharacterGroupToken> SUB_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("subOperator", CharacterGroups.SUB_OPERATOR);
    std::shared_ptr<CharacterGroupToken> MUL_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("mulOperator", CharacterGroups.MUL_OPERATOR);
    std::shared_ptr<CharacterGroupToken> DIV_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("divOperator", CharacterGroups.DIV_OPERATOR);
    std::shared_ptr<CharacterGroupToken> MOD_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("modOperator", CharacterGroups.MOD_OPERATOR);

    std::shared_ptr<CharacterGroupToken> ASSIGN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("assignOperator", CharacterGroups.ASSIGN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> ADD_ASSIGN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("addAssignOperator", CharacterGroups.ADD_ASSIGN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> SUB_ASSIGN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("subAssignOperator", CharacterGroups.SUB_ASSIGN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> MUL_ASSIGN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("mulAssignOperator", CharacterGroups.MUL_ASSIGN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> DIV_ASSIGN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("divAssignOperator", CharacterGroups.DIV_ASSIGN_OPERATOR);
    std::shared_ptr<CharacterGroupToken> MOD_ASSIGN_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("modAssignOperator", CharacterGroups.MOD_ASSIGN_OPERATOR);

    std::shared_ptr<CharacterGroupToken> INCREMENT_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("incrementOperator", CharacterGroups.INCREMENT_OPERATOR);
    std::shared_ptr<CharacterGroupToken> DECREMENT_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("decrementOperator", CharacterGroups.DECREMENT_OPERATOR);

    std::shared_ptr<CharacterGroupToken> NEGATE_OPERATOR_TOKEN =
        std::make_shared<CharacterGroupToken>("negateOperator", CharacterGroups.NEGATE_OPERATOR);

    std::shared_ptr<CharacterGroupToken> NOT_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("notOperator", CharacterGroups.NOT_OPERATOR);
    std::shared_ptr<CharacterGroupToken> AND_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("andOperator", CharacterGroups.AND_OPERATOR);
    std::shared_ptr<CharacterGroupToken> OR_OPERATOR_TOKEN = std::make_shared<CharacterGroupToken>("orOperator", CharacterGroups.OR_OPERATOR);

    std::shared_ptr<CharacterGroupToken> DOT_TOKEN = std::make_shared<CharacterGroupToken>("dot", CharacterGroups.DOT);

    /* ----- Const version of Not Constant Tokens (IdentifierToken, NumberToken, StringToken...) -----
        Their main usage is for their IsThisToken method. Which cannot be used static*/
    std::shared_ptr<TokenWithValue> CONST_IDENTIFIER_TOKEN = std::shared_ptr<TokenWithValue>(new TokenWithValue("idToken", ""));
    std::shared_ptr<TokenWithValue> CONST_INT_TOKEN = std::shared_ptr<TokenWithValue>(new TokenWithValue("intToken", "0"));
    std::shared_ptr<TokenWithValue> CONST_FLOAT_TOKEN = std::shared_ptr<TokenWithValue>(new TokenWithValue("floatToken", "0.0"));
    std::shared_ptr<TokenWithValue> CONST_STRING_TOKEN = std::shared_ptr<TokenWithValue>(new TokenWithValue("stringToken", ""));

} Tokens;