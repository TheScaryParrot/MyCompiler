#pragma once

#include <iostream>

#include "../../assembly/AssemblyGenerator.cpp"
#include "../../syntaxTree/SyntaxTree.cpp"
#include "../../utils/Stack.cpp"
#include "../environment/environmentLinkedList/EnvironmentLinkedList.cpp"
#include "../environment/funcVars/variables/Variable.cpp"
#include "ECodeGeneratorBinaryOperators.cpp"
#include "ISyntaxTreeNodeIn.cpp"
#include "SyntaxTreeTraverser.cpp"

class CodeGenerator : ISyntaxTreeNodeIn
{
   public:
    CodeGenerator();

    AssemblyCode* GenerateCode(SyntaxTree* syntaxTree);

    // SyntaxTreeNode In --------------------------------
    virtual AssemblyCode* GenerateVarDeclaration(VarDeclarationNode* declaration) override;
    virtual AssemblyCode* GenerateFuncDeclaration(FuncDeclarationNode* declaration) override;
    virtual AssemblyCode* GenerateClassDeclaration(ClassDeclarationNode* declaration) override;

    virtual AssemblyCode* GenerateBody(BodyNode* body) override;

    virtual AssemblyCode* GenerateIfStatement(IfStatementNode* statement) override;
    virtual AssemblyCode* GenerateReturnStatement(ReturnStatementNode* statement) override;
    virtual AssemblyCode* GenerateWhileStatement(WhileStatementNode* whileStatement) override;
    virtual AssemblyCode* GenerateForStatement(ForStatementNode* forStatement) override;
    virtual AssemblyCode* GenerateContinueStatement(ContinueStatementNode* statement) override;
    virtual AssemblyCode* GenerateBreakStatement(BreakStatementNode* statement) override;

    virtual AssemblyCode* GenerateAssignment(AssignmentNode* assignmentNode) override;
    virtual AssemblyCode* GenerateBinaryOperation(OperatorExpressionNode* binaryOperation) override;
    virtual AssemblyCode* GenerateUnaryOperation(UnaryExpressionNode* unaryOperation) override;

    virtual AssemblyCode* GenerateValueChain(ValueChainNode* valueChain) override;
    virtual AssemblyCode* GenerateStaticValueChain(StaticValueChainNode* valueChain) override;
    virtual AssemblyCode* GenerateIDValue(IDValueNode* value) override;
    virtual AssemblyCode* GenerateCall(CallNode* call) override;
    virtual AssemblyCode* GenerateConstNumber(NumberConstValueNode* numberConst) override;
    virtual AssemblyCode* GenerateConstString(StringConstValueNode* stringConst) override;
    virtual AssemblyCode* GenerateConstLogical(LogicalConstValueNode* logicalConst) override;

    // --------------------------------------------------

    enum class EGeneratorType
    {
        Function,
        Global,
        Class
    };

   private:
    const std::string RETURN_VARIABLE_NAME = "return";

    Stack<EGeneratorType> generatorTypeStack;
    SyntaxTreeTraverser* traverser;
    EnvironmentLinkedList* environmentLinkedList;

    Stack<Variable*> tempVariableStack;
    Environment* tempVariableEnvironment = nullptr;
    Environment* tempVariableStaticEnvironment = nullptr;

    /// @brief Pops temporary varibales from TempVariableStack, performs operations on them and pushes the result back
    AssemblyCode* PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators operation);

    AssemblyCode* AssignVariable(Variable* variable, AbstractExpressionNode* value);

    AssemblyCode* AssignFunction(Function* function, AssemblyCode* body);

    std::string MangleFunctionName(std::string functionName, std::vector<Variable*> arguments);

    AssemblyCode* CallFunction(std::string name, unsigned int argumentsCount);

    /// @brief Tries to get type from the tempStaticEnvironment, then tempEnvironment, then the current environment
    Type* GetType(std::string identifier);

    /// @brief Tries to get variable from the tempStaticEnvironment, then tempEnvironment, then the current environment
    Variable* GetVariable(std::string identifier);

    /// @brief Tries to get function from the tempStaticEnvironment, then tempEnvironment, then the current environment
    Function* GetFunction(std::string identifier);

    void PushEnvironment();
    void PopEnvironment();

    void PushGeneratorType(EGeneratorType generatorType);
    void PopGeneratorType();

    void ActivateTempVariableEnvironment(bool staticEnvironment);
    void ClearTempVariableEnvironment(bool staticEnvironment);
};

CodeGenerator::CodeGenerator()
{
    this->generatorTypeStack.Push(EGeneratorType::Global);
    this->traverser = new SyntaxTreeTraverser();
    this->environmentLinkedList = new EnvironmentLinkedList();
    environmentLinkedList->Push(new Environment());
}

AssemblyCode* CodeGenerator::GenerateCode(SyntaxTree* syntaxTree)
{
    std::cout << "GenerateCode" << std::endl;
    return traverser->GenerateCodeBlock(this, syntaxTree->GetCodeBlock());
}

#pragma region SyntaxTreeNode In

AssemblyCode* CodeGenerator::GenerateVarDeclaration(VarDeclarationNode* declaration)
{
    std::cout << "GenerateVarDeclaration" << std::endl;

    DeclarationAttributes attributes = DeclarationAttributes(
        declaration->attributes.scope, declaration->attributes.isFinal, declaration->attributes.isInline);

    // TODO: Pay attention to current generator type

    // TODO: Use static
    // FIXME: AddVariable should also return assembly code

    Variable* variable = new Variable(GetType(declaration->type.GetIdentfier()), attributes);
    environmentLinkedList->AddVariable(declaration->name, variable);

    return AssignVariable(variable, declaration->value);
}

AssemblyCode* CodeGenerator::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    DeclarationAttributes attributes = DeclarationAttributes(
        declaration->attributes.scope, declaration->attributes.isFinal, declaration->attributes.isInline);

    Type* returnType = nullptr;

    if (!declaration->returnType.IsVoid())
    {
        returnType = GetType(declaration->returnType.GetIdentfier());
    }

    // TODO: Add return variable
    // TODO: Add arguments
    Function* function = new Function(nullptr, std::vector<Variable*>(), attributes);
    std::string mangledName = MangleFunctionName(declaration->name, function->parameters);
    environmentLinkedList->AddFunction(mangledName, function);

    PushGeneratorType(EGeneratorType::Function);

    AssemblyCode* body = traverser->GenerateStatement(this, declaration->statement);

    PopGeneratorType();

    return AssignFunction(function, body);
}

AssemblyCode* CodeGenerator::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    Type* type = new Type(declaration->name, declaration->isStatic);
    environmentLinkedList->AddType(declaration->name, std::shared_ptr<Type>(type));

    PushGeneratorType(EGeneratorType::Class);

    AssemblyCode* body = GenerateBody(declaration->body);

    PopGeneratorType();

    return body;
}

AssemblyCode* CodeGenerator::GenerateBody(BodyNode* body)
{
    return traverser->GenerateCodeBlock(this, body->GetCodeBlock());
}

AssemblyCode* CodeGenerator::GenerateIfStatement(IfStatementNode* statement)
{
    std::cout << "GenerateIfStatement" << std::endl;
    // TODO: If statement
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateReturnStatement(ReturnStatementNode* statement)
{
    return nullptr;
    // TODO: Fix this

    // return is defined in function environment
    Variable* returnVariable = GetVariable(RETURN_VARIABLE_NAME);

    AssemblyCode* assemblyCode = AssignVariable(returnVariable, statement->expression);

    assemblyCode->AddLines(AssemblyGenerator.GenerateReturnInstruction());

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateWhileStatement(WhileStatementNode* whileStatement)
{
    std::cout << "GenerateWhileStatement" << std::endl;
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateForStatement(ForStatementNode* forStatement)
{
    std::cout << "GenerateForStatement" << std::endl;
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateContinueStatement(ContinueStatementNode* statement)
{
    std::cout << "GenerateContinueStatement" << std::endl;
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateBreakStatement(BreakStatementNode* statement)
{
    std::cout << "GenerateBreakStatement" << std::endl;
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateAssignment(AssignmentNode* assignmentNode)
{
    std::cout << "GenerateAssignment" << std::endl;

    AssemblyCode* assemblyCode = new AssemblyCode();

    for (Assignment* assignment : assignmentNode->assignments)
    {
        EAssignOperators assignOperator = assignment->assignOperator;

        if (assignOperator == EAssignOperators::ASSIGN)
        {
            assemblyCode->AddLines(traverser->GenerateExpression(
                this, assignment->L_value));  // Evaluate L_value & store to Temp variables
            assemblyCode->AddLines(traverser->GenerateExpression(
                this, assignmentNode->value));  // Evaluate value & store to Temp variables
            assemblyCode->AddLines(PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators::ASSIGN));
            continue;
        }

        ECodeGeneratorBinaryOperators codeGeneratorOperator;

        switch (assignOperator)
        {
            case EAssignOperators::ADD_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::ADD;
                break;
            case EAssignOperators::SUB_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::SUB;
                break;
            case EAssignOperators::MUL_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MUL;
                break;
            case EAssignOperators::DIV_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::DIV;
                break;
            case EAssignOperators::MOD_ASSIGN:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MOD;
                break;
        }

        assemblyCode->AddLines(
            traverser->GenerateExpression(this, assignment->L_value));  // (for assign) Evaluate L_value &
                                                                        // store to Temp variables
        assemblyCode->AddLines(
            traverser->GenerateExpression(this, assignment->L_value));  // (for operation ahead of assign) Evaluate
                                                                        // L_value & store to Temp variables
        assemblyCode->AddLines(
            traverser->GenerateExpression(this, assignmentNode->value));  // Evaluate value & store to Temp variables
        assemblyCode->AddLines(PerformBinaryOperationOnTempVariables(codeGeneratorOperator));
        assemblyCode->AddLines(PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators::ASSIGN));
    }

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateBinaryOperation(OperatorExpressionNode* binaryOperationNode)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    assemblyCode->AddLines(traverser->GenerateExpression(this, binaryOperationNode->firstExpression));

    for (OperatorExpressionPair* operatorExpressionPair : *binaryOperationNode->operatorExpressionPairs)
    {
        assemblyCode->AddLines(traverser->GenerateExpression(this, operatorExpressionPair->expression));

        ECodeGeneratorBinaryOperators codeGeneratorOperator;

        switch (operatorExpressionPair->op)
        {
            case EOperators::ADD_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::ADD;
                break;
            case EOperators::SUB_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::SUB;
                break;
            case EOperators::MUL_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MUL;
                break;
            case EOperators::DIV_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::DIV;
                break;
            case EOperators::MOD_OPERATOR:
                codeGeneratorOperator = ECodeGeneratorBinaryOperators::MOD;
                break;
        }

        assemblyCode->AddLines(PerformBinaryOperationOnTempVariables(codeGeneratorOperator));
    }

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateUnaryOperation(UnaryExpressionNode* unaryOperation)
{
    std::cout << "GenerateUnaryOperation" << std::endl;
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateValueChain(ValueChainNode* valueChain)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (AbstractExpressionNode* value : valueChain->propertyAccesses)
    {
        assemblyCode->AddLines(traverser->GenerateExpression(this, value));
        ActivateTempVariableEnvironment(false);  // Activate environment of temp variable
                                                 // (which is the result of generateExpression)
    }

    ClearTempVariableEnvironment(false);  // Clear the temp variable environment as the value chain is done

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateStaticValueChain(StaticValueChainNode* valueChain)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (AbstractExpressionNode* value : valueChain->propertyAccesses)
    {
        assemblyCode->AddLines(traverser->GenerateExpression(this, value));
        // TODO: Activate static environment of type
        ActivateTempVariableEnvironment(true);  // Activate environment of temp variable
                                                // (which is the result of generateExpression)
    }

    ClearTempVariableEnvironment(true);  // Clear the temp variable environment as the value chain is done

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateIDValue(IDValueNode* value)
{
    Variable* variable = GetVariable(value->GetValue());
    tempVariableStack.Push(variable);
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateCall(CallNode* call)
{
    for (AbstractExpressionNode* argument : call->arguments)
    {
        traverser->GenerateExpression(this, argument);
    }

    return CallFunction(call->functionName, call->arguments.size());
}

AssemblyCode* CodeGenerator::GenerateConstNumber(NumberConstValueNode* numberConst)
{
    std::cout << "GenerateConstNumber" << std::endl;
    tempVariableStack.Push(new Variable(GetType("int"), DeclarationAttributes()));
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateConstString(StringConstValueNode* stringConst)
{
    std::cout << "GenerateConstString" << std::endl;
    tempVariableStack.Push(new Variable(GetType("string"), DeclarationAttributes()));
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateConstLogical(LogicalConstValueNode* logicalConst)
{
    std::cout << "GenerateConstLogical" << std::endl;
    tempVariableStack.Push(new Variable(GetType("bool"), DeclarationAttributes()));
    return nullptr;
}

#pragma endregion

AssemblyCode* CodeGenerator::PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators operation)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    // TODO: Generate function name
    std::string operatorFunctionName = GetOperationFunctionName(operation);

    Variable* r_var = tempVariableStack.Pop();
    ActivateTempVariableEnvironment(false);
    tempVariableStack.Push(r_var);  // push the r_value back to the stack

    // only 1 argument as the l_value is seen as the method caller
    assemblyCode->AddLines(CallFunction(operatorFunctionName, 1));

    return assemblyCode;
}

AssemblyCode* CodeGenerator::AssignVariable(Variable* variable, AbstractExpressionNode* value)
{
    tempVariableStack.Push(variable);

    AssemblyCode* assemblyCode = traverser->GenerateExpression(this, value);
    return assemblyCode->AddLines(PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators::ASSIGN));
}

AssemblyCode* CodeGenerator::AssignFunction(Function* function, AssemblyCode* body)
{
    // TODO: Assign function
    return nullptr;
}

std::string CodeGenerator::MangleFunctionName(std::string functionName, std::vector<Variable*> arguments)
{
    std::string result = functionName;

    for (Variable* variable : arguments)
    {
        result += AssemblyGenerator.LABEL_MANGLING_TOKEN + variable->GetType()->name;
    }

    return result;
}

AssemblyCode* CodeGenerator::CallFunction(std::string name, unsigned int argumentsCount)
{
    std::cout << "Call function " << name << std::endl;

    AssemblyCode* assemblyCode = new AssemblyCode();

    // If the function is accessed using a tempVariable environment add one argument (which is the method caller)
    if (tempVariableEnvironment != nullptr)
    {
        std::cout << "TempVariableEnvironment is active\n";
        argumentsCount++;
    }

    std::cout << "Arguments count 1: " << argumentsCount << std::endl;

    std::vector<Variable*> arguments;

    for (unsigned int i = 0; i < argumentsCount; i++)
    {
        arguments.push_back(tempVariableStack.Pop());
    }

    std::cout << "Arguments count 2: " << arguments.size() << std::endl;

    std::string mangledName = MangleFunctionName(name, arguments);

    Function* function = GetFunction(mangledName);

    // TODO: Assign arguments

    if (function == nullptr)
    {
        return nullptr;
    }

    return assemblyCode->AddLines(function->GetFunctionCallCode());
}

Type* CodeGenerator::GetType(std::string identifier)
{
    if (tempVariableStaticEnvironment != nullptr)
    {
        return tempVariableStaticEnvironment->GetType(identifier);
    }

    if (tempVariableEnvironment != nullptr)
    {
        return tempVariableEnvironment->GetType(identifier);
    }

    return environmentLinkedList->GetType(identifier);
}

Variable* CodeGenerator::GetVariable(std::string identifier)
{
    if (tempVariableStaticEnvironment != nullptr)
    {
        return tempVariableStaticEnvironment->GetVariable(identifier);
    }

    if (tempVariableEnvironment != nullptr)
    {
        return tempVariableEnvironment->GetVariable(identifier);
    }

    return environmentLinkedList->GetVariable(identifier);
}

Function* CodeGenerator::GetFunction(std::string identifier)
{
    if (tempVariableStaticEnvironment != nullptr)
    {
        return tempVariableStaticEnvironment->GetFunction(identifier);
    }

    if (tempVariableEnvironment != nullptr)
    {
        return tempVariableEnvironment->GetFunction(identifier);
    }

    return environmentLinkedList->GetFunction(identifier);
}

void CodeGenerator::PushEnvironment() { environmentLinkedList->Push(new Environment()); }

void CodeGenerator::PopEnvironment() { environmentLinkedList->Pop(); }

void CodeGenerator::PushGeneratorType(EGeneratorType generatorType) { generatorTypeStack.Push(generatorType); }

void CodeGenerator::PopGeneratorType() { generatorTypeStack.Pop(); }

void CodeGenerator::ActivateTempVariableEnvironment(bool staticEnvironment)
{
    if (staticEnvironment)
    {
        tempVariableStaticEnvironment = new Environment();
        return;
    }

    tempVariableEnvironment = new Environment();
}

void CodeGenerator::ClearTempVariableEnvironment(bool staticEnvironment)
{
    if (staticEnvironment)
    {
        tempVariableStaticEnvironment = nullptr;
        return;
    }

    tempVariableEnvironment = nullptr;
}
