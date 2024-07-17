#pragma once

#include <iostream>

#include "../syntaxTree/SyntaxTree.cpp"
#include "../tokens/TokenList.cpp"

#pragma region Nodes
#include "../syntaxTree/nodes/line/AbstractLineNode.cpp"

#pragma region Declarations
#include "../syntaxTree/nodes/line/declaration/DeclarationAttributes.cpp"
#include "../syntaxTree/nodes/line/declaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ParameterDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/PropertyDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/TypeDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/types/FunctionReturnTypeNode.cpp"

#pragma endregion

#pragma region Expressions
#include "../syntaxTree/nodes/line/expression/AbstractExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../syntaxTree/nodes/line/expression/BinaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EAssignOperators.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EOperators.cpp"
#include "../syntaxTree/nodes/line/expression/operators/EUnaryOperators.cpp"
#include "../syntaxTree/nodes/line/expression/values/CallNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/ParenthesisExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/StructNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/VariableNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/FloatConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/IntConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/LogicalConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/StringConstValueNode.cpp"

#pragma endregion

#pragma region Statements
#include "../syntaxTree/nodes/line/statement/BodyNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ElifStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"

#pragma endregion

#pragma endregion

static class PredictiveParser
{
   public:
    SyntaxTree* Parse(TokenList* tokens);

   private:
    bool LookAhead_GlobalCode(TokenList* tokens);
    GlobalCodeNode* Parse_GlobalCode(TokenList* tokens);

    bool LookAhead_BodyCode(TokenList* tokens);
    BodyCodeNode* Parse_BodyCode(TokenList* tokens);

    bool LookAhead_Line(TokenList* tokens);
    AbstractLineNode* Parse_Line(TokenList* tokens);

    bool LookAhead_TypeDefCode(TokenList* tokens);
    TypeDefCodeNode* Parse_TypeDefCode(TokenList* tokens);

// ------- Declarations -------
#pragma region Declarations

    bool LookAhead_Declaration(TokenList* tokens);
    AbstractDeclarationNode* Parse_Declaration(TokenList* tokens);

    bool LookAhead_VarDeclaration(TokenList* tokens);
    VarDeclarationNode* Parse_VarDeclaration(TokenList* tokens);

    bool LookAhead_FuncDeclaration(TokenList* tokens);
    FuncDeclarationNode* Parse_FuncDeclaration(TokenList* tokens);

    bool LookAhead_DeclarationAttributes(TokenList* tokens,
                                         unsigned int offset = 0);  // Has offset to allow for skipping tokens
    unsigned int Skip_DeclarationAttributes(TokenList* tokens);     // Returns the number of tokens that belong to DeclarationAttributes.
                                                                    // Allows skipping the tokens
    DeclarationAttributes Parse_DeclarationAttributes(TokenList* tokens);

    bool LookAhead_TypeDeclaration(TokenList* tokens);
    TypeDeclarationNode* Parse_TypeDeclaration(TokenList* tokens);

    bool LookAhead_PropertyDeclaration(TokenList* tokens);
    PropertyDeclarationNode* Parse_PropertyDeclaration(TokenList* tokens);

    bool LookAhead_Params(TokenList* tokens);
    std::vector<ParameterDeclarationNode*>* Parse_Params(TokenList* tokens);

    bool LookAhead_ParamDeclaration(TokenList* tokens);
    ParameterDeclarationNode* Parse_ParamDeclaration(TokenList* tokens);

    bool LookAhead_Body(TokenList* tokens);
    BodyNode* Parse_Body(TokenList* tokens);

    bool LookAhead_FinalAttribute(TokenList* tokens, unsigned int offset = 0);
    bool Parse_FinalAttribute(TokenList* tokens);

    bool LookAhead_InlineAttribute(TokenList* tokens, unsigned int offset = 0);
    bool Parse_InlineAttribute(TokenList* tokens);

#pragma endregion

// ------- Expressions -------
#pragma region Expressions

    bool LookAhead_Expression(TokenList* tokens);
    AbstractExpressionNode* Parse_Expression(TokenList* tokens);

    bool LookAhead_AssignmentExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_AssignmentExpression(TokenList* tokens);

    bool LookAhead_AssignOperator(TokenList* tokens, unsigned int offset = 0);
    EAssignOperators Parse_AssignOperator(TokenList* tokens);

    bool LookAhead_OrExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_OrExpression(TokenList* tokens);

    bool LookAhead_AndExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_AndExpression(TokenList* tokens);

    bool LookAhead_EqualExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_EqualExpression(TokenList* tokens);

    bool LookAhead_EqualOperator(TokenList* tokens);
    EOperators Parse_EqualOperator(TokenList* tokens);

    bool LookAhead_SumExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_SumExpression(TokenList* tokens);

    bool LookAhead_SumOperator(TokenList* tokens);
    EOperators Parse_SumOperator(TokenList* tokens);

    bool LookAhead_MulExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_MulExpression(TokenList* tokens);

    bool LookAhead_MulOperator(TokenList* tokens);
    EOperators Parse_MulOperator(TokenList* tokens);

    bool LookAhead_UnaryExpression(TokenList* tokens);
    AbstractExpressionNode* Parse_UnaryExpression(TokenList* tokens);

    bool LookAhead_PreUnaryOperator(TokenList* tokens);
    EPreUnaryOperators Parse_PreUnaryOperator(TokenList* tokens);

    bool LookAhead_PostUnaryOperator(TokenList* tokens);
    EPostUnaryOperators Parse_PostUnaryOperator(TokenList* tokens);

    bool LookAhead_Value(TokenList* tokens);
    AbstractValueNode* Parse_Value(TokenList* tokens);

    bool LookAhead_Call(TokenList* tokens);
    CallNode* Parse_Call(TokenList* tokens);

    bool LookAhead_Arguments(TokenList* tokens);
    std::vector<AbstractExpressionNode*> Parse_Arguments(TokenList* tokens);

    bool LookAhead_Parenthesis_Expression(TokenList* tokens);
    ParenthesisExpressionNode* Parse_Parenthesis_Expression(TokenList* tokens);

    bool LookAhead_Struct(TokenList* tokens);
    StructNode* Parse_Struct(TokenList* tokens);

    bool LookAhead_Variable(TokenList* tokens);
    VariableNode* Parse_Variable(TokenList* tokens);

    bool LookAhead_Const(TokenList* tokens);
    AbstractConstValueNode* Parse_Const(TokenList* tokens);

    bool LookAhead_LogicalConst(TokenList* tokens);
    LogicalConstValueNode* Parse_LogicalConst(TokenList* tokens);

#pragma endregion

// ------- Statements -------
#pragma region Statements

    bool LookAhead_Statement(TokenList* tokens);
    AbstractStatementNode* Parse_Statement(TokenList* tokens);

    bool LookAhead_KeywordStatement(TokenList* tokens);
    AbstractKeywordStatementNode* Parse_KeywordStatement(TokenList* tokens);

// ------- Keyword Statements -------
#pragma region KeywordStatements

    bool LookAhead_IfStatement(TokenList* tokens);
    IfStatementNode* Parse_IfStatement(TokenList* tokens);

    bool LookAhead_ElifStatement(TokenList* tokens);
    ElifStatementNode* Parse_ElifStatement(TokenList* tokens);

    bool LookAhead_ElseStatement(TokenList* tokens);
    AbstractStatementNode* Parse_ElseStatement(TokenList* tokens);

    bool LookAhead_ReturnStatement(TokenList* tokens);
    ReturnStatementNode* Parse_ReturnStatement(TokenList* tokens);

    bool LookAhead_WhileStatement(TokenList* tokens);
    WhileStatementNode* Parse_WhileStatement(TokenList* tokens);

    bool LookAhead_ForStatement(TokenList* tokens);
    ForStatementNode* Parse_ForStatement(TokenList* tokens);

    bool LookAhead_BreakStatement(TokenList* tokens);
    BreakStatementNode* Parse_BreakStatement(TokenList* tokens);

    bool LookAhead_ContinueStatement(TokenList* tokens);
    ContinueStatementNode* Parse_ContinueStatement(TokenList* tokens);

#pragma endregion
#pragma endregion

} PredictiveParser;

SyntaxTree* PredictiveParser::Parse(TokenList* tokens)
{
    SyntaxTree* syntaxTree = new SyntaxTree();

    if (LookAhead_GlobalCode(tokens))
    {
        syntaxTree->SetCode(Parse_GlobalCode(tokens));
    }

    if (tokens->HasNext())
    {
        std::cerr << "Unexpected token: " + tokens->Peek()->ToString() + "\n Terminating compiler." << std::endl;
    }

    return syntaxTree;
}