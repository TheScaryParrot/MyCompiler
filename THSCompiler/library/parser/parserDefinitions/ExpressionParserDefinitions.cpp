#pragma once

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"
#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_Expression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_Expression(TokenList* tokens)
{
    return Parse_AssignmentExpression(tokens);
}

bool PredictiveParser::LookAhead_AssignmentExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_AssignmentExpression(TokenList* tokens)
{
    AbstractExpressionNode* currentExpression = Parse_OrExpression(tokens);

    if (!LookAhead_AssignOperator(tokens)) return currentExpression;  // No AssignOperator found

    AssignmentNode* assignmentNode = new AssignmentNode();

    while (LookAhead_AssignOperator(tokens))
    {
        EAssignOperators assignOperator = Parse_AssignOperator(tokens);
        assignmentNode->assignments.push_back(new Assignment(currentExpression, assignOperator));
        currentExpression = Parse_OrExpression(tokens);
    }

    assignmentNode->value = currentExpression;

    return assignmentNode;
}

bool PredictiveParser::LookAhead_AssignOperator(TokenList* tokens, unsigned int offset)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Peek(offset);

    return nextToken->IsThisToken(ConstTokens.ASSIGN_OPERATOR_TOKEN) ||      // ASSIGN_OPERATOR
           nextToken->IsThisToken(ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN) ||  // ADD_ASSIGN_OPERATOR
           nextToken->IsThisToken(ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN) ||  // SUB_ASSIGN_OPERATOR
           nextToken->IsThisToken(ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN) ||  // MUL_ASSIGN_OPERATOR
           nextToken->IsThisToken(ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN) ||  // DIV_ASSIGN_OPERATOR
           nextToken->IsThisToken(ConstTokens.MOD_ASSIGN_OPERATOR_TOKEN);    // MOD_ASSIGN_OPERATOR
}
EAssignOperators PredictiveParser::Parse_AssignOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume AssignOperator

    if (nextToken->IsThisToken(ConstTokens.ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::ASSIGN;
    if (nextToken->IsThisToken(ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::ADD_ASSIGN;
    if (nextToken->IsThisToken(ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::SUB_ASSIGN;
    if (nextToken->IsThisToken(ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::MUL_ASSIGN;
    if (nextToken->IsThisToken(ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::DIV_ASSIGN;

    return EAssignOperators::MOD_ASSIGN;
}

bool PredictiveParser::LookAhead_OrExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_OrExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_AndExpression(tokens);

    if (!tokens->IsPeekOfTokenType(ConstTokens.OR_OPERATOR_TOKEN)) return firstExpression;  // No OR_OPERATOR found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (tokens->IsPeekOfTokenType(ConstTokens.OR_OPERATOR_TOKEN))
    {
        tokens->Next();  // Consume OR_OPERATOR
        operatorValuePairs->push_back(new OperatorExpressionPair(EOperators::OR_OPERATOR, Parse_AndExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_AndExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_AndExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_EqualExpression(tokens);

    if (!tokens->IsPeekOfTokenType(ConstTokens.AND_OPERATOR_TOKEN)) return firstExpression;  // No AND_OPERATOR found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (tokens->IsPeekOfTokenType(ConstTokens.AND_OPERATOR_TOKEN))
    {
        tokens->Next();  // Consume AND_OPERATOR
        operatorValuePairs->push_back(
            new OperatorExpressionPair(EOperators::AND_OPERATOR, Parse_EqualExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_EqualExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_EqualExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_SumExpression(tokens);

    if (!LookAhead_EqualOperator(tokens)) return firstExpression;  // No EqualOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_EqualOperator(tokens))
    {
        EOperators op = Parse_EqualOperator(
            tokens);  // Ensure EqualOperator is parsed ahead of Parse_SumExpression. Complier sometimes does weird
                      // stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_SumExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_EqualOperator(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(ConstTokens.EQUAL_OPERATOR_TOKEN) ||               // EQUAL_OPERATOR
           tokens->IsPeekOfTokenType(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN) ||           // NOT_EQUAL_OPERATOR
           tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OPERATOR_TOKEN) ||           // LESS_THAN_OPERATOR
           tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN) ||  // LESS_THAN_OR_EQUAL_OPERATOR
           tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OPERATOR_TOKEN) ||        // GREATER_THAN_OPERATOR
           tokens->IsPeekOfTokenType(
               ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN);  // GREATER_THAN_OR_EQUAL_OPERATOR
}
EOperators PredictiveParser::Parse_EqualOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();

    if (nextToken->IsThisToken(ConstTokens.EQUAL_OPERATOR_TOKEN)) return EOperators::EQUAL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN)) return EOperators::NOT_EQUAL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN)) return EOperators::LESS_THAN_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN))
        return EOperators::LESS_THAN_OR_EQUAL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.GREATER_THAN_OPERATOR_TOKEN)) return EOperators::GREATER_THAN_OPERATOR;

    return EOperators::LESS_THAN_OPERATOR;
}

bool PredictiveParser::LookAhead_SumExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_SumExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_MulExpression(tokens);

    if (!LookAhead_SumOperator(tokens)) return firstExpression;  // No SumOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_SumOperator(tokens))
    {
        EOperators op =
            Parse_SumOperator(tokens);  // Ensure SumOperator is parsed ahead of MulExpression. Complier sometimes
                                        // does weird stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_MulExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_SumOperator(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(ConstTokens.ADD_OPERATOR_TOKEN) ||
           tokens->IsPeekOfTokenType(ConstTokens.SUB_OPERATOR_TOKEN);
}
EOperators PredictiveParser::Parse_SumOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume SumOperator

    if (nextToken->IsThisToken(ConstTokens.ADD_OPERATOR_TOKEN)) return EOperators::ADD_OPERATOR;

    return EOperators::SUB_OPERATOR;
}

bool PredictiveParser::LookAhead_MulExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_MulExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_UnaryExpression(tokens);

    if (!LookAhead_MulOperator(tokens)) return firstExpression;  // No MulOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_MulOperator(tokens))
    {
        EOperators op =
            Parse_MulOperator(tokens);  // Ensure MulOperator is parsed ahead of UnaryExpression. Complier sometimes
                                        // does weird stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_UnaryExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_MulOperator(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(ConstTokens.MUL_OPERATOR_TOKEN) ||
           tokens->IsPeekOfTokenType(ConstTokens.DIV_OPERATOR_TOKEN) ||
           tokens->IsPeekOfTokenType(ConstTokens.MOD_OPERATOR_TOKEN);
}
EOperators PredictiveParser::Parse_MulOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume MulOperator

    if (nextToken->IsThisToken(ConstTokens.MUL_OPERATOR_TOKEN)) return EOperators::MUL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.DIV_OPERATOR_TOKEN)) return EOperators::DIV_OPERATOR;

    return EOperators::MOD_OPERATOR;
}

bool PredictiveParser::LookAhead_UnaryExpression(TokenList* tokens)
{
    // <unaryOperator> | <relAccessValue>
    return LookAhead_PreUnaryOperator(tokens) || LookAhead_RelAccessValue(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_UnaryExpression(TokenList* tokens)
{
    EPreUnaryOperators preUnaryOperator = EPreUnaryOperators::PRE_NONE;

    AbstractExpressionNode* value = nullptr;

    EPostUnaryOperators postUnaryOperator = EPostUnaryOperators::POST_NONE;

    if (LookAhead_PreUnaryOperator(tokens))
    {
        preUnaryOperator = Parse_PreUnaryOperator(tokens);
    }

    value = Parse_RelAccessValue(tokens);

    if (LookAhead_PostUnaryOperator(tokens))
    {
        postUnaryOperator = Parse_PostUnaryOperator(tokens);
    }

    if (preUnaryOperator == EPreUnaryOperators::PRE_NONE && postUnaryOperator == EPostUnaryOperators::POST_NONE)
        return value;

    return new UnaryOperatorExpressionNode(preUnaryOperator, value, postUnaryOperator);
}

bool PredictiveParser::LookAhead_PreUnaryOperator(TokenList* tokens)
{
    // NEGATE | NOT | INCREMENT | DECREMENT
    std::shared_ptr<AbstractToken> next = tokens->Peek();

    return next->IsThisToken(ConstTokens.NEGATE_OPERATOR_TOKEN) ||     // NEGATE
           next->IsThisToken(ConstTokens.NOT_OPERATOR_TOKEN) ||        // NOT
           next->IsThisToken(ConstTokens.INCREMENT_OPERATOR_TOKEN) ||  // INCREMENT
           next->IsThisToken(ConstTokens.DECREMENT_OPERATOR_TOKEN);    // DECREMENT
}
EPreUnaryOperators PredictiveParser::Parse_PreUnaryOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume UnaryOperator

    if (nextToken->IsThisToken(ConstTokens.NEGATE_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_NEGATE;
    if (nextToken->IsThisToken(ConstTokens.NOT_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_NOT;
    if (nextToken->IsThisToken(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_INCREMENT;

    return EPreUnaryOperators::PRE_DECREMENT;
}

bool PredictiveParser::LookAhead_PostUnaryOperator(TokenList* tokens)
{
    // INCREMENT | DECREMENT
    return tokens->IsPeekOfTokenType(ConstTokens.INCREMENT_OPERATOR_TOKEN) ||
           tokens->IsPeekOfTokenType(ConstTokens.DECREMENT_OPERATOR_TOKEN);
}
EPostUnaryOperators PredictiveParser::Parse_PostUnaryOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume UnaryOperator

    if (nextToken->IsThisToken(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return EPostUnaryOperators::POST_INCREMENT;

    return EPostUnaryOperators::POST_DECREMENT;
}

bool PredictiveParser::LookAhead_RelAccessValue(TokenList* tokens)
{
    // <value>
    return LookAhead_Value(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_RelAccessValue(TokenList* tokens)
{
    // (<value><accessor>)*<value>

    AbstractExpressionNode* currentValue = Parse_Value(tokens);

    if (!LookAhead_Accessor(tokens)) return currentValue;  // No Accessor found

    RelAccessValueNode* relAccessValue = new RelAccessValueNode();

    while (LookAhead_Accessor(tokens))
    {
        RelAccess relAccess = RelAccess();
        relAccess.isStaticAccess = Parse_Accessor(tokens);
        relAccess.value = currentValue;

        relAccessValue->AddRelAccess(relAccess);

        currentValue = Parse_Value(tokens);
    }

    relAccessValue->SetLastValue(currentValue);

    return relAccessValue;
}

bool PredictiveParser::LookAhead_Value(TokenList* tokens)
{
    // ID | PARENTHESIS_OPEN  | <const>
    return tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) ||
           tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN) || LookAhead_Constant(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_Value(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN))
    {
        tokens->Next();  // Consume PARENTHESIS_OPEN
        AbstractExpressionNode* expression = Parse_Expression(tokens);
        tokens->Next();  // Consume PARENTHESIS_CLOSE

        return expression;
    }

    if (LookAhead_Call(tokens)) return Parse_Call(tokens);

    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN))
    {
        std::string variableName = tokens->Next<IdentifierToken>()->GetValue();
        return new IdentifierNode(variableName);
    }

    return Parse_Constant(tokens);
}

bool PredictiveParser::LookAhead_Call(TokenList* tokens)
{
    // ID (
    return tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN) &&
           tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, 1);
}
CallNode* PredictiveParser::Parse_Call(TokenList* tokens)
{
    std::string functionName = tokens->Next<IdentifierToken>()->GetValue();
    tokens->Next();  // Consume PARENTHESIS_OPEN
    std::vector<AbstractExpressionNode*> arguments = Parse_Arguments(tokens);
    tokens->Next();  // Consume PARENTHESIS_CLOSE

    return new CallNode(functionName, arguments);
}

bool PredictiveParser::LookAhead_Constant(TokenList* tokens)
{
    // INT | STRING | <logicalConst>
    return tokens->IsPeekOfTokenType(ConstTokens.CONST_NUMBER_TOKEN) ||
           tokens->IsPeekOfTokenType(ConstTokens.CONST_STRING_TOKEN) || LookAhead_LogicalConstant(tokens);
}
AbstractConstValueNode* PredictiveParser::Parse_Constant(TokenList* tokens)
{
    if (LookAhead_LogicalConstant(tokens))
        return Parse_LogicalConstant(tokens);  // Consumtion of token is handled by Parse_LogicalConstant()

    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_NUMBER_TOKEN))
        return new NumberConstValueNode(tokens->Next<NumberConstToken>()->GetValue());

    return new StringConstValueNode(tokens->Next<StringConstToken>()->GetValue());
}

bool PredictiveParser::LookAhead_LogicalConstant(TokenList* tokens)
{
    // TRUE | FALSE
    return tokens->IsPeekOfTokenType(Keywords.LOGICAL_TRUE_KEYWORD) ||
           tokens->IsPeekOfTokenType(Keywords.LOGICAL_FALSE_KEYWORD);
}
LogicalConstValueNode* PredictiveParser::Parse_LogicalConstant(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume LogicalConstant

    if (nextToken->IsThisToken(Keywords.LOGICAL_TRUE_KEYWORD)) return new LogicalConstValueNode(true);

    return new LogicalConstValueNode(false);
}

bool PredictiveParser::LookAhead_Accessor(TokenList* tokens)
{
    // DOT | COLON
    return tokens->IsPeekOfTokenType(ConstTokens.DOT_TOKEN) || tokens->IsPeekOfTokenType(ConstTokens.COLON_TOKEN);
}
bool PredictiveParser::Parse_Accessor(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume Accessor

    // Static if token was COLON, otherwise (DOT) not static
    return nextToken->IsThisToken(ConstTokens.COLON_TOKEN);
}

bool PredictiveParser::LookAhead_Arguments(TokenList* tokens)
{
    // <expression>? (SEPERATOR <expression>)* can be empty, therefore always true
    return true;
}
std::vector<AbstractExpressionNode*> PredictiveParser::Parse_Arguments(TokenList* tokens)
{
    std::vector<AbstractExpressionNode*> arguments;

    if (LookAhead_Expression(tokens))
    {
        arguments.push_back(Parse_Expression(tokens));

        while (tokens->IsPeekOfTokenType(ConstTokens.SEPERATOR_TOKEN))
        {
            tokens->Next();  // Consume SEPERATOR
            arguments.push_back(Parse_Expression(tokens));
        }
    }

    return arguments;
}
