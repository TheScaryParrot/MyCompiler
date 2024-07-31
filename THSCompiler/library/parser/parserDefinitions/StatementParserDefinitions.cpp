#pragma once

#include "../../tokens/Keywords.cpp"
#include "../../tokens/Tokens.cpp"
#include "../PredictiveParser.hpp"

bool PredictiveParser::LookAhead_Statement(TokenList* tokens)
{
    return tokens->IsPeekOfTokenType(Tokens.STATEMENT_END_TOKEN) || LookAhead_Body(tokens) || LookAhead_KeywordStatement(tokens) ||
           LookAhead_Expression(tokens);
}
AbstractStatementNode* PredictiveParser::Parse_Statement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Tokens.STATEMENT_END_TOKEN))
    {
        tokens->Next();  // Consume STATEMENT_END_TOKEN
        return new EmptyStatementNode();
    }

    if (LookAhead_Body(tokens) == true) return Parse_Body(tokens);
    if (tokens->Peek()->IsInstruction()) return Parse_KeywordStatement(tokens);

    AbstractExpressionNode* expressionNode = Parse_Expression(tokens);
    tokens->Next();  // Consume STATEMENT_END_TOKEN
    return expressionNode;
}

bool PredictiveParser::LookAhead_KeywordStatement(TokenList* tokens)
{
    return LookAhead_IfStatement(tokens) || LookAhead_ReturnStatement(tokens) || LookAhead_WhileStatement(tokens) || LookAhead_ForStatement(tokens) ||
           LookAhead_BreakStatement(tokens) || LookAhead_ContinueStatement(tokens);
}
AbstractKeywordStatementNode* PredictiveParser::Parse_KeywordStatement(TokenList* tokens)
{
    std::shared_ptr<Token> token = tokens->Next();

    if (token->IsThisToken(Keywords.IF_KEYWORD)) return Parse_IfStatement(tokens);
    if (token->IsThisToken(Keywords.RETURN_KEYWORD)) return Parse_ReturnStatement(tokens);
    if (token->IsThisToken(Keywords.WHILE_KEYWORD)) return Parse_WhileStatement(tokens);
    if (token->IsThisToken(Keywords.FOR_KEYWORD)) return Parse_ForStatement(tokens);
    if (token->IsThisToken(Keywords.BREAK_KEYWORD)) return Parse_BreakStatement(tokens);
    if (token->IsThisToken(Keywords.CONTINUE_KEYWORD)) return Parse_ContinueStatement(tokens);

    Logger.Log("Unknown keyword statement: " + token->ToString(), Logger::ERROR);
    return nullptr;
}

bool PredictiveParser::LookAhead_IfStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.IF_KEYWORD); }
IfStatementNode* PredictiveParser::Parse_IfStatement(TokenList* tokens)
{
    tokens->Next();  // Consume OPEN_PARENTHESIS_TOKEN

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next();  // Consume CLOSE_PARENTHESIS_TOKEN

    AbstractStatementNode* statement = Parse_Statement(tokens);

    std::vector<ElifStatementNode*> elifStatements;

    while (LookAhead_ElifStatement(tokens) == true)
    {
        elifStatements.push_back(Parse_ElifStatement(tokens));
    }

    AbstractStatementNode* elseStatement = nullptr;

    if (LookAhead_ElseStatement(tokens) == true)
    {
        elseStatement = Parse_ElseStatement(tokens);
    }

    return new IfStatementNode(expression, statement, elifStatements, elseStatement);
}

bool PredictiveParser::LookAhead_ElifStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.ELIF_KEYWORD); }
ElifStatementNode* PredictiveParser::Parse_ElifStatement(TokenList* tokens)
{
    tokens->Next();  // Consume ELIF_KEYWORD
    tokens->Next();  // Consume OPEN_PARENTHESIS_TOKEN

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next();  // Consume CLOSE_PARENTHESIS_TOKEN

    AbstractStatementNode* statement = Parse_Statement(tokens);

    return new ElifStatementNode(expression, statement);
}

bool PredictiveParser::LookAhead_ElseStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.ELSE_KEYWORD); }
AbstractStatementNode* PredictiveParser::Parse_ElseStatement(TokenList* tokens)
{
    tokens->Next();  // Consume ELSE_KEYWORD

    return Parse_Statement(tokens);
}

bool PredictiveParser::LookAhead_ReturnStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.RETURN_KEYWORD); }
ReturnStatementNode* PredictiveParser::Parse_ReturnStatement(TokenList* tokens)
{
    if (tokens->IsPeekOfTokenType(Tokens.STATEMENT_END_TOKEN))
    {
        tokens->Next();  // Consume STATEMENT_END_TOKEN
        return new ReturnStatementNode(nullptr);
    }

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next();  // Consume STATEMENT_END_TOKEN

    return new ReturnStatementNode(expression);
}

bool PredictiveParser::LookAhead_WhileStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.WHILE_KEYWORD); }
WhileStatementNode* PredictiveParser::Parse_WhileStatement(TokenList* tokens)
{
    tokens->Next();  // Consume OPEN_PARENTHESIS_TOKEN

    AbstractExpressionNode* expression = Parse_Expression(tokens);

    tokens->Next();  // Consume CLOSE_PARENTHESIS_TOKEN

    return new WhileStatementNode(expression, Parse_Statement(tokens));
}

bool PredictiveParser::LookAhead_ForStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.FOR_KEYWORD); }
ForStatementNode* PredictiveParser::Parse_ForStatement(TokenList* tokens)
{
    tokens->Next();  // Consume OPEN_PARENTHESIS_TOKEN

    LocalVarDeclarationNode* initialization = dynamic_cast<LocalVarDeclarationNode*>(Parse_VarDeclaration(tokens, true));

    if (initialization == nullptr)
    {
        Logger.Log("For loop initialization must be a local variable declaration", Logger::ERROR);
    }

    AbstractExpressionNode* condition = Parse_Expression(tokens);
    tokens->Next();  // Consume STATEMENT_END_TOKEN (Parse_Expression does not consume STATEMENT_END_TOKEN)

    AbstractStatementNode* increment = Parse_Statement(tokens);

    tokens->Next();  // Consume CLOSE_PARENTHESIS_TOKEN

    return new ForStatementNode(initialization, condition, increment, Parse_Statement(tokens));
}

bool PredictiveParser::LookAhead_BreakStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.BREAK_KEYWORD); }
BreakStatementNode* PredictiveParser::Parse_BreakStatement(TokenList* tokens)
{
    tokens->Next();  // Consume STATEMENT_END_TOKEN
    return new BreakStatementNode();
}

bool PredictiveParser::LookAhead_ContinueStatement(TokenList* tokens) { return tokens->IsPeekOfTokenType(Keywords.CONTINUE_KEYWORD); }
ContinueStatementNode* PredictiveParser::Parse_ContinueStatement(TokenList* tokens)
{
    tokens->Next();  // Consume STATEMENT_END_TOKEN
    return new ContinueStatementNode();
}
