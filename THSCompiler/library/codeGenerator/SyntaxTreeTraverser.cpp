#pragma once

#include "../assembly/AssemblyCode.cpp"
#include "../assembly/AssemblyLabelLine.cpp"
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
#include "../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"
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
    std::shared_ptr<StructType> TraverseTypeDefCodeNode(TypeDefCodeNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

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
    void TraverseBodyNode(BodyNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseKeywordStatementNode(AbstractKeywordStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseBreakStatementNode(BreakStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseContinueStatementNode(ContinueStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseForStatementNode(ForStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseIfStatementNode(IfStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseReturnNode(ReturnStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    void TraverseWhileStatementNode(WhileStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    std::shared_ptr<Variable> TraverseExpressionNode(AbstractExpressionNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                   AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                  AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseAssignmentNode(AssignmentNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    std::shared_ptr<Variable> TraverseValueNode(AbstractValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseCallNode(CallNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseParentesisExpressionNode(ParenthesisExpressionNode* node, CodeGenerator* codeGenerator,
                                                               AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseStructNode(StructNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseVariableNode(VariableNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);

    std::shared_ptr<Variable> TraverseAbstractConstValueNode(AbstractConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseLogicalConstValueNode(LogicalConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseIntConstValueNode(IntConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseFloatConstValueNode(FloatConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
    std::shared_ptr<Variable> TraverseStringConstValueNode(StringConstValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode);
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

std::shared_ptr<StructType> SyntaxTreeTraverser::TraverseTypeDefCodeNode(TypeDefCodeNode* node, CodeGenerator* codeGenerator,
                                                                         AssemblyCode* assemblyCode)
{
    StructType* structType = new StructType();

    for (unsigned int i = 0; i < node->GetLineCount(); i++)
    {
        PropertyDeclarationNode* declaration = node->GetProperty(i);

        if (declaration == nullptr) continue;

        TraversePropertyDeclarationNode(declaration, structType, codeGenerator, assemblyCode);
    }

    return std::shared_ptr<StructType>(structType);
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

    std::shared_ptr<Type> type = codeGenerator->GetType(node->type.name);
    Variable* newVariable = nullptr;

    // bss and no inline allowed
    if (node->value == nullptr)
    {
        if (node->attributes.isInline)
        {
            Logger.Log("Cannot declare inline global variable " + node->name + " without value", Logger::ERROR);
            return;
        }

        std::shared_ptr<LabelVarLocation> location = std::shared_ptr<LabelVarLocation>(new LabelVarLocation(node->name));
        newVariable = new Variable(location, type, node->attributes.isFinal);

        std::string assemblyReserveString = "resb " + std::to_string(type->GetSize());
        DataDeclarationLine* dataDeclarationLine = new DataDeclarationLine(node->name, assemblyReserveString);
        assemblyCode->AddToBss(dataDeclarationLine);
    }
    // inline or data/rodata
    else
    {
        std::shared_ptr<Variable> value = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

        if (!value->IsInline())
        {
            Logger.Log("Cannot assign a non-inline value to a global variable in global scope", Logger::ERROR);
            return;
        }

        if (value->type != type)
        {
            Logger.Log("Assign types of global variable " + node->name + " don't match", Logger::ERROR);
            return;
        }

        // inline
        if (node->attributes.isInline)
        {
            newVariable = new Variable(value->location, type, node->attributes.isFinal);
        }
        // data/rodata
        else
        {
            std::shared_ptr<LabelVarLocation> location = std::shared_ptr<LabelVarLocation>(new LabelVarLocation(node->name));
            newVariable = new Variable(location, type, node->attributes.isFinal);

            std::string assemblyDefineString = type->GetAssemblyDefineString() + " ";

            if (value == nullptr || value->location == nullptr)
            {
                assemblyDefineString += "VALUE OR VALUE->LOCATION IS NULLPTR";
            }
            else
            {
                assemblyDefineString += value->location->ToAssemblyDefineString();
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
    }

    codeGenerator->AddVariable(node->name, std::shared_ptr<Variable>(newVariable));
}

void SyntaxTreeTraverser::TraverseLocalVarDeclarationNode(LocalVarDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    bool isFinal = node->attributes.isFinal;
    bool isInline = node->attributes.isInline;
    std::shared_ptr<Type> type = codeGenerator->GetType(node->type.name);
    std::shared_ptr<Variable> value = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

    std::shared_ptr<Variable> newVariable = nullptr;

    if (isInline)
    {
        if (!value->IsInline())
        {
            Logger.Log("Cannot assign a non-inline value to inline variable " + node->name, Logger::ERROR);
            return;
        }

        if (value->type != type)
        {
            Logger.Log("Assign types of inline variable " + node->name + " don't match", Logger::ERROR);
            return;
        }

        newVariable.reset(new Variable(value->location, type, isFinal));
    }
    else
    {
        newVariable.reset(codeGenerator->GetNewLocalVariable(type, isFinal, assemblyCode));

        if (value != nullptr)
        {
            codeGenerator->ApplyBinaryOperatorOnVariables(newVariable, value, EOperators::ASSIGN_OPERATOR, assemblyCode);
        }
    }

    codeGenerator->AddVariable(node->name, newVariable);
}

void SyntaxTreeTraverser::TraverseFuncDeclarationNode(FuncDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    bool isStartFunction = node->name == "_start";

    std::vector<std::shared_ptr<Type>> parameterTypes;

    for (ParameterDeclarationNode* parameter : *node->parameters)
    {
        parameterTypes.push_back(codeGenerator->GetType(parameter->type));
    }

    std::shared_ptr<Type> returnType = nullptr;

    // if not void
    if (!node->returnType.IsVoid())
    {
        returnType = codeGenerator->GetType(node->returnType.name);
    }

    Function* newFunction = new Function(node->name, parameterTypes, returnType);

    codeGenerator->AddFunction(node->name, std::shared_ptr<Function>(newFunction));

    // Generate assembly code
    codeGenerator->PushNewEnvironment();

    for (ParameterDeclarationNode* parameter : *node->parameters)
    {
        TraverseParameterDeclarationNode(parameter, codeGenerator, assemblyCode);
    }
    codeGenerator->ClearParameterCounter();

    assemblyCode->AddLine(new AssemblyLabelLine(node->name));

    if (isStartFunction)
    {
        AssemblyCodeGenerator.AddPreStartBody(assemblyCode);
    }
    else
    {
        AssemblyCodeGenerator.AddPreBody(assemblyCode);
    }

    TraverseBodyNode(node->body, codeGenerator, assemblyCode);

    if (isStartFunction)
    {
        AssemblyCodeGenerator.AddPostStartBody(assemblyCode);
    }
    else
    {
        AssemblyCodeGenerator.AddPostBody(assemblyCode);
    }

    // Add ret always at the end, not perfect but works
    assemblyCode->AddLine(new AssemblyInstructionLine("ret"));

    codeGenerator->PopEnvironment(assemblyCode);
}

void SyntaxTreeTraverser::TraverseParameterDeclarationNode(ParameterDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    Variable* newVariable = codeGenerator->GetNewParameterVariable(codeGenerator->GetType(node->type), node->isFinal, assemblyCode);
    codeGenerator->AddVariable(node->name, std::shared_ptr<Variable>(newVariable));
}

void SyntaxTreeTraverser::TraversePropertyDeclarationNode(PropertyDeclarationNode* node, StructType* structType, CodeGenerator* codeGenerator,
                                                          AssemblyCode* assemblyCode)
{
    std::shared_ptr<Type> type = codeGenerator->GetType(node->type.name);
    structType->AddProperty(node->name, type);
}

void SyntaxTreeTraverser::TraverseTypeDeclarationNode(TypeDeclarationNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    if (codeGenerator->DoesTypeExist(node->name))
    {
        Logger.Log("Type " + node->name + " already exists. Cannot be declared again", Logger::ERROR);
        return;
    }

    std::shared_ptr<StructType> structType = TraverseTypeDefCodeNode(node->typeDefCode, codeGenerator, assemblyCode);
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
    if (dynamic_cast<ReturnStatementNode*>(node) != nullptr)
    {
        TraverseReturnNode(dynamic_cast<ReturnStatementNode*>(node), codeGenerator, assemblyCode);
    }
}

void SyntaxTreeTraverser::TraverseBreakStatementNode(BreakStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + codeGenerator->GetBreakLabel()));
}

void SyntaxTreeTraverser::TraverseContinueStatementNode(ContinueStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + codeGenerator->GetContinueLabel()));
}

void SyntaxTreeTraverser::TraverseForStatementNode(ForStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) {}

void SyntaxTreeTraverser::TraverseIfStatementNode(IfStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) {}

void SyntaxTreeTraverser::TraverseWhileStatementNode(WhileStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) {}

void SyntaxTreeTraverser::TraverseReturnNode(ReturnStatementNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // forget local variables
    AssemblyCodeGenerator.AddPostBody(assemblyCode);

    // store return as new local variable
    if (node->expression != nullptr)
    {
        std::shared_ptr<Variable> value = TraverseExpressionNode(node->expression, codeGenerator, assemblyCode);

        // store return value to stack
        IVariableLocation* returnLocation = AssemblyCodeGenerator.GetReturnLocation(value->type->GetSize(), assemblyCode);
        value->type->GenerateAssign(returnLocation, value->location.get(), assemblyCode);

        // store return location to rax
        AssemblyCodeGenerator.MoveReturnLocationToRax(value->type->GetSize(), assemblyCode);
    }

    // return
    assemblyCode->AddLine(new AssemblyInstructionLine("ret"));
}

void SyntaxTreeTraverser::TraverseBodyNode(BodyNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    TraverseBodyCodeNode(node->GetCodeBlock(), codeGenerator, assemblyCode);
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseExpressionNode(AbstractExpressionNode* node, CodeGenerator* codeGenerator,
                                                                      AssemblyCode* assemblyCode)
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

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseBinaryOperatorExpressionNode(BinaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                                    AssemblyCode* assemblyCode)
{
    std::shared_ptr<Variable> firstVariable = TraverseExpressionNode(node->firstExpression, codeGenerator, assemblyCode);

    std::shared_ptr<Variable> left = nullptr;

    if (firstVariable->IsInline())
    {
        left = firstVariable;
    }
    else
    {
        // If is not inline create new register variable
        left.reset(codeGenerator->GetNewRegisterVariable(firstVariable->type, false, assemblyCode));
        codeGenerator->ApplyBinaryOperatorOnVariables(left, firstVariable, EOperators::ASSIGN_OPERATOR, assemblyCode);
    }

    for (OperatorExpressionPair* operatorExpression : *node->operatorExpressionPairs)
    {
        std::shared_ptr<Variable> right = TraverseExpressionNode(operatorExpression->expression, codeGenerator, assemblyCode);
        left = codeGenerator->ApplyBinaryOperatorOnVariables(left, right, operatorExpression->op, assemblyCode);
    }

    left->isFinal = true;  // Make the result final
    return std::shared_ptr<Variable>(left);
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseUnaryOperatorExpressionNode(UnaryOperatorExpressionNode* node, CodeGenerator* codeGenerator,
                                                                                   AssemblyCode* assemblyCode)
{
    std::shared_ptr<Variable> variable = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

    if (!node->applyToReference)
    {
        std::shared_ptr<Variable> newVariable = std::shared_ptr<Variable>(codeGenerator->GetNewLocalVariable(variable->type, false, assemblyCode));
        codeGenerator->ApplyBinaryOperatorOnVariables(newVariable, variable, EOperators::ASSIGN_OPERATOR, assemblyCode);
        variable = newVariable;
    }

    switch (node->preUnaryOperator)
    {
        case EPreUnaryOperators::PRE_NOT:
            variable->type->GenerateNot(variable->location.get(), assemblyCode);
            break;
        case EPreUnaryOperators::PRE_NEGATE:
            variable->type->GenerateNeg(variable->location.get(), assemblyCode);
            break;
        case EPreUnaryOperators::PRE_INCREMENT:
            variable->type->GenerateInc(variable->location.get(), assemblyCode);
            break;
        case EPreUnaryOperators::PRE_DECREMENT:
            variable->type->GenerateDec(variable->location.get(), assemblyCode);
            break;
    }

    // TODO: Post unary operators

    return variable;
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseAssignmentNode(AssignmentNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    std::shared_ptr<Variable> value = TraverseExpressionNode(node->value, codeGenerator, assemblyCode);

    for (Assignment* assignment : node->assignments)
    {
        std::shared_ptr<Variable> l_variable = TraverseVariableNode(assignment->L_value, codeGenerator, assemblyCode);

        if (l_variable->isFinal)
        {
            Logger.Log("Cannot assign to final variable " + assignment->L_value->ids[0], Logger::ERROR);
            continue;
        }

        EOperators op = EOperators::ASSIGN_OPERATOR;

        switch (assignment->assignOperator)
        {
            case EAssignOperators::ASSIGN:
                break;
            case EAssignOperators::ADD_ASSIGN:
                op = EOperators::ADD_OPERATOR;
                break;
            case EAssignOperators::SUB_ASSIGN:
                op = EOperators::SUB_OPERATOR;
                break;
            case EAssignOperators::MUL_ASSIGN:
                op = EOperators::MUL_OPERATOR;
                break;
            case EAssignOperators::DIV_ASSIGN:
                op = EOperators::DIV_OPERATOR;
                break;
            case EAssignOperators::MOD_ASSIGN:
                op = EOperators::MOD_OPERATOR;
                break;
        }

        codeGenerator->ApplyBinaryOperatorOnVariables(l_variable, value, op, assemblyCode);

        value = l_variable;
    }

    return value;
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseValueNode(AbstractValueNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
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

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseCallNode(CallNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    // Create new environment for arguments
    codeGenerator->PushNewEnvironment();

    std::vector<std::shared_ptr<Variable>> arguments;

    for (AbstractExpressionNode* argument : node->arguments)
    {
        std::shared_ptr<Variable> argumentVariable = TraverseExpressionNode(argument, codeGenerator, assemblyCode);
        arguments.push_back(argumentVariable);
    }

    std::shared_ptr<Function> function = codeGenerator->GetFunction(node->functionName);

    // If wrong argument type
    for (size_t i = 0; i < arguments.size(); i++)
    {
        if (!function->parameterTypes[i]->CanApplyToThis(arguments[i]->type.get()))
        {
            Logger.Log("Argument " + std::to_string(i) + " of function " + node->functionName + " has wrong type", Logger::ERROR);
            return nullptr;
        }
    }

    // Push arguments to stack in reverse order
    for (int i = arguments.size() - 1; i >= 0; i--)
    {
        arguments[i]->type->GenerateStackPush(arguments[i]->location.get(), assemblyCode);
    }

    AssemblyCodeGenerator.AddPreCall(assemblyCode);
    function->GenerateCallInstruction(assemblyCode);
    AssemblyCodeGenerator.AddPostCall(assemblyCode);

    // Pop argument environment
    codeGenerator->PopEnvironment(assemblyCode);

    // if void
    if (function->returnType == nullptr)
    {
        return nullptr;
    }

    // return is stored on stack at location pointed at by rax
    IVariableLocation* returnVariable = new RegistryPointerVarLocation("rax", 0);
    Variable* localVariable = codeGenerator->GetNewLocalVariable(function->returnType, false, assemblyCode);

    // Assign return value to local variable
    localVariable->type->GenerateAssign(localVariable->location.get(), returnVariable, assemblyCode);

    return std::shared_ptr<Variable>(localVariable);
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseParentesisExpressionNode(ParenthesisExpressionNode* node, CodeGenerator* codeGenerator,
                                                                                AssemblyCode* assemblyCode)
{
    return TraverseExpressionNode(node->expression, codeGenerator, assemblyCode);
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseStructNode(StructNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
{
    std::shared_ptr<StructType> tempStructType = std::shared_ptr<StructType>(new StructType());

    std::vector<std::pair<Property, std::shared_ptr<Variable>>> propertyAssigns;

    // Generate temporary structtype
    for (size_t i = 0; i < node->values.size(); i++)
    {
        std::shared_ptr<Variable> r_value = TraverseExpressionNode(node->values[i], codeGenerator, assemblyCode);
        propertyAssigns.push_back({tempStructType->AddProperty(std::to_string(i), r_value->type), r_value});
    }

    Variable* structVariable = codeGenerator->GetNewLocalVariable(tempStructType, false, assemblyCode);

    // Assign the values to the struct
    for (size_t i = 0; i < propertyAssigns.size(); i++)
    {
        std::pair<Property, std::shared_ptr<Variable>> propertyAssign = propertyAssigns[i];
        std::shared_ptr<Variable> l_value = propertyAssign.first.Apply(structVariable->location.get());
        std::shared_ptr<Variable> r_value = propertyAssign.second;

        l_value->type->GenerateAssign(l_value->location.get(), r_value->location.get(), assemblyCode);
    }

    return std::shared_ptr<Variable>(structVariable);
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseVariableNode(VariableNode* node, CodeGenerator* codeGenerator, AssemblyCode* assemblyCode)
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

    std::shared_ptr<Variable> variable = codeGenerator->GetVariable(node->ids[0]);

    for (size_t i = 1; i < node->ids.size(); i++)
    {
        StructType* structType = dynamic_cast<StructType*>(variable->type.get());

        if (structType == nullptr)
        {
            Logger.Log("Cannot access property as " + node->ids[i] + " is not a struct", Logger::ERROR);
            return nullptr;
        }

        variable = structType->ApplyProperty(node->ids[i], variable->location.get());
    }

    return variable;
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseAbstractConstValueNode(AbstractConstValueNode* node, CodeGenerator* codeGenerator,
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

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseLogicalConstValueNode(LogicalConstValueNode* node, CodeGenerator* codeGenerator,
                                                                             AssemblyCode* assemblyCode)
{
    std::shared_ptr<Type> type = codeGenerator->GetType("bool");
    IVariableLocation* location = codeGenerator->ConstructLogicalConstVariableLocation(node->GetValue());
    return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(location), type, true));
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseIntConstValueNode(IntConstValueNode* node, CodeGenerator* codeGenerator,
                                                                         AssemblyCode* assemblyCode)
{
    std::shared_ptr<Type> type = codeGenerator->GetType("int");
    IVariableLocation* location = codeGenerator->ConstructIntConstVariableLocation(node->GetValue());
    return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(location), type, true));
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseFloatConstValueNode(FloatConstValueNode* node, CodeGenerator* codeGenerator,
                                                                           AssemblyCode* assemblyCode)
{
    std::shared_ptr<Type> type = codeGenerator->GetType("float");
    IVariableLocation* location = codeGenerator->ConstructFloatConstVaribaleLocation(node->GetValue());
    return std::shared_ptr<Variable>(new Variable(std::shared_ptr<IVariableLocation>(location), type, true));
}

std::shared_ptr<Variable> SyntaxTreeTraverser::TraverseStringConstValueNode(StringConstValueNode* node, CodeGenerator* codeGenerator,
                                                                            AssemblyCode* assemblyCode)
{
    // TODO: String const value
    return nullptr;
}