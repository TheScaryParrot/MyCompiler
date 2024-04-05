#pragma once

#include "../PredictiveParser.hpp"

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"

ELookAheadCertainties PredictiveParser::LookAhead_Expression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_Expression(TokenList* tokens)
{
    return Parse_OrExpression(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_OrExpression(TokenList* tokens)
{
    return LookAhead_UnaryExpression(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_OrExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_AndExpression(tokens);

    if (!tokens->IsPeekOfTokenType(ConstTokens.OR_OPERATOR_TOKEN)) return firstExpression; // No OR_OPERATOR found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (tokens->IsPeekOfTokenType(ConstTokens.OR_OPERATOR_TOKEN))
    {
        tokens->Next(); // Consume OR_OPERATOR
        operatorValuePairs->push_back(new OperatorExpressionPair(EOperators::ADD_OPERATOR, Parse_AndExpression(tokens)));
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

    if (!tokens->IsPeekOfTokenType(ConstTokens.AND_OPERATOR_TOKEN)) return firstExpression; // No AND_OPERATOR found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (tokens->IsPeekOfTokenType(ConstTokens.AND_OPERATOR_TOKEN))
    {
        tokens->Next(); // Consume AND_OPERATOR
        operatorValuePairs->push_back(new OperatorExpressionPair(EOperators::ADD_OPERATOR, Parse_EqualExpression(tokens)));
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

    if (LookAhead_EqualOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent) return firstExpression; // No EqualOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_EqualOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        operatorValuePairs->push_back(new OperatorExpressionPair(Parse_EqualOperator(tokens), Parse_SumExpression(tokens)));
    }

    return new OperatorExpressionNode(firstExpression, operatorValuePairs);
}

ELookAheadCertainties PredictiveParser::LookAhead_EqualOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EOperators PredictiveParser::Parse_EqualOperator(TokenList* tokens)
{
    AbstractToken* nextToken = tokens->Next();

    if (nextToken->IsThisToken(ConstTokens.EQUAL_OPERATOR_TOKEN)) return EOperators::EQUAL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.NOT_EQUAL_OPERATOR_TOKEN)) return EOperators::NOT_EQUAL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN)) return EOperators::LESS_THAN_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN)) return EOperators::LESS_THAN_OR_EQUAL_OPERATOR;
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

    if (LookAhead_SumOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent) return firstExpression; // No SumOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_SumOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        EOperators op = Parse_SumOperator(tokens); // Ensure SumOperator is parsed ahead of MulExpression. Complier sometimes does weird stuff: https://en.cppreference.com/w/c/language/eval_order
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
    AbstractToken* nextToken = tokens->Next(); // Consume SumOperator

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

    if (LookAhead_MulOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent) return firstExpression; // No MulOperator found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (LookAhead_MulOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        EOperators op = Parse_MulOperator(tokens); // Ensure MulOperator is parsed ahead of UnaryExpression. Complier sometimes does weird stuff: https://en.cppreference.com/w/c/language/eval_order
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
    AbstractToken* nextToken = tokens->Next(); // Consume MulOperator

    if (nextToken->IsThisToken(ConstTokens.MUL_OPERATOR_TOKEN)) return EOperators::MUL_OPERATOR;
    if (nextToken->IsThisToken(ConstTokens.DIV_OPERATOR_TOKEN)) return EOperators::DIV_OPERATOR;

    return EOperators::MOD_OPERATOR;
}

ELookAheadCertainties PredictiveParser::LookAhead_UnaryExpression(TokenList* tokens)
{
    // <unaryOperator> | <value>
    if (LookAhead_UnaryOperator(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Value(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_UnaryExpression(TokenList* tokens)
{
    if (LookAhead_UnaryOperator(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        return new UnaryExpressionNode(Parse_UnaryOperator(tokens), Parse_Value(tokens));
    }

    return Parse_Value(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_UnaryOperator(TokenList* tokens)
{
    // NEGATE | NOT
    if (tokens->IsPeekOfTokenType(ConstTokens.NEGATE_OPERATOR_TOKEN) || tokens->IsPeekOfTokenType(ConstTokens.NOT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EUnaryOperators PredictiveParser::Parse_UnaryOperator(TokenList* tokens)
{
    AbstractToken* nextToken = tokens->Next(); // Consume UnaryOperator

    if (nextToken->IsThisToken(ConstTokens.NEGATE_OPERATOR_TOKEN)) return EUnaryOperators::NEGATE;

    return EUnaryOperators::NOT;
}

ELookAheadCertainties PredictiveParser::LookAhead_Value(TokenList* tokens)
{
    // <mutable> | <immutable>
    if (LookAhead_Mutable(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Immutable(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_Value(TokenList* tokens)
{
    if (LookAhead_Immutable(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_Immutable(tokens);

    return Parse_Mutable(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_Mutable(TokenList* tokens)
{
    // ID
    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
IDValueNode* PredictiveParser::Parse_Mutable(TokenList* tokens)
{
    std::string id = tokens->Next<IdentifierToken>()->GetValue();
    return new IDValueNode(id);
}

ELookAheadCertainties PredictiveParser::LookAhead_Immutable(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_Call(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    return LookAhead_Constant(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_Immutable(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN))
    {
        tokens->Next(); // Consume PARENTHESIS_OPEN
        AbstractExpressionNode* expression = Parse_Expression(tokens);
        tokens->Next(); // Consume PARENTHESIS_CLOSE
        return expression;
    }

    if (LookAhead_Call(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        return Parse_Call(tokens);
    }

    return Parse_Constant(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_Call(TokenList* tokens)
{
    // ID (
    if (!tokens->IsPeekOfTokenType(ConstTokens.CONST_IDENTIFIER_TOKEN)) return ELookAheadCertainties::CertainlyNotPresent;
    if (!tokens->IsPeekOfTokenType(ConstTokens.PARENTHESIS_OPEN_TOKEN, 1)) return ELookAheadCertainties::CertainlyNotPresent;

    return ELookAheadCertainties::CertainlyPresent;
}
CallNode* PredictiveParser::Parse_Call(TokenList* tokens)
{
    std::string functionName = tokens->Next<IdentifierToken>()->GetValue();
    tokens->Next(); // Consume PARENTHESIS_OPEN
    std::vector<CallArgument*> arguments = Parse_Arguments(tokens);
    tokens->Next(); // Consume PARENTHESIS_CLOSE

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
    if (LookAhead_LogicalConstant(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_LogicalConstant(tokens); // Consumtion of token is handled by Parse_LogicalConstant()

    if (tokens->IsPeekOfTokenType(ConstTokens.CONST_NUMBER_TOKEN)) return new NumberConstValueNode(tokens->Next<NumberConstToken>()->GetValue());

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
    AbstractToken* nextToken = tokens->Next(); // Consume LogicalConstant

    if (nextToken->IsThisToken(Keywords.LOGICAL_TRUE_KEYWORD)) return new LogicalConstValueNode(true);

    return new LogicalConstValueNode(false);
}

ELookAheadCertainties PredictiveParser::LookAhead_Arguments(TokenList* tokens)
{
    // <expression>? (SEPERATOR <expression>)* can be empty, therefore always unknown
    return ELookAheadCertainties::Unknown;
}
std::vector<CallArgument*> PredictiveParser::Parse_Arguments(TokenList* tokens)
{
    std::vector<CallArgument*> arguments;

    if (LookAhead_Expression(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        arguments.push_back(new CallArgument(Parse_Expression(tokens)));

        while (tokens->IsPeekOfTokenType(ConstTokens.SEPERATOR_TOKEN))
        {
            tokens->Next(); // Consume SEPERATOR
            arguments.push_back(new CallArgument(Parse_Expression(tokens)));
        }
    }

    return arguments;
}

