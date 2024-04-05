#pragma once

#include "../PredictiveParser.hpp"

#include "../../tokens/ConstTokens.cpp"
#include "../../tokens/Keywords.cpp"

ELookAheadCertainties PredictiveParser::LookAhead_Statement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.STATEMENT_END_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_Body(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_Assignment(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;
    if (LookAhead_KeywordStatement(tokens) == ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_Call(tokens);
}
AbstractStatementNode* PredictiveParser::Parse_Statement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.STATEMENT_END_TOKEN))
    {
        tokens->Next(); // Consume STATEMENT_END_TOKEN
        return new EmptyStatementNode();
    }

    if (LookAhead_Body(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_Body(tokens);
    if (tokens->Peek()->IsKeyword()) return Parse_KeywordStatement(tokens);
    if (LookAhead_Assignment(tokens) == ELookAheadCertainties::CertainlyPresent) return Parse_Assignment(tokens);

    AbstractExpressionNode* expressionNode = Parse_Expression(tokens);
    tokens->Next(); // Consume STATEMENT_END_TOKEN
    return expressionNode;
}

ELookAheadCertainties PredictiveParser::LookAhead_Assignment(TokenList* tokens)
{
    if (LookAhead_Mutable(tokens) != ELookAheadCertainties::CertainlyPresent) return ELookAheadCertainties::CertainlyNotPresent;

    return LookAhead_AssignOperator(tokens);
}
AssignmentNode* PredictiveParser::Parse_Assignment(TokenList* tokens)
{
    std::string variableName = tokens->Next<IdentifierToken>()->GetValue();

    // If it's not a value assignment, it's a simple assignment
    if (LookAhead_ValueAssignOperator(tokens) == ELookAheadCertainties::CertainlyNotPresent) return new AssignmentNode(variableName, Parse_AssignOperator(tokens));

    EAssignOperators assignOperator = Parse_AssignOperator(tokens);
    AbstractExpressionNode* expression = Parse_Expression(tokens);

    return new ValueAssignmentNode(variableName, assignOperator, expression);
}

ELookAheadCertainties PredictiveParser::LookAhead_AssignOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.DECREMENT_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return LookAhead_ValueAssignOperator(tokens);
}
EAssignOperators PredictiveParser::Parse_AssignOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.INCREMENT_OPERATOR_TOKEN)) return EAssignOperators::INCREMENT;
    if (tokens->IsPeekOfTokenType(ConstTokens.DECREMENT_OPERATOR_TOKEN)) return EAssignOperators::DECREMENT;

    return Parse_ValueAssignOperator(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_ValueAssignOperator(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(ConstTokens.ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(ConstTokens.MOD_ASSIGN_OPERATOR_TOKEN)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
EAssignOperators PredictiveParser::Parse_ValueAssignOperator(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> token = tokens->Next();

    if (token->IsThisToken(ConstTokens.ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::ASSIGN;
    if (token->IsThisToken(ConstTokens.ADD_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::ADD_ASSIGN;
    if (token->IsThisToken(ConstTokens.SUB_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::SUB_ASSIGN;
    if (token->IsThisToken(ConstTokens.MUL_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::MUL_ASSIGN;
    if (token->IsThisToken(ConstTokens.DIV_ASSIGN_OPERATOR_TOKEN)) return EAssignOperators::DIV_ASSIGN;
    
    return EAssignOperators::MOD_ASSIGN;
}

ELookAheadCertainties PredictiveParser::LookAhead_KeywordStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.IF_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.RETURN_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.WHILE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.FOR_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.BREAK_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;
    if (tokens->IsPeekOfTokenType(Keywords.CONTINUE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
AbstractKeywordStatementNode* PredictiveParser::Parse_KeywordStatement(TokenList* tokens)
{
    std::shared_ptr<AbstractToken> token = tokens->Next();

    if (token->IsThisToken(Keywords.IF_KEYWORD)) return Parse_IfStatement(tokens);
    if (token->IsThisToken(Keywords.RETURN_KEYWORD)) return Parse_ReturnStatement(tokens);
    if (token->IsThisToken(Keywords.WHILE_KEYWORD)) return Parse_WhileStatement(tokens);
    if (token->IsThisToken(Keywords.FOR_KEYWORD)) return Parse_ForStatement(tokens);
    if (token->IsThisToken(Keywords.BREAK_KEYWORD)) return Parse_BreakStatement(tokens);

    return Parse_ContinueStatement(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_IfStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.IF_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
IfStatementNode* PredictiveParser::Parse_IfStatement(TokenList* tokens)
{
    tokens->Next(); // Consume OPEN_PARENTHESIS_TOKEN

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next(); // Consume CLOSE_PARENTHESIS_TOKEN

    AbstractStatementNode* statement = Parse_Statement(tokens);

    std::vector<ElifStatementNode*>* elifStatements = nullptr;

    while (LookAhead_ElifStatement(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        if (elifStatements == nullptr) elifStatements = new std::vector<ElifStatementNode*>();

        elifStatements->push_back(Parse_ElifStatement(tokens));
    }

    AbstractStatementNode* elseStatement = nullptr;

    if (LookAhead_ElseStatement(tokens) == ELookAheadCertainties::CertainlyPresent)
    {
        elseStatement = Parse_ElseStatement(tokens);
    }

    return new IfStatementNode(expression, statement, elifStatements, elseStatement);
}

ELookAheadCertainties PredictiveParser::LookAhead_ElifStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.ELIF_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ElifStatementNode* PredictiveParser::Parse_ElifStatement(TokenList* tokens)
{
    tokens->Next(); // Consume ELIF_KEYWORD
    tokens->Next(); // Consume OPEN_PARENTHESIS_TOKEN

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next(); // Consume CLOSE_PARENTHESIS_TOKEN

    AbstractStatementNode* statement = Parse_Statement(tokens);

    return new ElifStatementNode(expression, statement);
}

ELookAheadCertainties PredictiveParser::LookAhead_ElseStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.ELSE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
AbstractStatementNode* PredictiveParser::Parse_ElseStatement(TokenList* tokens)
{
    tokens->Next(); // Consume ELSE_KEYWORD

    return Parse_Statement(tokens);
}

ELookAheadCertainties PredictiveParser::LookAhead_ReturnStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.RETURN_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ReturnStatementNode* PredictiveParser::Parse_ReturnStatement(TokenList* tokens)
{
    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next(); // Consume STATEMENT_END_TOKEN

    return new ReturnStatementNode(expression);
}

ELookAheadCertainties PredictiveParser::LookAhead_WhileStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.WHILE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
WhileStatementNode* PredictiveParser::Parse_WhileStatement(TokenList* tokens)
{
    tokens->Next(); // Consume OPEN_PARENTHESIS_TOKEN

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next(); // Consume CLOSE_PARENTHESIS_TOKEN

    return new WhileStatementNode(expression, Parse_Statement(tokens));
}

ELookAheadCertainties PredictiveParser::LookAhead_ForStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.FOR_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ForStatementNode* PredictiveParser::Parse_ForStatement(TokenList* tokens)
{
    tokens->Next(); // Consume OPEN_PARENTHESIS_TOKEN

    VarDeclarationNode* initialization = Parse_VarDeclaration(tokens);
    AbstractExpressionNode* condition = Parse_Expression(tokens);
    AbstractStatementNode* increment = Parse_Statement(tokens);
    
    tokens->Next(); // Consume CLOSE_PARENTHESIS_TOKEN

    return new ForStatementNode(initialization, condition, increment, Parse_Statement(tokens));
}

ELookAheadCertainties PredictiveParser::LookAhead_BreakStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.BREAK_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
BreakStatementNode* PredictiveParser::Parse_BreakStatement(TokenList* tokens)
{
    tokens->Next(); // Consume STATEMENT_END_TOKEN
    return new BreakStatementNode();
}

ELookAheadCertainties PredictiveParser::LookAhead_ContinueStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Keywords.CONTINUE_KEYWORD)) return ELookAheadCertainties::CertainlyPresent;

    return ELookAheadCertainties::CertainlyNotPresent;
}
ContinueStatementNode* PredictiveParser::Parse_ContinueStatement(TokenList* tokens)
{
    tokens->Next(); // Consume STATEMENT_END_TOKEN
    return new ContinueStatementNode();
}

