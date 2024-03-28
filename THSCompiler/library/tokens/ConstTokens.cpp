#pragma once

#include "AbstractToken.cpp"
#include "characterGroups/CharacterGroups.cpp"

static class ConstTokens {
public:
    AbstractToken STATEMENT_END_TOKEN = AbstractToken("statementEnd", &CharacterGroups.STATEMENT_END);
    AbstractToken PARENTHESIS_OPEN_TOKEN = AbstractToken("parenthesisOpen", &CharacterGroups.PARENTHESIS_OPEN);
    AbstractToken PARENTHESIS_CLOSE_TOKEN = AbstractToken("parenthesisClose", &CharacterGroups.PARENTHESIS_CLOSE);
    AbstractToken BODY_OPEN_TOKEN = AbstractToken("bodyOpen", &CharacterGroups.BODY_OPEN);
    AbstractToken BODY_CLOSE_TOKEN = AbstractToken("bodyClose", &CharacterGroups.BODY_CLOSE);
    AbstractToken SEPERATOR_TOKEN = AbstractToken("seperator", &CharacterGroups.SEPERATOR);

    AbstractToken EQUAL_OPERATOR_TOKEN = AbstractToken("equalOperator", &CharacterGroups.EQUAL_OPERATOR);
    AbstractToken NOT_EQUAL_OPERATOR_TOKEN = AbstractToken("notEqualOperator", &CharacterGroups.NOT_EQUAL_OPERATOR);
    AbstractToken LESS_THAN_OPERATOR_TOKEN = AbstractToken("lessThanOperator", &CharacterGroups.LESS_THAN_OPERATOR);
    AbstractToken GREATER_THAN_OPERATOR_TOKEN = AbstractToken("greaterThanOperator", &CharacterGroups.GREATER_THAN_OPERATOR);
    AbstractToken LESS_THAN_OR_EQUAL_OPERATOR_TOKEN = AbstractToken("lessThanOrEqualOperator", &CharacterGroups.LESS_THAN_OR_EQUAL_OPERATOR);
    AbstractToken GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN = AbstractToken("greaterThanOrEqualOperator", &CharacterGroups.GREATER_THAN_OR_EQUAL_OPERATOR);

    AbstractToken ADD_OPERATOR_TOKEN = AbstractToken("addOperator", &CharacterGroups.ADD_OPERATOR);
    AbstractToken SUB_OPERATOR_TOKEN = AbstractToken("subOperator", &CharacterGroups.SUB_OPERATOR);
    AbstractToken MUL_OPERATOR_TOKEN = AbstractToken("mulOperator", &CharacterGroups.MUL_OPERATOR);
    AbstractToken DIV_OPERATOR_TOKEN = AbstractToken("divOperator", &CharacterGroups.DIV_OPERATOR);
    AbstractToken MOD_OPERATOR_TOKEN = AbstractToken("modOperator", &CharacterGroups.MOD_OPERATOR);

    AbstractToken ASSIGN_OPERATOR_TOKEN = AbstractToken("assignOperator", &CharacterGroups.ASSIGN_OPERATOR);
    AbstractToken ADD_ASSIGN_OPERATOR_TOKEN = AbstractToken("addAssignOperator", &CharacterGroups.ADD_ASSIGN_OPERATOR);
    AbstractToken SUB_ASSIGN_OPERATOR_TOKEN = AbstractToken("subAssignOperator", &CharacterGroups.SUB_ASSIGN_OPERATOR);
    AbstractToken MUL_ASSIGN_OPERATOR_TOKEN = AbstractToken("mulAssignOperator", &CharacterGroups.MUL_ASSIGN_OPERATOR);
    AbstractToken DIV_ASSIGN_OPERATOR_TOKEN = AbstractToken("divAssignOperator", &CharacterGroups.DIV_ASSIGN_OPERATOR);
    AbstractToken MOD_ASSIGN_OPERATOR_TOKEN = AbstractToken("modAssignOperator", &CharacterGroups.MOD_ASSIGN_OPERATOR);

    AbstractToken INCREMENT_OPERATOR_TOKEN = AbstractToken("incrementOperator", &CharacterGroups.INCREMENT_OPERATOR);
    AbstractToken DECREMENT_OPERATOR_TOKEN = AbstractToken("decrementOperator", &CharacterGroups.DECREMENT_OPERATOR); 

    AbstractToken NEGATE_OPERATOR_TOKEN = AbstractToken("negateOperator", &CharacterGroups.NEGATE_OPERATOR);
    
    AbstractToken NOT_OPERATOR_TOKEN = AbstractToken("notOperator", &CharacterGroups.NOT_OPERATOR);
    AbstractToken AND_OPERATOR_TOKEN = AbstractToken("andOperator", &CharacterGroups.AND_OPERATOR);
    AbstractToken OR_OPERATOR_TOKEN = AbstractToken("orOperator", &CharacterGroups.OR_OPERATOR);

    static AbstractToken* GetToken(std::string character);

}ConstTokens;

AbstractToken* ConstTokens::GetToken(std::string character)
{
    // TODO: Do this
    return nullptr;
}