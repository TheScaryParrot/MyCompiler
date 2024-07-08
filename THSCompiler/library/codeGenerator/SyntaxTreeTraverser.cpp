#pragma once

#include "../assembly/AssemblyCode.cpp"
#include "../syntaxTree/SyntaxTree.cpp"
#include "../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/expression/BinaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"

class SyntaxTreeTraverser
{
   public:
    AssemblyCode* Traverse(SyntaxTree* syntaxTree);

   private:
    void TraverseLineNode(AbstractLineNode* node, AssemblyCode* assemblyCode);

    void TraverseDeclarationNode(AbstractDeclarationNode* node, AssemblyCode* assemblyCode);
    void TraverseVarDeclarationNode(VarDeclarationNode* node, AssemblyCode* assemblyCode);
    void TraverseFuncDeclarationNode(FuncDeclarationNode* node, AssemblyCode* assemblyCode);
    void TraverseClassDeclarationNode(ClassDeclarationNode* node, AssemblyCode* assemblyCode);

    void TraverseStatementNode(AbstractStatementNode* node, AssemblyCode* assemblyCode);
    void TraverseEmptyStatementNode(EmptyStatementNode* node, AssemblyCode* assemblyCode);
    void TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, AssemblyCode* assemblyCode);
    void TraverseBodyNode(BodyNode* node, AssemblyCode* assemblyCode);

    void TraverseExpressionNode(AbstractExpressionNode* node, AssemblyCode* assemblyCode);
    void TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, AssemblyCode* assemblyCode);
    void TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, AssemblyCode* assemblyCode);
};

AssemblyCode* SyntaxTreeTraverser::Traverse(SyntaxTree* syntaxTree)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (unsigned int i = 0; i < syntaxTree->GetLineCount(); i++)
    {
        AbstractLineNode* node = syntaxTree->GetLine(i);

        if (node == nullptr) continue;

        TraverseLineNode(node, assemblyCode);
    }

    return assemblyCode;
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
    // TODO: Class declaration
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
    // TODO: Body
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
}
