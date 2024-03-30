#pragma once

#include <iostream>

#include "../tokens/TokenList.cpp"
#include "ELookAheadCertainties.cpp"
#include "../syntaxTree/SyntaxTree.cpp"

#pragma region Nodes
#include "../syntaxTree/nodes/line/CodeLineNode.cpp"

#pragma region Declarations
#include "../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/declarationAttributes/DeclarationAttributes.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/ParameterDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/types/FunctionReturnTypeNode.cpp"

#pragma endregion

#pragma endregion


static class PredictiveParser {
public:
    SyntaxTree* Parse(TokenList* tokens);

private:
    ELookAheadCertainties LookAhead_Line(TokenList* tokens);
    CodeLineNode* Parse_Line(TokenList* tokens);

    // ------- Declarations -------
    #pragma region Declarations

    ELookAheadCertainties LookAhead_Declaration(TokenList* tokens);
    AbstractDeclarationNode* Parse_Declaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_ClassDeclaration(TokenList* tokens);
    ClassDeclarationNode* Parse_ClassDeclaration(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_VarFuncDeclaration(TokenList* tokens);
    AbstractVarFuncDeclarationNode* Parse_VarFuncDeclaration(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_VarDeclaration(TokenList* tokens);
    VarDeclarationNode* Parse_VarDeclaration(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_FuncDeclaration(TokenList* tokens);
    FuncDeclarationNode* Parse_FuncDeclaration(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_VarFuncDeclarationAttributes(TokenList* tokens);
    unsigned int Skip_VarFuncDeclarationAttributes(TokenList* tokens); // Returns the number of tokens that belong to VarFuncDeclarationAttributes. Allows skipping the tokens
    DeclarationAttributes Parse_VarFuncDeclarationAttributes(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Params(TokenList* tokens);
    std::vector<ParameterDeclarationNode*>* Parse_Params(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ParamDeclaration(TokenList* tokens);
    ParameterDeclarationNode* Parse_ParamDeclaration(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Body(TokenList* tokens);
    void Parse_Body(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ScopeAttribute(TokenList* tokens);
    EScopes Parse_ScopeAttribute(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_StaticAttribute(TokenList* tokens);
    bool Parse_StaticAttribute(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ReadWriteAttribute(TokenList* tokens);
    EReadWrites Parse_ReadWriteAttribute(TokenList* tokens /*, Node*/);

    #pragma endregion

    // ------- Expressions -------
    #pragma region Expressions

    ELookAheadCertainties LookAhead_Expression(TokenList* tokens);
    void Parse_Expression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_OrExpression(TokenList* tokens);
    void Parse_OrExpression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_AndExpression(TokenList* tokens);
    void Parse_AndExpression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_EqualExpression(TokenList* tokens);
    void Parse_EqualExpression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_EqualOperator(TokenList* tokens);
    void Parse_EqualOperator(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_SumExpression(TokenList* tokens);
    void Parse_SumExpression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_SumOperator(TokenList* tokens);
    void Parse_SumOperator(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_MulExpression(TokenList* tokens);
    void Parse_MulExpression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_MulOperator(TokenList* tokens);
    void Parse_MulOperator(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_UnaryExpression(TokenList* tokens);
    void Parse_UnaryExpression(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_UnaryOperator(TokenList* tokens);
    void Parse_UnaryOperator(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Value(TokenList* tokens);
    void Parse_Value(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Mutable(TokenList* tokens);
    void Parse_Mutable(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Immutable(TokenList* tokens);
    void Parse_Immutable(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Call(TokenList* tokens);
    void Parse_Call(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Constant(TokenList* tokens);
    void Parse_Constant(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_LogicalConstant(TokenList* tokens);
    void Parse_LogicalConstant(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Arguments(TokenList* tokens);
    void Parse_Arguments(TokenList* tokens /*, Node*/);

    #pragma endregion

    // ------- Statements -------
    #pragma region Statements

    ELookAheadCertainties LookAhead_Statement(TokenList* tokens);
    void Parse_Statement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_Assignment(TokenList* tokens);
    void Parse_Assignment(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_AssignOperator(TokenList* tokens);
    void Parse_AssignOperator(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ValueAssignOperator(TokenList* tokens);
    void Parse_ValueAssignOperator(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_KeywordStatement(TokenList* tokens);
    void Parse_KeywordStatement(TokenList* tokens /*, Node*/);

    // ------- Keyword Statements -------
    #pragma region KeywordStatements

    ELookAheadCertainties LookAhead_IfStatement(TokenList* tokens);
    void Parse_IfStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ElifStatement(TokenList* tokens);
    void Parse_ElifStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ElseStatement(TokenList* tokens);
    void Parse_ElseStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ReturnStatement(TokenList* tokens);
    void Parse_ReturnStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_WhileStatement(TokenList* tokens);
    void Parse_WhileStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ForStatement(TokenList* tokens);
    void Parse_ForStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_BreakStatement(TokenList* tokens);
    void Parse_BreakStatement(TokenList* tokens /*, Node*/);

    ELookAheadCertainties LookAhead_ContinueStatement(TokenList* tokens);
    void Parse_ContinueStatement(TokenList* tokens /*, Node*/);

    #pragma endregion
    #pragma endregion

}PredictiveParser;

SyntaxTree* PredictiveParser::Parse(TokenList* tokens)
{
    SyntaxTree* syntaxTree = new SyntaxTree();

    while (tokens->HasNext())
    {
        if (LookAhead_Line(tokens) == ELookAheadCertainties::CertainlyPresent)
        {
            syntaxTree->AddCodeLineNode(Parse_Line(tokens));
        }
        else
        {
            std::cout << "Unexpected token during parsing: " + tokens->Next()->ToString() + "\n";
        }
    }

    return syntaxTree;
}