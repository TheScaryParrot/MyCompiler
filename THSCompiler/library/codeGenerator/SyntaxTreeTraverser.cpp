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
#include "../utils/Logger.cpp"
#include "CodeGenerator.cpp"
#include "Variable.cpp"
#include "types/StructType.cpp"
#include "varLocation/IVariableLocation.cpp"
#include "varLocation/LabelVarLocation.cpp"

class SyntaxTreeTraverser
{
   public:
    AssemblyCode* Traverse(SyntaxTree* syntaxTree);

   private:
    void TraverseGlobalCodeNode(GlobalCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseBodyCodeNode(BodyCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseLineNode(AbstractLineNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    StructType* TraverseTypeDefCodeNode(TypeDefCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    void TraverseDeclarationNode(AbstractDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseGlobalVarDeclarationNode(GlobalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseLocalVarDeclarationNode(LocalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseFuncDeclarationNode(FuncDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseParameterDeclarationNode(ParameterDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraversePropertyDeclarationNode(PropertyDeclarationNode* node, StructType* structType, CodeGenerator* codeGenerator,
                                         AssemblyCode* assemblyCode);
    void TraverseTypeDeclarationNode(TypeDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    void TraverseStatementNode(AbstractStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseEmptyStatementNode(EmptyStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseBodyNode(BodyNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    Variable* TraverseExpressionNode(AbstractExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseAssignmentNode(AssignmentNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    Variable* TraverseValueNode(AbstractValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseCallNode(CallNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseParentesisExpressionNode(ParenthesisExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseStructNode(StructNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseVariableNode(VariableNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    Variable* TraverseAbstractConstValueNode(AbstractConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseLogicalConstValueNode(LogicalConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseIntConstValueNode(IntConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseFloatConstValueNode(FloatConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    Variable* TraverseStringConstValueNode(StringConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
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

StructType* SyntaxTreeTraverser::TraverseTypeDefCodeNode(TypeDefCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    StructType* structType = new StructType();

    for (unsigned int i = 0; i < node->GetLineCount(); i++)
    {
        PropertyDeclarationNode* declaration = node->GetProperty(i);

        if (declaration == nullptr) continue;

        TraversePropertyDeclarationNode(declaration, structType, codeGenerator, assemblyCode);
    }

    return structType;
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
    if (codeGenerator->DoesVariableExist(node->name))
    {
        Logger.Log("Variable " + node->name + " already exists. Cannot be declared again", Logger::ERROR);
        return;
    }

    Type* type = codeGenerator->GetType(node->type.name);

    Variable* value = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

    if (!value->IsInline())
    {
        Logger.Log("Cannot assign a non-inline value to a global variable in global scope", Logger::ERROR);
        return;
    }

    Variable* newVariable = nullptr;

    if (node->attributes.isInline)
    {
        newVariable = new Variable(value->location, type, node->attributes.isFinal);
    }
    else
    {
        LabelVarLocation* location = new LabelVarLocation(node->name);
        newVariable = new Variable(location, type, node->attributes.isFinal);

        std::string assemblyDefineString = type->GetAssemblyDefineString() + " ";

        if (value == nullptr || value->location == nullptr)
        {
            assemblyDefineString += "VALUE OR VALUE->LOCATION IS NULLPTR";
        }
        else
        {
            assemblyDefineString += value->location->ToAssemblyString();
        }

        DataDeclarationLine* dataDeclarationLine = new DataDeclarationLine(node->name, assemblyDefineString);

        if (node->attributes.isFinal)
        {
            assemblyCode->AddToRoData(dataDeclarationLine);
        }
        else
        {
            assemblyCode->AddToData(dataDeclarationLine);
        }
    }

    codeGenerator->AddVariable(node->name, newVariable);
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

void SyntaxTreeTraverser::TraversePropertyDeclarationNode(PropertyDeclarationNode* node, StructType* structType, CodeGenerator* codeGenerator,
                                                          AssemblyCode* assemblyCode)
{
    Type* type = codeGenerator->GetType(node->type.name);
    structType->AddProperty(node->name, type);
}

void SyntaxTreeTraverser::TraverseTypeDeclarationNode(TypeDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (codeGenerator->DoesTypeExist(node->name))
    {
        Logger.Log("Type " + node->name + " already exists. Cannot be declared again", Logger::ERROR);
        return;
    }

    StructType* structType = TraverseTypeDefCodeNode(node->typeDefCode, codeGenerator, assemblyCode);
    codeGenerator->AddType(node->name, structType);
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

Variable* SyntaxTreeTraverser::TraverseExpressionNode(AbstractExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
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

Variable* SyntaxTreeTraverser::TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                    AssemblyCode* assemblyCode)
{
    // TODO: Binary operator expression
    return nullptr;
};

Variable* SyntaxTreeTraverser::TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                   AssemblyCode* assemblyCode)
{
    Variable* variable = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

    if (!node->applyToReference)
    {
        Variable* newVariable = codeGenerator->GetNewLocalVariable(variable->type);
        variable->type->GenerateAssign(newVariable->location, variable->location, assemblyCode);
        variable = newVariable;
    }

    switch (node->preUnaryOperator)
    {
        case EPreUnaryOperators::PRE_NOT:
            variable->type->GenerateNot(variable->location, assemblyCode);
            break;
        case EPreUnaryOperators::PRE_NEGATE:
            variable->type->GenerateNeg(variable->location, assemblyCode);
            break;
        case EPreUnaryOperators::PRE_INCREMENT:
            variable->type->GenerateInc(variable->location, assemblyCode);
            break;
        case EPreUnaryOperators::PRE_DECREMENT:
            variable->type->GenerateDec(variable->location, assemblyCode);
            break;
    }

    // TODO: Post unary operators

    return variable;
}

Variable* SyntaxTreeTraverser::TraverseAssignmentNode(AssignmentNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    Variable* value = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

    for (Assignment* assignment : node->assignments)
    {
        Variable* l_variable = TraverseVariableNode(assignment->L_value, codeGenerator, assemblyCode);

        if (l_variable->isFinal)
        {
            Logger.Log("Cannot assign to final variable " + assignment->L_value->ids[0], Logger::ERROR);
            continue;
        }

        switch (assignment->assignOperator)
        {
            case EAssignOperators::ASSIGN:
                l_variable->type->GenerateAssign(l_variable->location, value->location, assemblyCode);
                break;
            case EAssignOperators::ADD_ASSIGN:
                l_variable->type->GenerateAdd(l_variable->location, value->location, assemblyCode);
                break;
            case EAssignOperators::SUB_ASSIGN:
                l_variable->type->GenerateSub(l_variable->location, value->location, assemblyCode);
                break;
            case EAssignOperators::MUL_ASSIGN:
                l_variable->type->GenerateMul(l_variable->location, value->location, assemblyCode);
                break;
            case EAssignOperators::DIV_ASSIGN:
                l_variable->type->GenerateDiv(l_variable->location, value->location, assemblyCode);
                break;
            case EAssignOperators::MOD_ASSIGN:
                l_variable->type->GenerateMod(l_variable->location, value->location, assemblyCode);
                break;
        }

        value = l_variable;
    }

    return value;
}

Variable* SyntaxTreeTraverser::TraverseValueNode(AbstractValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
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

Variable* SyntaxTreeTraverser::TraverseCallNode(CallNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO Call
    return nullptr;
}

Variable* SyntaxTreeTraverser::TraverseParentesisExpressionNode(ParenthesisExpressionNode* node, CodeGenerator* codeGenerator,
                                                                AssemblyCode* assemblyCode)
{
    return TraverseExpressionNode(node->expression, codeGenerator, assemblyCode);
}

Variable* SyntaxTreeTraverser::TraverseStructNode(StructNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    StructType* tempStructType = new StructType();

    std::vector<std::pair<Property, Variable*>> propertyAssigns;

    // Generate temporary structtype
    for (size_t i = 0; i < node->values.size(); i++)
    {
        Variable* r_value = TraverseExpressionNode(node->values[i], codeGenerator, assemblyCode);
        propertyAssigns.push_back({tempStructType->AddProperty("", r_value->type), r_value});
    }

    Variable* structVariable = codeGenerator->GetNewLocalVariable(tempStructType);

    // Assign the values to the struct
    for (size_t i = 0; i < propertyAssigns.size(); i++)
    {
        std::pair<Property, Variable*> propertyAssign = propertyAssigns[i];
        Variable* l_value = propertyAssign.first.Apply(structVariable->location);
        Variable* r_value = propertyAssign.second;

        l_value->type->GenerateAssign(l_value->location, r_value->location, assemblyCode);
    }

    return structVariable;
}

Variable* SyntaxTreeTraverser::TraverseVariableNode(VariableNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (node->ids.size() == 0)
    {
        Logger.Log("VariableNode with no ids. This is a mistake of the idiot who made this compiler", Logger::ERROR);
        return nullptr;
    }

    if (!codeGenerator->DoesVariableExist(node->ids[0]))
    {
        Logger.Log("Variable " + node->ids[0] + " does not exist", Logger::ERROR);
        return nullptr;
    }

    Variable* variable = codeGenerator->GetVariable(node->ids[0]);

    for (size_t i = 1; i < node->ids.size(); i++)
    {
        StructType* structType = dynamic_cast<StructType*>(variable->type);

        if (structType == nullptr)
        {
            Logger.Log("Cannot access property as " + node->ids[i] + " is not a struct", Logger::ERROR);
            return nullptr;
        }

        variable = structType->ApplyProperty(node->ids[i], variable->location);
    }

    return variable;
}

Variable* SyntaxTreeTraverser::TraverseAbstractConstValueNode(AbstractConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
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

Variable* SyntaxTreeTraverser::TraverseLogicalConstValueNode(LogicalConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    Type* type = codeGenerator->GetType("bool");
    IVariableLocation* location = codeGenerator->ConstructLogicalConstVariableLocation(node->GetValue());
    return new Variable(location, type, true);
}

Variable* SyntaxTreeTraverser::TraverseIntConstValueNode(IntConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    Type* type = codeGenerator->GetType("int");
    IVariableLocation* location = codeGenerator->ConstructIntConstVariableLocation(node->GetValue());
    return new Variable(location, type, true);
}

Variable* SyntaxTreeTraverser::TraverseFloatConstValueNode(FloatConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    Type* type = codeGenerator->GetType("float");
    IVariableLocation* location = codeGenerator->ConstructFloatConstVaribaleLocation(node->GetValue());
    return new Variable(location, type, true);
}

Variable* SyntaxTreeTraverser::TraverseStringConstValueNode(StringConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // TODO: String const value
    return nullptr;
}