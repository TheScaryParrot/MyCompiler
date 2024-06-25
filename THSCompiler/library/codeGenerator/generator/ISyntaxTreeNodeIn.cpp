#pragma once

#include "../../assembly/AssemblyCode.cpp"
#include "../../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../../syntaxTree/nodes/line/expression/OperatorExpressionNode.cpp"
#include "../../syntaxTree/nodes/line/expression/UnaryExpressionNode.cpp"
#include "../../syntaxTree/nodes/line/expression/functionCall/CallNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/IDValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/LogicalConstValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/NumberConstValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/StaticValueChainNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/StringConstValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/ValueChainNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"

class ISyntaxTreeNodeIn
{
   public:
    virtual AssemblyCode* GenerateVarDeclaration(VarDeclarationNode* declaration) = 0;
    virtual AssemblyCode* GenerateFuncDeclaration(FuncDeclarationNode* declaration) = 0;
    virtual AssemblyCode* GenerateClassDeclaration(ClassDeclarationNode* declaration) = 0;

    virtual AssemblyCode* GenerateBody(BodyNode* body, bool newEnvironment) = 0;

    virtual AssemblyCode* GenerateIfStatement(IfStatementNode* statement) = 0;
    virtual AssemblyCode* GenerateReturnStatement(ReturnStatementNode* statement) = 0;
    virtual AssemblyCode* GenerateWhileStatement(WhileStatementNode* whileStatement) = 0;
    virtual AssemblyCode* GenerateForStatement(ForStatementNode* forStatement) = 0;
    virtual AssemblyCode* GenerateContinueStatement(ContinueStatementNode* statement) = 0;
    virtual AssemblyCode* GenerateBreakStatement(BreakStatementNode* statement) = 0;

    virtual AssemblyCode* GenerateAssignment(AssignmentNode* assignmentNode) = 0;
    virtual AssemblyCode* GenerateBinaryOperation(OperatorExpressionNode* binaryOperation) = 0;
    virtual AssemblyCode* GenerateUnaryOperation(UnaryExpressionNode* unaryOperation) = 0;

    virtual AssemblyCode* GenerateValueChain(ValueChainNode* valueChain) = 0;
    virtual AssemblyCode* GenerateStaticValueChain(StaticValueChainNode* valueChain) = 0;
    virtual AssemblyCode* GenerateIDValue(IDValueNode* value) = 0;
    virtual AssemblyCode* GenerateCall(CallNode* call) = 0;
    virtual AssemblyCode* GenerateConstNumber(NumberConstValueNode* numberConst) = 0;
    virtual AssemblyCode* GenerateConstString(StringConstValueNode* stringConst) = 0;
    virtual AssemblyCode* GenerateConstLogical(LogicalConstValueNode* logicalConst) = 0;
};