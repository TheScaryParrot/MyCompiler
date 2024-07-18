#pragma once

#include "../assembly/AssemblyCode.cpp"
#include "../syntaxTree/SyntaxTree.cpp"
#include "../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/GlobalVarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/LocalVarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ParameterDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/PropertyDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/TypeDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../syntaxTree/nodes/line/expression/BinaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryOperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/AbstractValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/CallNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/ParenthesisExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/StructNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/VariableNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/AbstractConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/FloatConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/IntConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/LogicalConstValueNode.cpp"
#include "../syntaxTree/nodes/line/expression/values/constValues/StringConstValueNode.cpp"
#include "../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"
#include "CodeGenerator.cpp"
#include "varLocation/IVariableLocation.cpp"

class SyntaxTreeTraverser
{
   public:
    AssemblyCode* Traverse(SyntaxTree* syntaxTree);

   private:
    void TraverseGlobalCodeNode(GlobalCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseBodyCodeNode(BodyCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseLineNode(AbstractLineNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseTypeDefCodeNode(TypeDefCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    void TraverseDeclarationNode(AbstractDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseGlobalVarDeclarationNode(GlobalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseLocalVarDeclarationNode(LocalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseFuncDeclarationNode(FuncDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseParameterDeclarationNode(ParameterDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraversePropertyDeclarationNode(PropertyDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseTypeDeclarationNode(TypeDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    void TraverseStatementNode(AbstractStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseEmptyStatementNode(EmptyStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseBodyNode(BodyNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    IVariableLocation* TraverseExpressionNode(AbstractExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                            AssemblyCode* assemblyCode);
    IVariableLocation* TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                           AssemblyCode* assemblyCode);
    IVariableLocation* TraverseAssignmentNode(AssignmentNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    IVariableLocation* TraverseValueNode(AbstractValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseCallNode(CallNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseParentesisExpressionNode(ParenthesisExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseStructNode(StructNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseVariableNode(VariableNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    IVariableLocation* TraverseAbstractConstValueNode(AbstractConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseLogicalConstValueNode(LogicalConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseIntConstValueNode(IntConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseFloatConstValueNode(FloatConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseStringConstValueNode(StringConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
};

AssemblyCode* SyntaxTreeTraverser::Traverse(SyntaxTree* syntaxTree)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    CodeGenerator codeGenerator = CodeGenerator();

    TraverseGlobalCodeNode(syntaxTree->GetCode(), &codeGenerator, assemblyCode);

    return assemblyCode;
}

void SyntaxTreeTraverser::TraverseGlobalCodeNode(GlobalCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    for (unsigned int i = 0; i < node->GetLineCount(); i++)
    {
        AbstractDeclarationNode* declaration = node->GetLine(i);

        if (declaration == nullptr) continue;

        TraverseDeclarationNode(declaration, codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseBodyCodeNode(BodyCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    for (unsigned int i = 0; i < node->GetLineCount(); i++)
    {
        AbstractLineNode* lineNode = node->GetLine(i);

        if (lineNode == nullptr) continue;

        TraverseLineNode(lineNode, codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseLineNode(AbstractLineNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<AbstractDeclarationNode*>(node) != nullptr)
    {
        TraverseDeclarationNode(dynamic_cast<AbstractDeclarationNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<AbstractStatementNode*>(node) != nullptr)
    {
        TraverseStatementNode(dynamic_cast<AbstractStatementNode*>(node), codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseTypeDefCodeNode(TypeDefCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    for (unsigned int i = 0; i < node->GetLineCount(); i++)
    {
        PropertyDeclarationNode* declaration = node->GetProperty(i);

        if (declaration == nullptr) continue;

        TraversePropertyDeclarationNode(declaration, codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseDeclarationNode(AbstractDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<GlobalVarDeclarationNode*>(node) != nullptr)
    {
        TraverseGlobalVarDeclarationNode(dynamic_cast<GlobalVarDeclarationNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<LocalVarDeclarationNode*>(node) != nullptr)
    {
        TraverseLocalVarDeclarationNode(dynamic_cast<LocalVarDeclarationNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<FuncDeclarationNode*>(node) != nullptr)
    {
        TraverseFuncDeclarationNode(dynamic_cast<FuncDeclarationNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<TypeDeclarationNode*>(node) != nullptr)
    {
        TraverseTypeDeclarationNode(dynamic_cast<TypeDeclarationNode*>(node), codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseGlobalVarDeclarationNode(GlobalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Global var declaration
}

void SyntaxTreeTraverser::TraverseLocalVarDeclarationNode(LocalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Local var declaration
}

void SyntaxTreeTraverser::TraverseFuncDeclarationNode(FuncDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Func declaration
}

void SyntaxTreeTraverser::TraverseParameterDeclarationNode(ParameterDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Parameter declaration
}

void SyntaxTreeTraverser::TraversePropertyDeclarationNode(PropertyDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Property declaration
}

void SyntaxTreeTraverser::TraverseTypeDeclarationNode(TypeDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Type declaration
}

void SyntaxTreeTraverser::TraverseStatementNode(AbstractStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<EmptyStatementNode*>(node) != nullptr)
    {
        TraverseEmptyStatementNode(dynamic_cast<EmptyStatementNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<AbstractKeywordStatementNode*>(node) != nullptr)
    {
        TraverseKeywordStatementNode(dynamic_cast<AbstractKeywordStatementNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<BodyNode*>(node) != nullptr)
    {
        TraverseBodyNode(dynamic_cast<BodyNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<AbstractExpressionNode*>(node) != nullptr)
    {
        TraverseExpressionNode(dynamic_cast<AbstractExpressionNode*>(node), codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseEmptyStatementNode(EmptyStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) { return; }

void SyntaxTreeTraverser::TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Keyword statement
}

void SyntaxTreeTraverser::TraverseBodyNode(BodyNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Body node
}

IVariableLocation* SyntaxTreeTraverser::TraverseExpressionNode(AbstractExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<BinaryOperatorExpressionNode*>(node) != nullptr)
    {
        return TraverseBinaryOperatorExpressionNode(dynamic_cast<BinaryOperatorExpressionNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<UnaryOperatorExpressionNode*>(node) != nullptr)
    {
        return TraverseUnaryOperatorExpressionNode(dynamic_cast<UnaryOperatorExpressionNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<AssignmentNode*>(node) != nullptr)
    {
        return TraverseAssignmentNode(dynamic_cast<AssignmentNode*>(node), codeGenerator, assemblyCode);
    }

    return TraverseValueNode(dynamic_cast<AbstractValueNode*>(node), codeGenerator, assemblyCode);
}

IVariableLocation* SyntaxTreeTraverser::TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                             AssemblyCode* assemblyCode)
{
    // TODO: Binary operator expression
    return nullptr;
};

IVariableLocation* SyntaxTreeTraverser::TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                            AssemblyCode* assemblyCode)
{
    // TODO: Unary operator expression
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseAssignmentNode(AssignmentNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: Assignment
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseValueNode(AbstractValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<CallNode*>(node) != nullptr)
    {
        return TraverseCallNode(dynamic_cast<CallNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<ParenthesisExpressionNode*>(node) != nullptr)
    {
        return TraverseParentesisExpressionNode(dynamic_cast<ParenthesisExpressionNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<StructNode*>(node) != nullptr)
    {
        return TraverseStructNode(dynamic_cast<StructNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<VariableNode*>(node) != nullptr)
    {
        return TraverseVariableNode(dynamic_cast<VariableNode*>(node), codeGenerator, assemblyCode);
    }

    return TraverseAbstractConstValueNode(dynamic_cast<AbstractConstValueNode*>(node), codeGenerator, assemblyCode);
}

IVariableLocation* SyntaxTreeTraverser::TraverseCallNode(CallNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Call
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseParentesisExpressionNode(ParenthesisExpressionNode* node, CodeGenerator* codeGenerator,
                                                                         AssemblyCode* assemblyCode)
{
    return TraverseExpressionNode(node->expression, codeGenerator, assemblyCode);
}

IVariableLocation* SyntaxTreeTraverser::TraverseStructNode(StructNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Struct
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseVariableNode(VariableNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Variable
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseAbstractConstValueNode(AbstractConstValueNode* node, CodeGenerator* codeGenerator,
                                                                       AssemblyCode* assemblyCode)
{
    if (dynamic_cast<LogicalConstValueNode*>(node) != nullptr)
    {
        return TraverseLogicalConstValueNode(dynamic_cast<LogicalConstValueNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<IntConstValueNode*>(node) != nullptr)
    {
        return TraverseIntConstValueNode(dynamic_cast<IntConstValueNode*>(node), codeGenerator, assemblyCode);
    }

    if (dynamic_cast<FloatConstValueNode*>(node) != nullptr)
    {
        return TraverseFloatConstValueNode(dynamic_cast<FloatConstValueNode*>(node), codeGenerator, assemblyCode);
    }

    return TraverseStringConstValueNode(dynamic_cast<StringConstValueNode*>(node), codeGenerator, assemblyCode);
}

IVariableLocation* SyntaxTreeTraverser::TraverseLogicalConstValueNode(LogicalConstValueNode* node, CodeGenerator* codeGenerator,
                                                                      AssemblyCode* assemblyCode)
{
    // TODO: Logical const value
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseIntConstValueNode(IntConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Int const value
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseFloatConstValueNode(FloatConstValueNode* node, CodeGenerator* codeGenerator,
                                                                    AssemblyCode* assemblyCode)
{
    // TODO Float const value
    return nullptr;
}

IVariableLocation* SyntaxTreeTraverser::TraverseStringConstValueNode(StringConstValueNode* node, CodeGenerator* codeGenerator,
                                                                     AssemblyCode* assemblyCode)
{
    // TODO: String const value
    return nullptr;
}