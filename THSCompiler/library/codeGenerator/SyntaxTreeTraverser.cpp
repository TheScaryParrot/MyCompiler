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
#include "environment/Environment.cpp"
#include "function/Function.cpp"
#include "varLocation/IVariableLocation.cpp"
#include "varLocation/NumConstVarLocation.cpp"
#include "varLocation/RelAccessVarLocation.cpp"

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
    /// @brief Overload of TraverseBodyNode for when instead of pushing a new environment, the environment passed as
    /// an argument is pushed(eg. used by TraverseClassDeclarationNode)
    void TraverseBodyNode(BodyNode* node, AssemblyCode* assemblyCode, Environment* environment);

    IVariableLocation* TraverseExpressionNode(AbstractExpressionNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseAssignmentNode(AssignmentNode* node, AssemblyCode* assemblyCode);

    IVariableLocation* TraverseValueNode(AbstractValueNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseCallNode(CallNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseIdentifierNode(VariableNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseRelAccessValueNode(RelAccessValueNode* node, AssemblyCode* assemblyCode);

    IVariableLocation* TraverseAbstractConstValueNode(AbstractConstValueNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseLogicalConstValueNode(LogicalConstValueNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseNumberConstValueNode(IntConstValueNode* node, AssemblyCode* assemblyCode);
    IVariableLocation* TraverseStringConstValueNode(StringConstValueNode* node, AssemblyCode* assemblyCode);
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
    Type* type = codeGenerator->environmentList->GetType(node->type.name);
    IVariableLocation* propertyLocation = nullptr;

    switch (codeGenerator->state)
    {
        case CodeGenerator::CodeGeneratorStates::GLOBAL:
            // TODO: New variable in data section of assemblyCode
            break;
        case CodeGenerator::CodeGeneratorStates::FUNCTION:
            if (node->attributes.isInline)
            {
                if (node->value != nullptr)
                {
                    propertyLocation = TraverseExpressionNode(node->value, assemblyCode);
                }

                propertyLocation->SetIsInline(true);

                break;
            }

            propertyLocation = codeGenerator->AllocateNewVariableLocation(type, assemblyCode);

            if (node->value != nullptr)
            {
                IVariableLocation* valueLocation = TraverseExpressionNode(node->value, assemblyCode);
                // TODO: Move value from valueLocation to propertyLocation
            }

            break;

        case CodeGenerator::CodeGeneratorStates::CLASS:

            if (node->attributes.isInline)
            {
                if (!node->attributes.isStatic)
                {
                    std::cerr << "Inline variable not declared as static. Will be treated as static\n";
                    node->attributes.isStatic = true;
                }

                if (node->value != nullptr)
                {
                    propertyLocation = TraverseExpressionNode(node->value, assemblyCode);
                }

                propertyLocation->SetIsInline(true);
                break;
            }

            if (node->value != nullptr)
            {
                std::cerr << "Property " << node->name << " is assigned on declaration. Will be ignored. Use constructor instead\n";
            }

            if (!codeGenerator->environmentList->HasCompilerVarInt(codeGenerator->CLASS_SIZE_COMPILE_VAR))
            {
                std::cerr << "Class size not found in current environment\n";
                return;
            }

            int* classSize = codeGenerator->environmentList->GetCompilerVarInt(codeGenerator->CLASS_SIZE_COMPILE_VAR);
            propertyLocation = new RelAccessVarLocation(*classSize, type);

            int typeSize = *type->environment->GetCompilerVarIntMap()->Get(codeGenerator->CLASS_SIZE_COMPILE_VAR);
            classSize += typeSize;  // classSize is a pointer so this works

            break;
    }

    if (propertyLocation->GetType() != type)
    {
        std::cerr << "Trying to assign Variable " << node->name << " of type " << node->type.ToString()
                  << " on declaration. But expression has wrong type\n";
        return;
    }

    codeGenerator->environmentList->GetVariableMap()->Insert(node->name, propertyLocation);
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
    classEnv->GetCompilerVarIntMap()->Insert(codeGenerator->CLASS_SIZE_COMPILE_VAR, 0);
    Type* newType = new Type(classEnv);
    codeGenerator->environmentList->GetTypeMap()->Insert(node->name, newType);

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

IVariableLocation* SyntaxTreeTraverser::TraverseExpressionNode(AbstractExpressionNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<BinaryOperatorExpressionNode*>(node) != nullptr)
    {
        return TraverseBinaryOperatorExpressionNode(dynamic_cast<BinaryOperatorExpressionNode*>(node), assemblyCode);
    }

    if (dynamic_cast<UnaryOperatorExpressionNode*>(node) != nullptr)
    {
        return TraverseUnaryOperatorExpressionNode(dynamic_cast<UnaryOperatorExpressionNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AssignmentNode*>(node) != nullptr)
    {
        return TraverseAssignmentNode(dynamic_cast<AssignmentNode*>(node), assemblyCode);
    }

    if (dynamic_cast<AbstractValueNode*>(node) != nullptr)
    {
        return TraverseValueNode(dynamic_cast<AbstractValueNode*>(node), assemblyCode);
    }
}

IVariableLocation* SyntaxTreeTraverser::TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, AssemblyCode* assemblyCode) {
    // TODO: Binary operator expression
};

IVariableLocation* SyntaxTreeTraverser::TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Unary operator expression
}

IVariableLocation* SyntaxTreeTraverser::TraverseAssignmentNode(AssignmentNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Assignment
}

IVariableLocation* SyntaxTreeTraverser::TraverseValueNode(AbstractValueNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<CallNode*>(node) != nullptr)
    {
        TraverseCallNode(dynamic_cast<CallNode*>(node), assemblyCode);
    }

    if (dynamic_cast<VariableNode*>(node) != nullptr)
    {
        TraverseIdentifierNode(dynamic_cast<VariableNode*>(node), assemblyCode);
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

IVariableLocation* SyntaxTreeTraverser::TraverseCallNode(CallNode* node, AssemblyCode* assemblyCode)
{
    Function* function = nullptr;

    std::vector<IVariableLocation*> arguments;
    Map<std::string, IVariableLocation*>* parameterMap = function->environment->GetVariableMap();

    if (function->isInline)
    {
        codeGenerator->environmentList->Push(function->environment);
        CodeGenerator::CodeGeneratorStates stateBackup = codeGenerator->state;
        codeGenerator->state = CodeGenerator::CodeGeneratorStates::FUNCTION;

        unsigned int i = 0;

        for (std::pair<std::string, IVariableLocation*> pair : *parameterMap)
        {
            IVariableLocation* argument = arguments[i];
            std::string parameterName = pair.first;
            IVariableLocation* parameter = pair.second;

            if (parameter->IsInline())
            {
                // Directly sets the variable in the environment to the argument
                codeGenerator->environmentList->GetVariableMap()->Insert(parameterName, argument);
            }
            else
            {
                codeGenerator->GenerateCodeAssign(parameter, argument, assemblyCode);
                // Varlocation in environment remains unchanged as it was just assigned to
            }

            i++;
        }

        // TODO: Make function body
    }
    else
    {
        unsigned int i = 0;

        for (std::pair<std::string, IVariableLocation*> pair : *parameterMap)
        {
            IVariableLocation* argument = arguments[i];
            IVariableLocation* parameter = pair.second;
            codeGenerator->GenerateCodeAssign(parameter, argument, assemblyCode);
            i++;
        }

        // TODO: Call function
    }

    return parameterMap->Get(function->RETURN_VARIABLE_NAME);
}

IVariableLocation* SyntaxTreeTraverser::TraverseIdentifierNode(VariableNode* node, AssemblyCode* assemblyCode)
{
    IVariableLocation* idVarLocation = codeGenerator->environmentList->GetVariable(node->id);

    if (idVarLocation == nullptr)
    {
        std::cerr << "Variable " << node->id << " not found\n";
    }

    if (codeGenerator->relAccessBaseVarLocation != nullptr)
    {
        return idVarLocation->ConstructionFromRelAccessBase(codeGenerator->relAccessBaseVarLocation);
    }

    return idVarLocation;
}

IVariableLocation* SyntaxTreeTraverser::TraverseRelAccessValueNode(RelAccessValueNode* node, AssemblyCode* assemblyCode)
{
    EnvironmentLinkedList* envListBackup = codeGenerator->environmentList;

    for (auto& relAccess : node->relAccesses)
    {
        IVariableLocation* varLocation = TraverseExpressionNode(relAccess.value, assemblyCode);

        codeGenerator->environmentList->Clear();
        codeGenerator->environmentList->Push(varLocation->GetType()->environment);

        if (!relAccess.isStaticAccess)
        {
            codeGenerator->relAccessBaseVarLocation = varLocation;
        }
    }

    IVariableLocation* result = TraverseExpressionNode(node->lastValue, assemblyCode);
    codeGenerator->relAccessBaseVarLocation = nullptr;  // Clear relative access
    codeGenerator->environmentList = envListBackup;     // Restore environment
    return result;
}

IVariableLocation* SyntaxTreeTraverser::TraverseAbstractConstValueNode(AbstractConstValueNode* node, AssemblyCode* assemblyCode)
{
    if (dynamic_cast<LogicalConstValueNode*>(node) != nullptr)
    {
        return TraverseLogicalConstValueNode(dynamic_cast<LogicalConstValueNode*>(node), assemblyCode);
    }

    if (dynamic_cast<IntConstValueNode*>(node) != nullptr)
    {
        return TraverseNumberConstValueNode(dynamic_cast<IntConstValueNode*>(node), assemblyCode);
    }

    if (dynamic_cast<StringConstValueNode*>(node) != nullptr)
    {
        return TraverseStringConstValueNode(dynamic_cast<StringConstValueNode*>(node), assemblyCode);
    }
}

IVariableLocation* SyntaxTreeTraverser::TraverseLogicalConstValueNode(LogicalConstValueNode* node, AssemblyCode* assemblyCode)
{
    // TODO: Logical const value
}

IVariableLocation* SyntaxTreeTraverser::TraverseNumberConstValueNode(IntConstValueNode* node, AssemblyCode* assemblyCode)
{
    Type* type = codeGenerator->environmentList->GetNumConstType();
    return new NumConstVarLocation(node->GetValue(), type);
}

IVariableLocation* SyntaxTreeTraverser::TraverseStringConstValueNode(StringConstValueNode* node, AssemblyCode* assemblyCode)
{
    // TODO: String const value
}