#pragma once

#include <iostream>

#include "../tokens/TokenList.cpp"
#include "ELookAheadCertainties.cpp"
#include "../syntaxTree/SyntaxTree.cpp"

#pragma region Nodes
#include "../syntaxTree/nodes/line/AbstractLineNode.cpp"

#pragma region Declarations
#include "../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/declarationAttributes/DeclarationAttributes.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/ParameterDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/types/FunctionReturnTypeNode.cpp"
#include "../syntaxTree/nodes/line/declaration/BodyNode.cpp"

#pragma endregion

#pragma region Expressions
#include "../syntaxTree/nodes/line/expression/AbstractExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/IDValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/NumberConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/StringConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/LogicalConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/functionCall/CallNode.cpp"
#include "../syntaxTree/nodes/line/expression/OperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EUnaryOperators.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EOperators.cpp"

#pragma endregion

#pragma endregion


static class PredictiveParser {
public:
    SyntaxTree* Parse(TokenList* tokens);

private:
    ELookAheadCertainties LookAhead_Line(TokenList* tokens);
    AbstractLineNode* Parse_Line(TokenList* tokens);

    // ------- Declarations -------
    #pragma region Declarations

    ELookAheadCertainties LookAhead_Declaration(TokenList* tokens);
    AbstractDeclarationNode* Parse_Declaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_ClassDeclaration(TokenList* tokens);
    ClassDeclarationNode* Parse_ClassDeclaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_VarFuncDeclaration(TokenList* tokens);
    AbstractVarFuncDeclarationNode* Parse_VarFuncDeclaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_VarDeclaration(TokenList* tokens);
    VarDeclarationNode* Parse_VarDeclaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_FuncDeclaration(TokenList* tokens);
    FuncDeclarationNode* Parse_FuncDeclaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_VarFuncDeclarationAttributes(TokenList* tokens, unsigned int offset = 0); // Has offset to allow for skipping tokens
    unsigned int Skip_VarFuncDeclarationAttributes(TokenList* tokens); // Returns the number of tokens that belong to VarFuncDeclarationAttributes. Allows skipping the tokens
    DeclarationAttributes Parse_VarFuncDeclarationAttributes(TokenList* tokens);

    ELookAheadCertainties LookAhead_Params(TokenList* tokens);
    std::vector<ParameterDeclarationNode*>* Parse_Params(TokenList* tokens);

    ELookAheadCertainties LookAhead_ParamDeclaration(TokenList* tokens);
    ParameterDeclarationNode* Parse_ParamDeclaration(TokenList* tokens);

    ELookAheadCertainties LookAhead_Body(TokenList* tokens);
    BodyNode* Parse_Body(TokenList* tokens);

    ELookAheadCertainties LookAhead_ScopeAttribute(TokenList* tokens, unsigned int offset = 0);
    EScopes Parse_ScopeAttribute(TokenList* tokens);

    ELookAheadCertainties LookAhead_StaticAttribute(TokenList* tokens, unsigned int offset = 0);
    bool Parse_StaticAttribute(TokenList* tokens);

    ELookAheadCertainties LookAhead_ReadWriteAttribute(TokenList* tokens, unsigned int offset = 0);
    EReadWrites Parse_ReadWriteAttribute(TokenList* tokens);

    #pragma endregion

    // ------- Expressions -------
    #pragma region Expressions

    ELookAheadCertainties LookAhead_Expression(TokenList* tokens);
    AbstractExpressionNode* Parse_Expression(TokenList* tokens);

    ELookAheadCertainties LookAhead_OrExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_OrExpression(TokenList* tokens);

    ELookAheadCertainties LookAhead_AndExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_AndExpression(TokenList* tokens);

    ELookAheadCertainties LookAhead_EqualExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_EqualExpression(TokenList* tokens);

    ELookAheadCertainties LookAhead_EqualOperator(TokenList* tokens);
    EOperators Parse_EqualOperator(TokenList* tokens);

    ELookAheadCertainties LookAhead_SumExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_SumExpression(TokenList* tokens);

    ELookAheadCertainties LookAhead_SumOperator(TokenList* tokens);
    EOperators Parse_SumOperator(TokenList* tokens);

    ELookAheadCertainties LookAhead_MulExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_MulExpression(TokenList* tokens);

    ELookAheadCertainties LookAhead_MulOperator(TokenList* tokens);
    EOperators Parse_MulOperator(TokenList* tokens);

    ELookAheadCertainties LookAhead_UnaryExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_UnaryExpression(TokenList* tokens);

    ELookAheadCertainties LookAhead_UnaryOperator(TokenList* tokens);
    EUnaryOperators Parse_UnaryOperator(TokenList* tokens);

    ELookAheadCertainties LookAhead_Value(TokenList* tokens);
    AbstractExpressionNode* Parse_Value(TokenList* tokens);

    ELookAheadCertainties LookAhead_Mutable(TokenList* tokens);
    IDValueNode* Parse_Mutable(TokenList* tokens);

    ELookAheadCertainties LookAhead_Immutable(TokenList* tokens);
    AbstractExpressionNode* Parse_Immutable(TokenList* tokens);

    ELookAheadCertainties LookAhead_Call(TokenList* tokens);
    CallNode* Parse_Call(TokenList* tokens);

    ELookAheadCertainties LookAhead_Constant(TokenList* tokens);
    AbstractConstValueNode* Parse_Constant(TokenList* tokens);

    ELookAheadCertainties LookAhead_LogicalConstant(TokenList* tokens);
    LogicalConstValueNode* Parse_LogicalConstant(TokenList* tokens);

    ELookAheadCertainties LookAhead_Arguments(TokenList* tokens);
    std::vector<CallArgument*> Parse_Arguments(TokenList* tokens);

    #pragma endregion

    // ------- Statements -------
    #pragma region Statements

    ELookAheadCertainties LookAhead_Statement(TokenList* tokens);
    void Parse_Statement(TokenList* tokens);

    ELookAheadCertainties LookAhead_Assignment(TokenList* tokens);
    void Parse_Assignment(TokenList* tokens);

    ELookAheadCertainties LookAhead_AssignOperator(TokenList* tokens);
    void Parse_AssignOperator(TokenList* tokens);

    ELookAheadCertainties LookAhead_ValueAssignOperator(TokenList* tokens);
    void Parse_ValueAssignOperator(TokenList* tokens);

    ELookAheadCertainties LookAhead_KeywordStatement(TokenList* tokens);
    void Parse_KeywordStatement(TokenList* tokens);

    // ------- Keyword Statements -------
    #pragma region KeywordStatements

    ELookAheadCertainties LookAhead_IfStatement(TokenList* tokens);
    void Parse_IfStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_ElifStatement(TokenList* tokens);
    void Parse_ElifStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_ElseStatement(TokenList* tokens);
    void Parse_ElseStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_ReturnStatement(TokenList* tokens);
    void Parse_ReturnStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_WhileStatement(TokenList* tokens);
    void Parse_WhileStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_ForStatement(TokenList* tokens);
    void Parse_ForStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_BreakStatement(TokenList* tokens);
    void Parse_BreakStatement(TokenList* tokens);

    ELookAheadCertainties LookAhead_ContinueStatement(TokenList* tokens);
    void Parse_ContinueStatement(TokenList* tokens);

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