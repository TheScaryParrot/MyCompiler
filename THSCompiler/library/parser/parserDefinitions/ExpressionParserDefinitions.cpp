#pragma once

#include "../../syntaxTree/nodes/line/expression/values/ValueChainNode.cpp"
#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"
#include "../PredictiveParser.hpp"

ELookAheadCertainties PredictiveParser::LookAhead_Expression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_Expression(TokenList* tokens)
{
    return Parse_AssignmentExpression(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_AssignmentExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_AssignmentExpression(TokenList* tokens)
{
    std::vector<Assignment*> assignments;

    while (LookAhead_Assignment(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        assignments.push_back(Parse_Assignment(tokens));
    }

    AbstractExpressionNode* value = Parse_OrExpression(tokens);

    if (assignments.size() == 0) return value;

    return new AssignmentNode(assignments, value);
}

ELookAheadCertainties PredictiveParser::LookAhead_Assignment(TokenList* tokens)
{
    if (LookAhead_ValueChain(tokens) != ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyNotPresent;

    // Offset 1 because we need to check the next token
    return LookAhead_AssignOperator(tokens, 1);
}
Assignment* PredictiveParser::Parse_Assignment(TokenList* tokens)
{
    AbstractExpressionNode* L_value = Parse_ValueChain(tokens);

    EAssignOperators assignOperator = Parse_AssignOperator(tokens);

    return new Assignment(L_value, assignOperator);
}

ELookAheadCertainties PredictiveParser::LookAhead_AssignOperator(TokenList* tokens, unsigned int offset)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Peek(offset);

    if (nextToken->IsThisToken(ConstTokens.ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (nextToken->IsThisToken(ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (nextToken->IsThisToken(ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (nextToken->IsThisToken(ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (nextToken->IsThisToken(ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (nextToken->IsThisToken(ConstTokens.MOD_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
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

ELookAheadCertainties PredictiveParser::LookAhead_OrExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
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

    return new OperatorExpressionNode(firstExpression, operatorValuePairs);
}

ELookAheadCertainties PredictiveParser::LookAhead_AndExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
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

    return new OperatorExpressionNode(firstExpression, operatorValuePairs);
}

ELookAheadCertainties PredictiveParser::LookAhead_EqualExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_EqualExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_SumExpression(tokens);

    if (LookAhead_EqualOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent)
        return firstExpression;  // No EqualOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_EqualOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        EOperators op = Parse_EqualOperator(
            tokens);  // Ensure EqualOperator is parsed ahead of Parse_SumExpression. Complier sometimes does weird
                      // stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_SumExpression(tokens)));
    }

    return new OperatorExpressionNode(firstExpression, operatorValuePairs);
}

ELookAheadCertainties PredictiveParser::LookAhead_EqualOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN))
        return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OPERATOR_TOKEN))
        return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN))
        return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
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

ELookAheadCertainties PredictiveParser::LookAhead_SumExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_SumExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_MulExpression(tokens);

    if (LookAhead_SumOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent)
        return firstExpression;  // No SumOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_SumOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        EOperators op =
            Parse_SumOperator(tokens);  // Ensure SumOperator is parsed ahead of MulExpression. Complier sometimes does
                                        // weird stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_MulExpression(tokens)));
    }

    return new OperatorExpressionNode(firstExpression, operatorValuePairs);
}

ELookAheadCertainties PredictiveParser::LookAhead_SumOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.ADD_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.SUB_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EOperators PredictiveParser::Parse_SumOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume SumOperator

    if (nextToken->IsThisToken(ConstTokens.ADD_OPERATOR_TOKEN)) return EOperators::ADD_OPERATOR;

    return EOperators::SUB_OPERATOR;
}

ELookAheadCertainties PredictiveParser::LookAhead_MulExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_MulExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_UnaryExpression(tokens);

    if (LookAhead_MulOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent)
        return firstExpression;  // No MulOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_MulOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        EOperators op =
            Parse_MulOperator(tokens);  // Ensure MulOperator is parsed ahead of UnaryExpression. Complier sometimes
                                        // does weird stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_UnaryExpression(tokens)));
    }

    return new OperatorExpressionNode(firstExpression, operatorValuePairs);
}

ELookAheadCertainties PredictiveParser::LookAhead_MulOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.MUL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.DIV_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.MOD_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EOperators PredictiveParser::Parse_MulOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume MulOperator

    if (nextToken->IsThisToken(ConstTokens.MUL_OPERATOR_TOKEN)) return EOperators::MUL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.DIV_OPERATOR_TOKEN)) return EOperators::DIV_OPERATOR;

    return EOperators::MOD_OPERATOR;
}

ELookAheadCertainties PredictiveParser::LookAhead_UnaryExpression(TokenList* tokens)
{
    // <unaryOperator> | <value>
    if (LookAhead_PreUnaryOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
        return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_ValueChain(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_UnaryExpression(TokenList* tokens)
{
    EPreUnaryOperators preUnaryOperator = EPreUnaryOperators::PRE_NONE;

    AbstractExpressionNode* value = nullptr;

    EPostUnaryOperators postUnaryOperator = EPostUnaryOperators::POST_NONE;

    if (LookAhead_PreUnaryOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        preUnaryOperator = Parse_PreUnaryOperator(tokens);
    }

    value = Parse_ValueChain(tokens);

    if (LookAhead_PostUnaryOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        postUnaryOperator = Parse_PostUnaryOperator(tokens);
    }

    if (preUnaryOperator == EPreUnaryOperators::PRE_NONE && postUnaryOperator == EPostUnaryOperators::POST_NONE)
        return value;

    return new UnaryExpressionNode(preUnaryOperator, value, postUnaryOperator);
}

ELookAheadCertainties PredictiveParser::LookAhead_PreUnaryOperator(TokenList* tokens)
{
    // NEGATE | NOT | INCREMENT | DECREMENT
    std::shared_ptr<AbstractToken> next = tokens->Peek();

    if (next->IsThisToken(ConstTokens.NEGATE_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (next->IsThisToken(ConstTokens.NOT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (next->IsThisToken(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (next->IsThisToken(ConstTokens.DECREMENT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EPreUnaryOperators PredictiveParser::Parse_PreUnaryOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume UnaryOperator

    if (nextToken->IsThisToken(ConstTokens.NEGATE_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_NEGATE;
    if (nextToken->IsThisToken(ConstTokens.NOT_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_NOT;
    if (nextToken->IsThisToken(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_INCREMENT;

    return EPreUnaryOperators::PRE_DECREMENT;
}

ELookAheadCertainties PredictiveParser::LookAhead_PostUnaryOperator(TokenList* tokens)
{
    // INCREMENT | DECREMENT
    if (tokens->IsPeekOfTokenType(ConstTokens.INCREMENT_OPERATOR_TOKEN) ||
        tokens->IsPeekOfTokenType(ConstTokens.DECREMENT_OPERATOR_TOKEN))
        return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EPostUnaryOperators PredictiveParser::Parse_PostUnaryOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume UnaryOperator

    if (nextToken->IsThisToken(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return EPostUnaryOperators::POST_INCREMENT;

    return EPostUnaryOperators::POST_DECREMENT;
}

ELookAheadCertainties PredictiveParser::LookAhead_ValueChain(TokenList* tokens)
{
    // <value>
    return LookAhead_Value(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_ValueChain(TokenList* tokens)
{
    // <staticValueChain>(<normalPropertyAccessor><staticValueChain>)*

    AbstractExpressionNode* firstValue = Parse_StaticValueChain(tokens);

    if (LookAhead_NormalAccessor(tokens) == ELookAheadCertainties::CertainlyNotPresent)
    {
        return firstValue;  // No PropertyAccessor found
    }

    ValueChainNode* valueChain = (new ValueChainNode())->AddPropertyAccess(firstValue);

    while (LookAhead_NormalAccessor(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        Parse_NormalAccessor(tokens);
        valueChain->AddPropertyAccess(Parse_Value(tokens));
    }

    return valueChain;
}

ELookAheadCertainties PredictiveParser::LookAhead_StaticValueChain(TokenList* tokens)
{
    // <value>
    return LookAhead_Value(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_StaticValueChain(TokenList* tokens)
{
    // <value>(<staticPropertyAccessor><value>)*

    AbstractExpressionNode* firstValue = Parse_Value(tokens);

    if (LookAhead_StaticAccessor(tokens) == ELookAheadCertainties::CertainlyNotPresent)
    {
        return firstValue;  // No PropertyAccessor found
    }

    ValueChainNode* valueChain = (new ValueChainNode())->AddPropertyAccess(firstValue);

    while (LookAhead_StaticAccessor(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        Parse_StaticAccessor(tokens);
        valueChain->AddPropertyAccess(Parse_Value(tokens));
    }

    return valueChain;
}

ELookAheadCertainties PredictiveParser::LookAhead_Value(TokenList* tokens)
{
    // ID | PARENTHESIS_OPEN  | <const>
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Constant(tokens);
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

    if (LookAhead_Call(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_Call(tokens);
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN))
    {
        std::string variableName = tokens->Next<IdentifierToken>()->GetValue();
        return new IDValueNode(variableName);
    }

    if (LookAhead_Constant(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_Constant(tokens);

    return Parse_Constant(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_Call(TokenList* tokens)
{
    // ID (
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN))
        return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, 1))
        return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
CallNode* PredictiveParser::Parse_Call(TokenList* tokens)
{
    std::string functionName = tokens->Next<IdentifierToken>()->GetValue();
    tokens->Next();  // Consume PARENTHESIS_OPEN
    std::vector<AbstractExpressionNode*> arguments = Parse_Arguments(tokens);
    tokens->Next();  // Consume PARENTHESIS_CLOSE

    return new CallNode(functionName, arguments);
}

ELookAheadCertainties PredictiveParser::LookAhead_Constant(TokenList* tokens)
{
    // INT | STRING | <logicalConst>
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_NUMBER_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_STRING_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_LogicalConstant(tokens);
}
AbstractConstValueNode* PredictiveParser::Parse_Constant(TokenList* tokens)
{
    if (LookAhead_LogicalConstant(tokens) == ELookAheadCertainties::CertainlyPresent)
        return Parse_LogicalConstant(tokens);  // Consumtion of token is handled by Parse_LogicalConstant()

    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_NUMBER_TOKEN))
        return new NumberConstValueNode(tokens->Next<NumberConstToken>()->GetValue());

    return new StringConstValueNode(tokens->Next<StringConstToken>()->GetValue());
}

ELookAheadCertainties PredictiveParser::LookAhead_LogicalConstant(TokenList* tokens)
{
    // TRUE | FALSE
    if (tokens->IsPeekOfTokenType(Keywords.LOGICAL_TRUE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.LOGICAL_FALSE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
LogicalConstValueNode* PredictiveParser::Parse_LogicalConstant(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> nextToken = tokens->Next();  // Consume LogicalConstant

    if (nextToken->IsThisToken(Keywords.LOGICAL_TRUE_KEYWORD)) return new LogicalConstValueNode(true);

    return new LogicalConstValueNode(false);
}

ELookAheadCertainties PredictiveParser::LookAhead_NormalAccessor(TokenList* tokens)
{
    // .
    return tokens->IsPeekOfTokenType(ConstTokens.DOT_TOKEN) ? ELookAheadCertainties::CertainlyPresent
                                                            : ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_NormalAccessor(TokenList* tokens)
{
    tokens->Next();  // Consume DOT
}

ELookAheadCertainties PredictiveParser::LookAhead_StaticAccessor(TokenList* tokens)
{
    // :
    return tokens->IsPeekOfTokenType(ConstTokens.COLON_TOKEN) ? ELookAheadCertainties::CertainlyPresent
                                                              : ELookAheadCertainties::CertainlyNotPresent;
}
void PredictiveParser::Parse_StaticAccessor(TokenList* tokens)
{
    tokens->Next();  // Consume COLON
}

ELookAheadCertainties PredictiveParser::LookAhead_Arguments(TokenList* tokens)
{
    // <expression>? (SEPERATOR <expression>)* can be empty, therefore always unknown
    return ELookAheadCertainties::Unknown;
}
std::vector<AbstractExpressionNode*> PredictiveParser::Parse_Arguments(TokenList* tokens)
{
    std::vector<AbstractExpressionNode*> arguments;

    if (LookAhead_Expression(tokens) == ELookAheadCertainties::CertainlyPresent)
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
