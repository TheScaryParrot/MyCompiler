#pragma once

#include "CharacterGroupToken.cpp"
#include "notConstTokens/IdentifierToken.cpp"
#include "notConstTokens/NumberConstToken.cpp"
#include "notConstTokens/StringConstToken.cpp"
#include "characterGroups/CharacterGroups.cpp"

static class ConstTokens {
public:
    std::shared_ptr<CharacterGroupToken> STATEMENT_END_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("statementEnd", CharacterGroups.STATEMENT_END));
    std::shared_ptr<CharacterGroupToken> PARENTHESIS_OPEN_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("parenthesisOpen", CharacterGroups.PARENTHESIS_OPEN));
    std::shared_ptr<CharacterGroupToken> PARENTHESIS_CLOSE_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("parenthesisClose", CharacterGroups.PARENTHESIS_CLOSE));
    std::shared_ptr<CharacterGroupToken> BODY_OPEN_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("bodyOpen", CharacterGroups.BODY_OPEN));
    std::shared_ptr<CharacterGroupToken> BODY_CLOSE_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("bodyClose", CharacterGroups.BODY_CLOSE));
    std::shared_ptr<CharacterGroupToken> SEPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("seperator", CharacterGroups.SEPERATOR));

    std::shared_ptr<CharacterGroupToken> EQUAL_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("equalOperator", CharacterGroups.EQUAL_OPERATOR));
    std::shared_ptr<CharacterGroupToken> NOT_EQUAL_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("notEqualOperator", CharacterGroups.NOT_EQUAL_OPERATOR));
    std::shared_ptr<CharacterGroupToken> LESS_THAN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("lessThanOperator", CharacterGroups.LESS_THAN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> GREATER_THAN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("greaterThanOperator", CharacterGroups.GREATER_THAN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> LESS_THAN_OR_EQUAL_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("lessThanOrEqualOperator", CharacterGroups.LESS_THAN_OR_EQUAL_OPERATOR));
    std::shared_ptr<CharacterGroupToken> GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("greaterThanOrEqualOperator", CharacterGroups.GREATER_THAN_OR_EQUAL_OPERATOR));

    std::shared_ptr<CharacterGroupToken> ADD_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("addOperator", CharacterGroups.ADD_OPERATOR));
    std::shared_ptr<CharacterGroupToken> SUB_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("subOperator", CharacterGroups.SUB_OPERATOR));
    std::shared_ptr<CharacterGroupToken> MUL_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("mulOperator", CharacterGroups.MUL_OPERATOR));
    std::shared_ptr<CharacterGroupToken> DIV_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("divOperator", CharacterGroups.DIV_OPERATOR));
    std::shared_ptr<CharacterGroupToken> MOD_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("modOperator", CharacterGroups.MOD_OPERATOR));

    std::shared_ptr<CharacterGroupToken> ASSIGN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("assignOperator", CharacterGroups.ASSIGN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> ADD_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("addAssignOperator", CharacterGroups.ADD_ASSIGN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> SUB_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("subAssignOperator", CharacterGroups.SUB_ASSIGN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> MUL_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("mulAssignOperator", CharacterGroups.MUL_ASSIGN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> DIV_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("divAssignOperator", CharacterGroups.DIV_ASSIGN_OPERATOR));
    std::shared_ptr<CharacterGroupToken> MOD_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("modAssignOperator", CharacterGroups.MOD_ASSIGN_OPERATOR));

    std::shared_ptr<CharacterGroupToken> INCREMENT_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("incrementOperator", CharacterGroups.INCREMENT_OPERATOR));
    std::shared_ptr<CharacterGroupToken> DECREMENT_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("decrementOperator", CharacterGroups.DECREMENT_OPERATOR)); 

    std::shared_ptr<CharacterGroupToken> NEGATE_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("negateOperator", CharacterGroups.NEGATE_OPERATOR));
    
    std::shared_ptr<CharacterGroupToken> NOT_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("notOperator", CharacterGroups.NOT_OPERATOR));
    std::shared_ptr<CharacterGroupToken> AND_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("andOperator", CharacterGroups.AND_OPERATOR));
    std::shared_ptr<CharacterGroupToken> OR_OPERATOR_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("orOperator", CharacterGroups.OR_OPERATOR));

    std::shared_ptr<CharacterGroupToken> DOT_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("dot", CharacterGroups.DOT));
    std::shared_ptr<CharacterGroupToken> COLON_TOKEN = std::shared_ptr<CharacterGroupToken>(new CharacterGroupToken("colon", CharacterGroups.COLON));

    /* ----- Const version of Not Constant Tokens (IdentifierToken, NumberToken, StringToken...) -----
        Their main usage is for their IsThisToken method. Which cannot be used static*/
    std::shared_ptr<IdentifierToken> CONST_IDENTIFIER_TOKEN = std::shared_ptr<IdentifierToken>(new IdentifierToken(""));
    std::shared_ptr<NumberConstToken> CONST_NUMBER_TOKEN = std::shared_ptr<NumberConstToken>(new NumberConstToken("0"));
    std::shared_ptr<StringConstToken> CONST_STRING_TOKEN = std::shared_ptr<StringConstToken>(new StringConstToken(""));

}ConstTokens;