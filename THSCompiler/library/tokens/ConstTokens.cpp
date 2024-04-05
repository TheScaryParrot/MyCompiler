#pragma once

#include "AbstractToken.cpp"
#include "notConstTokens/IdentifierToken.cpp"
#include "notConstTokens/NumberConstToken.cpp"
#include "notConstTokens/StringConstToken.cpp"
#include "characterGroups/CharacterGroups.cpp"

static class ConstTokens {
public:
    std::shared_ptr<AbstractToken> STATEMENT_END_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("statementEnd", CharacterGroups.STATEMENT_END));
    std::shared_ptr<AbstractToken> PARENTHESIS_OPEN_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("parenthesisOpen", CharacterGroups.PARENTHESIS_OPEN));
    std::shared_ptr<AbstractToken> PARENTHESIS_CLOSE_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("parenthesisClose", CharacterGroups.PARENTHESIS_CLOSE));
    std::shared_ptr<AbstractToken> BODY_OPEN_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("bodyOpen", CharacterGroups.BODY_OPEN));
    std::shared_ptr<AbstractToken> BODY_CLOSE_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("bodyClose", CharacterGroups.BODY_CLOSE));
    std::shared_ptr<AbstractToken> SEPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("seperator", CharacterGroups.SEPERATOR));

    std::shared_ptr<AbstractToken> EQUAL_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("equalOperator", CharacterGroups.EQUAL_OPERATOR));
    std::shared_ptr<AbstractToken> NOT_EQUAL_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("notEqualOperator", CharacterGroups.NOT_EQUAL_OPERATOR));
    std::shared_ptr<AbstractToken> LESS_THAN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("lessThanOperator", CharacterGroups.LESS_THAN_OPERATOR));
    std::shared_ptr<AbstractToken> GREATER_THAN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("greaterThanOperator", CharacterGroups.GREATER_THAN_OPERATOR));
    std::shared_ptr<AbstractToken> LESS_THAN_OR_EQUAL_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("lessThanOrEqualOperator", CharacterGroups.LESS_THAN_OR_EQUAL_OPERATOR));
    std::shared_ptr<AbstractToken> GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("greaterThanOrEqualOperator", CharacterGroups.GREATER_THAN_OR_EQUAL_OPERATOR));

    std::shared_ptr<AbstractToken> ADD_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("addOperator", CharacterGroups.ADD_OPERATOR));
    std::shared_ptr<AbstractToken> SUB_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("subOperator", CharacterGroups.SUB_OPERATOR));
    std::shared_ptr<AbstractToken> MUL_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("mulOperator", CharacterGroups.MUL_OPERATOR));
    std::shared_ptr<AbstractToken> DIV_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("divOperator", CharacterGroups.DIV_OPERATOR));
    std::shared_ptr<AbstractToken> MOD_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("modOperator", CharacterGroups.MOD_OPERATOR));

    std::shared_ptr<AbstractToken> ASSIGN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("assignOperator", CharacterGroups.ASSIGN_OPERATOR));
    std::shared_ptr<AbstractToken> ADD_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("addAssignOperator", CharacterGroups.ADD_ASSIGN_OPERATOR));
    std::shared_ptr<AbstractToken> SUB_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("subAssignOperator", CharacterGroups.SUB_ASSIGN_OPERATOR));
    std::shared_ptr<AbstractToken> MUL_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("mulAssignOperator", CharacterGroups.MUL_ASSIGN_OPERATOR));
    std::shared_ptr<AbstractToken> DIV_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("divAssignOperator", CharacterGroups.DIV_ASSIGN_OPERATOR));
    std::shared_ptr<AbstractToken> MOD_ASSIGN_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("modAssignOperator", CharacterGroups.MOD_ASSIGN_OPERATOR));

    std::shared_ptr<AbstractToken> INCREMENT_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("incrementOperator", CharacterGroups.INCREMENT_OPERATOR));
    std::shared_ptr<AbstractToken> DECREMENT_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("decrementOperator", CharacterGroups.DECREMENT_OPERATOR)); 

    std::shared_ptr<AbstractToken> NEGATE_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("negateOperator", CharacterGroups.NEGATE_OPERATOR));
    
    std::shared_ptr<AbstractToken> NOT_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("notOperator", CharacterGroups.NOT_OPERATOR));
    std::shared_ptr<AbstractToken> AND_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("andOperator", CharacterGroups.AND_OPERATOR));
    std::shared_ptr<AbstractToken> OR_OPERATOR_TOKEN = std::shared_ptr<AbstractToken>(new AbstractToken("orOperator", CharacterGroups.OR_OPERATOR));

    /* ----- Const version of Not Constant Tokens (IdentifierToken, NumberToken, StringToken...) -----
        Their main usage is for their IsThisToken method. Which cannot be used static*/
    std::shared_ptr<IdentifierToken> CONST_IDENTIFIER_TOKEN = std::shared_ptr<IdentifierToken>(new IdentifierToken(""));
    std::shared_ptr<NumberConstToken> CONST_NUMBER_TOKEN = std::shared_ptr<NumberConstToken>(new NumberConstToken("0"));
    std::shared_ptr<StringConstToken> CONST_STRING_TOKEN = std::shared_ptr<StringConstToken>(new StringConstToken(""));

}ConstTokens;