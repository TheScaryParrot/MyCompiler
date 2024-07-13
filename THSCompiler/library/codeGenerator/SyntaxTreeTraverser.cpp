#pragma once

#include "../assembly/AssemblyCode.cpp"
#include "../syntaxTree/SyntaxTree.cpp"
#include "../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../syntaxTree/nodes/line/expression/BinaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/AbstractValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/CallNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/IdentifierNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/RelAccessValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/AbstractConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/LogicalConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/NumberConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/StringConstValueNode.cpp"
#include "../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"
#include "CodeGenerator.cpp"
#include "Environment.cpp"

class SyntaxTreeTraverser
{
   public:
    AssemblyCode* Traverse(SyntaxTree* syntaxTree);

   private:
    CodeGenerator* codeGenerator;

    void TraverseCodeBlock(CodeblockNode* node, AssemblyCode* assemblyCode);
    void TraverseLineNode(AbstractLineNode* node, AssemblyCode* assemblyCode);

    void TraverseDeclarationNode(AbstractDeclarationNode* node, AssemblyCode* assemblyCode);
    void TraverseVarDeclarationNode(VarDeclarationNode* node, AssemblyCode* assemblyCode);
    void TraverseFuncDeclarationNode(FuncDeclarationNode* node, AssemblyCode* assemblyCode);
    void TraverseClassDeclarationNode(ClassDeclarationNode* node, AssemblyCode* assemblyCode);

    void TraverseStatementNode(AbstractStatementNode* node, AssemblyCode* assemblyCode);
    void TraverseEmptyStatementNode(EmptyStatementNode* node, AssemblyCode* assemblyCode);
    void TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, AssemblyCode* assemblyCode);
    void TraverseBodyNode(BodyNode* node, AssemblyCode* assemblyCode);
    /// @brief Overload of TraverseBodyNode for when instead of pushing a new environment, the environment  passed as
    /// an argument is pushed(eg. used by TraverseClassDeclarationNode)
    void TraverseBodyNode(BodyNode* node, AssemblyCode* assemblyCode, Environment* environment);

    void TraverseExpressionNode(AbstractExpressionNode* node, AssemblyCode* assemblyCode);
    void TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, AssemblyCode* assemblyCode);
    void TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, AssemblyCode* assemblyCode);
    void TraverseAssignmentNode(AssignmentNode* node, AssemblyCode* assemblyCode);

    void TraverseValueNode(AbstractValueNode* node, AssemblyCode* assemblyCode);
    void TraverseCallNode(CallNode* node, AssemblyCode* assemblyCode);
    void TraverseIdentifierNode(IdentifierNode* node, AssemblyCode* assemblyCode);
    void TraverseRelAccessValueNode(RelAccessValueNode* node, AssemblyCode* assemblyCode);

    void TraverseAbstractConstValueNode(AbstractConstValueNode* node, AssemblyCode* assemblyCode);
    void TraverseLogicalConstValueNode(LogicalConstValueNode* node, AssemblyCode* assemblyCode);
    void TraverseNumberConstValueNode(NumberConstValueNode* node, AssemblyCode* assemblyCode);
    void TraverseStringConstValueNode(StringConstValueNode* node, AssemblyCode* assemblyCode);
};

AssemblyCode* SyntaxTreeTraverser::Traverse(SyntaxTree* syntaxTree)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    TraverseCodeBlock(syntaxTree->GetCodeBlock(), assemblyCode);

    return assemblyCode;
}

void SyntaxTreeTraverser::TraverseCodeBlock(CodeblockNode* node, AssemblyCode* assemblyCode)
{
    for (unsigned int i = 0; i < node->GetLineCount(); i++)
    {
        AbstractLineNode* lineNode = node->GetLine(i);

        if (lineNode == nullptr) continue;

        TraverseLineNode(lineNode, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseLineNode(AbstractLineNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<AbstractDeclarationNode*>(node) != nullptr)
    {
        TraverseDeclarationNode(dynamic_cast<AbstractDeclarationNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AbstractStatementNode*>(node) != nullptr)
    {
        TraverseStatementNode(dynamic_cast<AbstractStatementNode*>(node), assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseDeclarationNode(AbstractDeclarationNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<VarDeclarationNode*>(node) != nullptr)
    {
        TraverseVarDeclarationNode(dynamic_cast<VarDeclarationNode*>(node), assemblyCode);
    }

    if (dynamic_cast<FuncDeclarationNode*>(node) != nullptr)
    {
        TraverseFuncDeclarationNode(dynamic_cast<FuncDeclarationNode*>(node), assemblyCode);
    }

    if (dynamic_cast<ClassDeclarationNode*>(node) != nullptr)
    {
        TraverseClassDeclarationNode(dynamic_cast<ClassDeclarationNode*>(node), assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseVarDeclarationNode(VarDeclarationNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Var declaration
}

void SyntaxTreeTraverser::TraverseFuncDeclarationNode(FuncDeclarationNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Func declaration
}

void SyntaxTreeTraverser::TraverseClassDeclarationNode(ClassDeclarationNode* node, AssemblyCode* assemblyCode)
{
    CodeGenerator::CodeGeneratorStates stateBackup = codeGenerator->state;
    codeGenerator->state = CodeGenerator::CodeGeneratorStates::CLASS;

    Environment* classEnv = new Environment();
    // TODO: Add type with Environment
    TraverseBodyNode(node->body, assemblyCode, classEnv);

    codeGenerator->state = stateBackup;
    // TODO: Implement node->isStatic (add variable called like the class)
}

void SyntaxTreeTraverser::TraverseStatementNode(AbstractStatementNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<EmptyStatementNode*>(node) != nullptr)
    {
        TraverseEmptyStatementNode(dynamic_cast<EmptyStatementNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AbstractKeywordStatementNode*>(node) != nullptr)
    {
        TraverseKeywordStatementNode(dynamic_cast<AbstractKeywordStatementNode*>(node), assemblyCode);
    }

    if (dynamic_cast<BodyNode*>(node) != nullptr)
    {
        TraverseBodyNode(dynamic_cast<BodyNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AbstractExpressionNode*>(node) != nullptr)
    {
        TraverseExpressionNode(dynamic_cast<AbstractExpressionNode*>(node), assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseEmptyStatementNode(EmptyStatementNode* node, AssemblyCode* assemblyCode) { return; }

void SyntaxTreeTraverser::TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Keyword statement
}

void SyntaxTreeTraverser::TraverseBodyNode(BodyNode* node, AssemblyCode* assemblyCode)
{
    Environment* environment = new Environment();
    TraverseBodyNode(node, assemblyCode, environment);
    delete environment;
}

void SyntaxTreeTraverser::TraverseBodyNode(BodyNode* node, AssemblyCode* assemblyCode, Environment* environment)
{
    codeGenerator->environmentList->Push(environment);
    TraverseCodeBlock(node->GetCodeBlock(), assemblyCode);
    codeGenerator->environmentList->Pop();
}

void SyntaxTreeTraverser::TraverseExpressionNode(AbstractExpressionNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<BinaryOperatorExpressionNode*>(node) != nullptr)
    {
        TraverseBinaryOperatorExpressionNode(dynamic_cast<BinaryOperatorExpressionNode*>(node), assemblyCode);
    }

    if (dynamic_cast<UnaryOperatorExpressionNode*>(node) != nullptr)
    {
        TraverseUnaryOperatorExpressionNode(dynamic_cast<UnaryOperatorExpressionNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AssignmentNode*>(node) != nullptr)
    {
        TraverseAssignmentNode(dynamic_cast<AssignmentNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AbstractValueNode*>(node) != nullptr)
    {
        TraverseValueNode(dynamic_cast<AbstractValueNode*>(node), assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node,
                                                               AssemblyCode* assemblyCode) {
    // TODO: Binary operator expression
};

void SyntaxTreeTraverser::TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node,
                                                              AssemblyCode* assemblyCode)
{
    // TODO: Unary operator expression
}

void SyntaxTreeTraverser::TraverseAssignmentNode(AssignmentNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Assignment
}

void SyntaxTreeTraverser::TraverseValueNode(AbstractValueNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<CallNode*>(node) != nullptr)
    {
        TraverseCallNode(dynamic_cast<CallNode*>(node), assemblyCode);
    }

    if (dynamic_cast<IdentifierNode*>(node) != nullptr)
    {
        TraverseIdentifierNode(dynamic_cast<IdentifierNode*>(node), assemblyCode);
    }

    if (dynamic_cast<RelAccessValueNode*>(node) != nullptr)
    {
        TraverseRelAccessValueNode(dynamic_cast<RelAccessValueNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AbstractConstValueNode*>(node) != nullptr)
    {
        TraverseAbstractConstValueNode(dynamic_cast<AbstractConstValueNode*>(node), assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseCallNode(CallNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Call
}

void SyntaxTreeTraverser::TraverseIdentifierNode(IdentifierNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Identifier
}

void SyntaxTreeTraverser::TraverseRelAccessValueNode(RelAccessValueNode* node, AssemblyCode* assemblyCode)
{
    for (auto& relAccess : node->relAccesses)
    {
        TraverseExpressionNode(relAccess.value, assemblyCode);

        VariableLocation* varLocation = codeGenerator->varLocationStack.Pop();

        // TODO: Activate varLocation environment

        if (!relAccess.isStaticAccess)
        {
            codeGenerator->relAccessVarLocation = varLocation;
        }
    }

    TraverseExpressionNode(node->lastValue, assemblyCode);
}

void SyntaxTreeTraverser::TraverseAbstractConstValueNode(AbstractConstValueNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<LogicalConstValueNode*>(node) != nullptr)
    {
        TraverseLogicalConstValueNode(dynamic_cast<LogicalConstValueNode*>(node), assemblyCode);
    }

    if (dynamic_cast<NumberConstValueNode*>(node) != nullptr)
    {
        TraverseNumberConstValueNode(dynamic_cast<NumberConstValueNode*>(node), assemblyCode);
    }

    if (dynamic_cast<StringConstValueNode*>(node) != nullptr)
    {
        TraverseStringConstValueNode(dynamic_cast<StringConstValueNode*>(node), assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseLogicalConstValueNode(LogicalConstValueNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Logical const value
}

void SyntaxTreeTraverser::TraverseNumberConstValueNode(NumberConstValueNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Number const value
}

void SyntaxTreeTraverser::TraverseStringConstValueNode(StringConstValueNode* node, AssemblyCode* assemblyCode)
{
    // TODO: String const value
}