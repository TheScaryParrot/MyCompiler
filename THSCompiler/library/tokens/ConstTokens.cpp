#pragma once

#include "AbstractToken.cpp"
#include "notConstTokens/IdentifierToken.cpp"
#include "notConstTokens/NumberConstToken.cpp"
#include "notConstTokens/StringConstToken.cpp"
#include "characterGroups/CharacterGroups.cpp"

static class ConstTokens {
public:
    // Deletion of the pointers is handled by TokenList.cpp. Because for NotConstTokens, we need to delete all instances of them

    AbstractToken* STATEMENT_END_TOKEN = new AbstractToken("statementEnd", CharacterGroups.STATEMENT_END);
    AbstractToken* PARENTHESIS_OPEN_TOKEN = new AbstractToken("parenthesisOpen", CharacterGroups.PARENTHESIS_OPEN);
    AbstractToken* PARENTHESIS_CLOSE_TOKEN = new AbstractToken("parenthesisClose", CharacterGroups.PARENTHESIS_CLOSE);
    AbstractToken* BODY_OPEN_TOKEN = new AbstractToken("bodyOpen", CharacterGroups.BODY_OPEN);
    AbstractToken* BODY_CLOSE_TOKEN = new AbstractToken("bodyClose", CharacterGroups.BODY_CLOSE);
    AbstractToken* SEPERATOR_TOKEN = new AbstractToken("seperator", CharacterGroups.SEPERATOR);

    AbstractToken* EQUAL_OPERATOR_TOKEN = new AbstractToken("equalOperator", CharacterGroups.EQUAL_OPERATOR);
    AbstractToken* NOT_EQUAL_OPERATOR_TOKEN = new AbstractToken("notEqualOperator", CharacterGroups.NOT_EQUAL_OPERATOR);
    AbstractToken* LESS_THAN_OPERATOR_TOKEN = new AbstractToken("lessThanOperator", CharacterGroups.LESS_THAN_OPERATOR);
    AbstractToken* GREATER_THAN_OPERATOR_TOKEN = new AbstractToken("greaterThanOperator", CharacterGroups.GREATER_THAN_OPERATOR);
    AbstractToken* LESS_THAN_OR_EQUAL_OPERATOR_TOKEN = new AbstractToken("lessThanOrEqualOperator", CharacterGroups.LESS_THAN_OR_EQUAL_OPERATOR);
    AbstractToken* GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN = new AbstractToken("greaterThanOrEqualOperator", CharacterGroups.GREATER_THAN_OR_EQUAL_OPERATOR);

    AbstractToken* ADD_OPERATOR_TOKEN = new AbstractToken("addOperator", CharacterGroups.ADD_OPERATOR);
    AbstractToken* SUB_OPERATOR_TOKEN = new AbstractToken("subOperator", CharacterGroups.SUB_OPERATOR);
    AbstractToken* MUL_OPERATOR_TOKEN = new AbstractToken("mulOperator", CharacterGroups.MUL_OPERATOR);
    AbstractToken* DIV_OPERATOR_TOKEN = new AbstractToken("divOperator", CharacterGroups.DIV_OPERATOR);
    AbstractToken* MOD_OPERATOR_TOKEN = new AbstractToken("modOperator", CharacterGroups.MOD_OPERATOR);

    AbstractToken* ASSIGN_OPERATOR_TOKEN = new AbstractToken("assignOperator", CharacterGroups.ASSIGN_OPERATOR);
    AbstractToken* ADD_ASSIGN_OPERATOR_TOKEN = new AbstractToken("addAssignOperator", CharacterGroups.ADD_ASSIGN_OPERATOR);
    AbstractToken* SUB_ASSIGN_OPERATOR_TOKEN = new AbstractToken("subAssignOperator", CharacterGroups.SUB_ASSIGN_OPERATOR);
    AbstractToken* MUL_ASSIGN_OPERATOR_TOKEN = new AbstractToken("mulAssignOperator", CharacterGroups.MUL_ASSIGN_OPERATOR);
    AbstractToken* DIV_ASSIGN_OPERATOR_TOKEN = new AbstractToken("divAssignOperator", CharacterGroups.DIV_ASSIGN_OPERATOR);
    AbstractToken* MOD_ASSIGN_OPERATOR_TOKEN = new AbstractToken("modAssignOperator", CharacterGroups.MOD_ASSIGN_OPERATOR);

    AbstractToken* INCREMENT_OPERATOR_TOKEN = new AbstractToken("incrementOperator", CharacterGroups.INCREMENT_OPERATOR);
    AbstractToken* DECREMENT_OPERATOR_TOKEN = new AbstractToken("decrementOperator", CharacterGroups.DECREMENT_OPERATOR); 

    AbstractToken* NEGATE_OPERATOR_TOKEN = new AbstractToken("negateOperator", CharacterGroups.NEGATE_OPERATOR);
    
    AbstractToken* NOT_OPERATOR_TOKEN = new AbstractToken("notOperator", CharacterGroups.NOT_OPERATOR);
    AbstractToken* AND_OPERATOR_TOKEN = new AbstractToken("andOperator", CharacterGroups.AND_OPERATOR);
    AbstractToken* OR_OPERATOR_TOKEN = new AbstractToken("orOperator", CharacterGroups.OR_OPERATOR);

    /* ----- Const version of Not Constant Tokens (IdentifierToken, NumberToken, StringToken...) -----
        Their main usage is for their IsThisToken method. Which cannot be used static*/
    IdentifierToken* CONST_IDENTIFIER_TOKEN = new IdentifierToken("");
    NumberConstToken* CONST_NUMBER_TOKEN = new NumberConstToken("0");
    StringConstToken* CONST_STRING_TOKEN = new StringConstToken("");

}ConstTokens;