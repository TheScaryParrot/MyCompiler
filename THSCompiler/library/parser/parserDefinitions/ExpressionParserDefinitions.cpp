#pragma once

#include "../../tokens/Keywords.cpp"
#include "../../tokens/Tokens.cpp"
#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_Expression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_Expression(TokenList* tokens) { return Parse_AssignmentExpression(tokens); }

bool PredictiveParser::LookAhead_AssignmentExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_AssignmentExpression(TokenList* tokens)
{
    AbstractExpressionNode* currentExpression = Parse_OrExpression(tokens);

    if (!LookAhead_AssignOperator(tokens)) return currentExpression;  // No AssignOperator found
    AssignmentNode* assignmentNode = new AssignmentNode();

    while (LookAhead_AssignOperator(tokens))
    {
        EAssignOperators assignOperator = Parse_AssignOperator(tokens);

        VariableNode* variable = dynamic_cast<VariableNode*>(currentExpression);

        if (variable == nullptr)
        {
            std::cerr << "L-value of assignment must be a variable" << std::endl;
            return nullptr;
        }

        assignmentNode->assignments.push_back(new Assignment(variable, assignOperator));
        currentExpression = Parse_OrExpression(tokens);
    }

    assignmentNode->value = currentExpression;

    return assignmentNode;
}

bool PredictiveParser::LookAhead_AssignOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Peek();

    return nextToken->IsThisToken(Tokens.ASSIGN_OPERATOR_TOKEN) ||      // ASSIGN_OPERATOR
           nextToken->IsThisToken(Tokens.ADD_ASSIGN_OPERATOR_TOKEN) ||  // ADD_ASSIGN_OPERATOR
           nextToken->IsThisToken(Tokens.SUB_ASSIGN_OPERATOR_TOKEN) ||  // SUB_ASSIGN_OPERATOR
           nextToken->IsThisToken(Tokens.MUL_ASSIGN_OPERATOR_TOKEN) ||  // MUL_ASSIGN_OPERATOR
           nextToken->IsThisToken(Tokens.DIV_ASSIGN_OPERATOR_TOKEN) ||  // DIV_ASSIGN_OPERATOR
           nextToken->IsThisToken(Tokens.MOD_ASSIGN_OPERATOR_TOKEN);    // MOD_ASSIGN_OPERATOR
}
EAssignOperators PredictiveParser::Parse_AssignOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume AssignOperator

    if (nextToken->IsThisToken(Tokens.ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::ASSIGN;
    if (nextToken->IsThisToken(Tokens.ADD_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::ADD_ASSIGN;
    if (nextToken->IsThisToken(Tokens.SUB_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::SUB_ASSIGN;
    if (nextToken->IsThisToken(Tokens.MUL_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::MUL_ASSIGN;
    if (nextToken->IsThisToken(Tokens.DIV_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::DIV_ASSIGN;

    return EAssignOperators::MOD_ASSIGN;
}

bool PredictiveParser::LookAhead_OrExpression(TokenList* tokens) { return LookAhead_UnaryExpression(tokens); }
AbstractExpressionNode* PredictiveParser::Parse_OrExpression(TokenList* tokens)
{
    AbstractExpressionNode* firstExpression = Parse_AndExpression(tokens);

    if (!tokens->IsPeekOfTokenType(Tokens.OR_OPERATOR_TOKEN)) return firstExpression;  // No OR_OPERATOR found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (tokens->IsPeekOfTokenType(Tokens.OR_OPERATOR_TOKEN))
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

    if (!tokens->IsPeekOfTokenType(Tokens.AND_OPERATOR_TOKEN)) return firstExpression;  // No AND_OPERATOR found

    std::vector<OperatorExpressionPair*>* operatorValuePairs = new std::vector<OperatorExpressionPair*>();

    while (tokens->IsPeekOfTokenType(Tokens.AND_OPERATOR_TOKEN))
    {
        tokens->Next();  // Consume AND_OPERATOR
        operatorValuePairs->push_back(new OperatorExpressionPair(EOperators::AND_OPERATOR, Parse_EqualExpression(tokens)));
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
        EOperators op = Parse_EqualOperator(tokens);  // Ensure EqualOperator is parsed ahead of Parse_SumExpression. Complier sometimes does weird
                                                      // stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_SumExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_EqualOperator(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(Tokens.EQUAL_OPERATOR_TOKEN) ||                // EQUAL_OPERATOR
           tokens->IsPeekOfTokenType(Tokens.NOT_EQUAL_OPERATOR_TOKEN) ||            // NOT_EQUAL_OPERATOR
           tokens->IsPeekOfTokenType(Tokens.LESS_THAN_OPERATOR_TOKEN) ||            // LESS_THAN_OPERATOR
           tokens->IsPeekOfTokenType(Tokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN) ||   // LESS_THAN_OR_EQUAL_OPERATOR
           tokens->IsPeekOfTokenType(Tokens.GREATER_THAN_OPERATOR_TOKEN) ||         // GREATER_THAN_OPERATOR
           tokens->IsPeekOfTokenType(Tokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN);  // GREATER_THAN_OR_EQUAL_OPERATOR
}
EOperators PredictiveParser::Parse_EqualOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();

    if (nextToken->IsThisToken(Tokens.EQUAL_OPERATOR_TOKEN)) return EOperators::EQUAL_OPERATOR;
    if (nextToken->IsThisToken(Tokens.NOT_EQUAL_OPERATOR_TOKEN)) return EOperators::NOT_EQUAL_OPERATOR;
    if (nextToken->IsThisToken(Tokens.GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN)) return EOperators::LESS_THAN_OPERATOR;
    if (nextToken->IsThisToken(Tokens.LESS_THAN_OR_EQUAL_OPERATOR_TOKEN)) return EOperators::LESS_THAN_OR_EQUAL_OPERATOR;
    if (nextToken->IsThisToken(Tokens.GREATER_THAN_OPERATOR_TOKEN)) return EOperators::GREATER_THAN_OPERATOR;

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
        EOperators op = Parse_SumOperator(tokens);  // Ensure SumOperator is parsed ahead of MulExpression. Complier sometimes
                                                    // does weird stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_MulExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_SumOperator(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(Tokens.ADD_OPERATOR_TOKEN) || tokens->IsPeekOfTokenType(Tokens.SUB_OPERATOR_TOKEN);
}
EOperators PredictiveParser::Parse_SumOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume SumOperator

    if (nextToken->IsThisToken(Tokens.ADD_OPERATOR_TOKEN)) return EOperators::ADD_OPERATOR;

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
        EOperators op = Parse_MulOperator(tokens);  // Ensure MulOperator is parsed ahead of UnaryExpression. Complier sometimes
                                                    // does weird stuff: https://en.cppreference.com/w/c/language/eval_order
        operatorValuePairs->push_back(new OperatorExpressionPair(op, Parse_UnaryExpression(tokens)));
    }

    return new BinaryOperatorExpressionNode(firstExpression, operatorValuePairs);
}

bool PredictiveParser::LookAhead_MulOperator(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(Tokens.MUL_OPERATOR_TOKEN) || tokens->IsPeekOfTokenType(Tokens.DIV_OPERATOR_TOKEN) ||
           tokens->IsPeekOfTokenType(Tokens.MOD_OPERATOR_TOKEN);
}
EOperators PredictiveParser::Parse_MulOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume MulOperator

    if (nextToken->IsThisToken(Tokens.MUL_OPERATOR_TOKEN)) return EOperators::MUL_OPERATOR;
    if (nextToken->IsThisToken(Tokens.DIV_OPERATOR_TOKEN)) return EOperators::DIV_OPERATOR;

    return EOperators::MOD_OPERATOR;
}

bool PredictiveParser::LookAhead_UnaryExpression(TokenList* tokens)
{
    // <unaryOperator> | <value>
    return LookAhead_PreUnaryOperator(tokens) || LookAhead_Value(tokens);
}
AbstractExpressionNode* PredictiveParser::Parse_UnaryExpression(TokenList* tokens)
{
    EPreUnaryOperators preUnaryOperator = EPreUnaryOperators::PRE_NONE;

    AbstractValueNode* value = nullptr;

    EPostUnaryOperators postUnaryOperator = EPostUnaryOperators::POST_NONE;

    if (LookAhead_PreUnaryOperator(tokens))
    {
        preUnaryOperator = Parse_PreUnaryOperator(tokens);
    }

    value = Parse_Value(tokens);

    if (LookAhead_PostUnaryOperator(tokens))
    {
        if (preUnaryOperator != EPreUnaryOperators::PRE_NONE)
        {
            Logger.Log("PreUnaryOperator and PostUnaryOperator cannot be used together. Add parenthesis", Logger::ERROR);
        }
        else
        {
            postUnaryOperator = Parse_PostUnaryOperator(tokens);
        }
    }

    if (preUnaryOperator == EPreUnaryOperators::PRE_NONE && postUnaryOperator == EPostUnaryOperators::POST_NONE) return value;

    bool applyToReference = preUnaryOperator == EPreUnaryOperators::PRE_INCREMENT || preUnaryOperator == EPreUnaryOperators::PRE_DECREMENT ||
                            postUnaryOperator == EPostUnaryOperators::POST_INCREMENT || postUnaryOperator == EPostUnaryOperators::POST_DECREMENT;

    return new UnaryOperatorExpressionNode(preUnaryOperator, value, postUnaryOperator, applyToReference);
}

bool PredictiveParser::LookAhead_PreUnaryOperator(TokenList* tokens)
{
    // NEGATE | NOT | INCREMENT | DECREMENT
    std::shared_ptr<Token> next = tokens->Peek();

    return next->IsThisToken(Tokens.NEGATE_OPERATOR_TOKEN) ||     // NEGATE
           next->IsThisToken(Tokens.NOT_OPERATOR_TOKEN) ||        // NOT
           next->IsThisToken(Tokens.INCREMENT_OPERATOR_TOKEN) ||  // INCREMENT
           next->IsThisToken(Tokens.DECREMENT_OPERATOR_TOKEN);    // DECREMENT
}
EPreUnaryOperators PredictiveParser::Parse_PreUnaryOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume UnaryOperator

    if (nextToken->IsThisToken(Tokens.NEGATE_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_NEGATE;
    if (nextToken->IsThisToken(Tokens.NOT_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_NOT;
    if (nextToken->IsThisToken(Tokens.INCREMENT_OPERATOR_TOKEN)) return EPreUnaryOperators::PRE_INCREMENT;

    return EPreUnaryOperators::PRE_DECREMENT;
}

bool PredictiveParser::LookAhead_PostUnaryOperator(TokenList* tokens)
{
    // INCREMENT | DECREMENT
    return tokens->IsPeekOfTokenType(Tokens.INCREMENT_OPERATOR_TOKEN) || tokens->IsPeekOfTokenType(Tokens.DECREMENT_OPERATOR_TOKEN);
}
EPostUnaryOperators PredictiveParser::Parse_PostUnaryOperator(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume UnaryOperator

    if (nextToken->IsThisToken(Tokens.INCREMENT_OPERATOR_TOKEN)) return EPostUnaryOperators::POST_INCREMENT;

    return EPostUnaryOperators::POST_DECREMENT;
}

bool PredictiveParser::LookAhead_Value(TokenList* tokens)
{
    // <call> | <parenthesis_expression> | <const> | <variable> | <struct>
    return LookAhead_Call(tokens) || LookAhead_Parenthesis_Expression(tokens) || LookAhead_Struct(tokens) || LookAhead_Variable(tokens) ||
           LookAhead_Const(tokens);
}
AbstractValueNode* PredictiveParser::Parse_Value(TokenList* tokens)
{
    if (LookAhead_Call(tokens)) return Parse_Call(tokens);

    if (LookAhead_Parenthesis_Expression(tokens)) return Parse_Parenthesis_Expression(tokens);

    if (LookAhead_Struct(tokens)) return Parse_Struct(tokens);

    if (LookAhead_Variable(tokens)) return Parse_Variable(tokens);

    return Parse_Const(tokens);
}

bool PredictiveParser::LookAhead_Call(TokenList* tokens)
{
    // ID (
    return tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN) && tokens->IsPeekOfTokenType(Tokens.PARENTHESIS_OPEN_TOKEN, 1);
}
CallNode* PredictiveParser::Parse_Call(TokenList* tokens)
{
    std::string functionName = tokens->Next<TokenWithValue>()->GetValue();
    tokens->Next();  // Consume PARENTHESIS_OPEN
    std::vector<AbstractExpressionNode*> arguments = Parse_Arguments(tokens);
    tokens->Next();  // Consume PARENTHESIS_CLOSE

    return new CallNode(functionName, arguments);
}

bool PredictiveParser::LookAhead_Parenthesis_Expression(TokenList* tokens)
{
    // PARENTHESIS_OPEN
    return tokens->IsPeekOfTokenType(Tokens.PARENTHESIS_OPEN_TOKEN);
}
ParenthesisExpressionNode* PredictiveParser::Parse_Parenthesis_Expression(TokenList* tokens)
{
    tokens->Next();  // Consume PARENTHESIS_OPEN
    AbstractExpressionNode* expression = Parse_Expression(tokens);
    tokens->Next();  // Consume PARENTHESIS_CLOSE

    return new ParenthesisExpressionNode(expression);
}

bool PredictiveParser::LookAhead_Struct(TokenList* tokens)
{
    // BRACES_OPEN
    return tokens->IsPeekOfTokenType(Tokens.BRACES_OPEN_TOKEN);
}
StructNode* PredictiveParser::Parse_Struct(TokenList* tokens)
{
    tokens->Next();  // Consume BRACES_OPEN

    std::vector<AbstractExpressionNode*> properties = std::vector<AbstractExpressionNode*>();

    while (!tokens->IsPeekOfTokenType(Tokens.BRACES_CLOSE_TOKEN))
    {
        properties.push_back(Parse_Expression(tokens));

        if (tokens->IsPeekOfTokenType(Tokens.BRACES_CLOSE_TOKEN)) break;

        tokens->Next();  // Consume SEPERATOR
    }

    tokens->Next();  // Consume BRACES_CLOSE

    return new StructNode(properties);
}

bool PredictiveParser::LookAhead_Variable(TokenList* tokens)
{
    // ID
    return tokens->IsPeekOfTokenType(Tokens.CONST_IDENTIFIER_TOKEN);
}
VariableNode* PredictiveParser::Parse_Variable(TokenList* tokens)
{
    std::vector<std::string> ids;
    ids.push_back(tokens->Next<TokenWithValue>()->GetValue());

    while (tokens->IsPeekOfTokenType(Tokens.DOT_TOKEN))
    {
        tokens->Next();  // Consume DOT
        ids.push_back(tokens->Next<TokenWithValue>()->GetValue());
    }

    return new VariableNode(ids);
}

bool PredictiveParser::LookAhead_Const(TokenList* tokens)
{
    // INT | STRING | <logicalConst>
    return tokens->IsPeekOfTokenType(Tokens.CONST_INT_TOKEN) || tokens->IsPeekOfTokenType(Tokens.CONST_FLOAT_TOKEN) ||
           tokens->IsPeekOfTokenType(Tokens.CONST_STRING_TOKEN) || LookAhead_LogicalConst(tokens);
}
AbstractConstValueNode* PredictiveParser::Parse_Const(TokenList* tokens)
{
    if (LookAhead_LogicalConst(tokens)) return Parse_LogicalConst(tokens);  // Consumtion of token is handled by Parse_LogicalConstant()

    if (tokens->IsPeekOfTokenType(Tokens.CONST_INT_TOKEN)) return new IntConstValueNode(std::stoi(tokens->Next<TokenWithValue>()->GetValue()));
    if (tokens->IsPeekOfTokenType(Tokens.CONST_FLOAT_TOKEN)) return new FloatConstValueNode(std::stof(tokens->Next<TokenWithValue>()->GetValue()));

    return new StringConstValueNode(tokens->Next<TokenWithValue>()->GetValue());
}

bool PredictiveParser::LookAhead_LogicalConst(TokenList* tokens)
{
    // TRUE | FALSE
    return tokens->IsPeekOfTokenType(Keywords.LOGICAL_TRUE_KEYWORD) || tokens->IsPeekOfTokenType(Keywords.LOGICAL_FALSE_KEYWORD);
}
LogicalConstValueNode* PredictiveParser::Parse_LogicalConst(TokenList* tokens)
{
    std::shared_ptr<Token> nextToken = tokens->Next();  // Consume LogicalConstant

    if (nextToken->IsThisToken(Keywords.LOGICAL_TRUE_KEYWORD)) return new LogicalConstValueNode(true);

    return new LogicalConstValueNode(false);
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

        while (tokens->IsPeekOfTokenType(Tokens.SEPERATOR_TOKEN))
        {
            tokens->Next();  // Consume SEPERATOR
            arguments.push_back(Parse_Expression(tokens));
        }
    }

    return arguments;
}
