#pragma once

#include "../../assembly/AssemblyCode.cpp"
#include "../../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/expression/AbstractValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../../syntaxTree/nodes/line/expression/OperatorExpressionNode.cpp"
#include "../../syntaxTree/nodes/line/expression/UnaryExpressionNode.cpp"
#include "../../syntaxTree/nodes/line/expression/functionCall/CallNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/AbstractConstValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/StaticValueChainNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/StringConstValueNode.cpp"
#include "../../syntaxTree/nodes/line/expression/values/ValueChainNode.cpp"
#include "../../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"
#include "ISyntaxTreeNodeIn.cpp"

class SyntaxTreeTraverser
{
   public:
    AssemblyCode* GenerateCodeBlock(ISyntaxTreeNodeIn* nodeIn, CodeblockNode* codeBlock);

    AssemblyCode* GenerateLine(ISyntaxTreeNodeIn* nodeIn, AbstractLineNode* line);

    AssemblyCode* GenerateDeclaration(ISyntaxTreeNodeIn* nodeIn, AbstractDeclarationNode* declaration);
    AssemblyCode* GenerateStatement(ISyntaxTreeNodeIn* nodeIn, AbstractStatementNode* statement);
    AssemblyCode* GenerateKeywordStatement(ISyntaxTreeNodeIn* nodeIn, AbstractKeywordStatementNode* statement);

    AssemblyCode* GenerateExpression(ISyntaxTreeNodeIn* nodeIn, AbstractExpressionNode* expression);

    AssemblyCode* GenerateValue(ISyntaxTreeNodeIn* nodeIn, AbstractValueNode* value);
    AssemblyCode* GenerateConstValue(ISyntaxTreeNodeIn* nodeIn, AbstractConstValueNode* value);
};

AssemblyCode* SyntaxTreeTraverser::GenerateCodeBlock(ISyntaxTreeNodeIn* nodeIn, CodeblockNode* codeBlock)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (size_t i = 0; i < codeBlock->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(nodeIn, codeBlock->GetLine(i)));
    }

    return assemblyCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateLine(ISyntaxTreeNodeIn* nodeIn, AbstractLineNode* line)
{
    if (line == nullptr)
    {
        std::cout << "Line is null\n";
        return nullptr;
    }

    // FIXME: Solve this without dynamic_cast; visitor pattern with
    // ISyntaxTreeTraverser?
    if (dynamic_cast<AbstractDeclarationNode*>(line) != nullptr)
    {
        return GenerateDeclaration(nodeIn, dynamic_cast<AbstractDeclarationNode*>(line));
    }

    // Generate statement
    return GenerateStatement(nodeIn, dynamic_cast<AbstractStatementNode*>(line));
};

AssemblyCode* SyntaxTreeTraverser::GenerateDeclaration(ISyntaxTreeNodeIn* nodeIn, AbstractDeclarationNode* declaration)
{
    if (dynamic_cast<VarDeclarationNode*>(declaration) != nullptr)
    {
        return nodeIn->GenerateVarDeclaration(dynamic_cast<VarDeclarationNode*>(declaration));
    }

    if (dynamic_cast<FuncDeclarationNode*>(declaration) != nullptr)
    {
        return nodeIn->GenerateFuncDeclaration(dynamic_cast<FuncDeclarationNode*>(declaration));
    }

    return nodeIn->GenerateClassDeclaration(dynamic_cast<ClassDeclarationNode*>(declaration));
}

AssemblyCode* SyntaxTreeTraverser::GenerateStatement(ISyntaxTreeNodeIn* nodeIn, AbstractStatementNode* statement)
{
    if (dynamic_cast<EmptyStatementNode*>(statement) != nullptr)
    {
        return nullptr;  // No code if empty statement
    }

    if (dynamic_cast<BodyNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateBody(dynamic_cast<BodyNode*>(statement));
        /*
        if (!environmentLock)
        {
            // TODO: New environment; where does it know what type of environment
            // to create?
            ISyntaxTreeNodeIn.PushEnvironment(std::make_shared<ScopeSpecificEnvironment>());
            AssemblyCode* body = GenerateBody(dynamic_cast<BodyNode*>(statement));
            ISyntaxTreeNodeIn.PopEnvironment();
            return body;
        }

        return GenerateBody(nodeIn, dynamic_cast<BodyNode*>(statement));*/
    }

    if (dynamic_cast<AbstractKeywordStatementNode*>(statement) != nullptr)
    {
        return GenerateKeywordStatement(nodeIn, dynamic_cast<AbstractKeywordStatementNode*>(statement));
    }

    if (dynamic_cast<AbstractExpressionNode*>(statement) != nullptr)
    {
        return GenerateExpression(nodeIn, dynamic_cast<AbstractExpressionNode*>(statement));
    }

    // TODO: Check for other types of statements

    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateKeywordStatement(ISyntaxTreeNodeIn* nodeIn,
                                                            AbstractKeywordStatementNode* statement)
{
    if (dynamic_cast<IfStatementNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateIfStatement(dynamic_cast<IfStatementNode*>(statement));
    }

    if (dynamic_cast<ReturnStatementNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateReturnStatement(dynamic_cast<ReturnStatementNode*>(statement));
    }

    if (dynamic_cast<WhileStatementNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateWhileStatement(dynamic_cast<WhileStatementNode*>(statement));
    }

    if (dynamic_cast<ForStatementNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateForStatement(dynamic_cast<ForStatementNode*>(statement));
    }

    if (dynamic_cast<ContinueStatementNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateContinueStatement(dynamic_cast<ContinueStatementNode*>(statement));
    }

    if (dynamic_cast<BreakStatementNode*>(statement) != nullptr)
    {
        return nodeIn->GenerateBreakStatement(dynamic_cast<BreakStatementNode*>(statement));
    }

    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateExpression(ISyntaxTreeNodeIn* nodeIn, AbstractExpressionNode* expression)
{
    if (dynamic_cast<AssignmentNode*>(expression) != nullptr)
    {
        return nodeIn->GenerateAssignment(dynamic_cast<AssignmentNode*>(expression));
    }

    if (dynamic_cast<OperatorExpressionNode*>(expression) != nullptr)
    {
        return nodeIn->GenerateBinaryOperation(dynamic_cast<OperatorExpressionNode*>(expression));
    }

    if (dynamic_cast<UnaryExpressionNode*>(expression) != nullptr)
    {
        return nodeIn->GenerateUnaryOperation(dynamic_cast<UnaryExpressionNode*>(expression));
    }

    // If is not assignment, binary or unary, then it is a AbstractValueNode
    return GenerateValue(nodeIn, dynamic_cast<AbstractValueNode*>(expression));
}

AssemblyCode* SyntaxTreeTraverser::GenerateValue(ISyntaxTreeNodeIn* nodeIn, AbstractValueNode* value)
{
    if (dynamic_cast<ValueChainNode*>(value) != nullptr)
    {
        return nodeIn->GenerateValueChain(dynamic_cast<ValueChainNode*>(value));
    }

    if (dynamic_cast<StaticValueChainNode*>(value) != nullptr)
    {
        return nodeIn->GenerateStaticValueChain(dynamic_cast<StaticValueChainNode*>(value));
    }

    if (dynamic_cast<AbstractConstValueNode*>(value) != nullptr)
    {
        return GenerateConstValue(nodeIn, dynamic_cast<AbstractConstValueNode*>(value));
    }

    if (dynamic_cast<IDValueNode*>(value) != nullptr)
    {
        return nodeIn->GenerateIDValue(dynamic_cast<IDValueNode*>(value));
    }

    if (dynamic_cast<CallNode*>(value) != nullptr)
    {
        return nodeIn->GenerateCall(dynamic_cast<CallNode*>(value));
    }

    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateConstValue(ISyntaxTreeNodeIn* nodeIn, AbstractConstValueNode* value)
{
    if (dynamic_cast<LogicalConstValueNode*>(value) != nullptr)
    {
        return nodeIn->GenerateConstLogical(dynamic_cast<LogicalConstValueNode*>(value));
    }

    if (dynamic_cast<NumberConstValueNode*>(value) != nullptr)
    {
        return nodeIn->GenerateConstNumber(dynamic_cast<NumberConstValueNode*>(value));
    }

    if (dynamic_cast<StringConstValueNode*>(value) != nullptr)
    {
        return nodeIn->GenerateConstString(dynamic_cast<StringConstValueNode*>(value));
    }

    return nullptr;
}
