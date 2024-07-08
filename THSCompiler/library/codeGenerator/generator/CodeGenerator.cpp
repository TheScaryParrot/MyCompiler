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

    virtual AssemblyCode* GenerateBody(BodyNode* body, bool newEnvironment) override;

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

    /// @brief Variable that is currently used when accessing things in a relative way (properties, methods)
    Variable* relativeAccessVariable = nullptr;

    /// @brief Uses relativeAccessVariable as l_value and pops from tempVariableStack as r_value. Result is pushed to
    /// tempVariableStack
    AssemblyCode* PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators operation);

    /// @brief Performs binary operation on two expressions and  pushes the result to tempVariableStack
    AssemblyCode* PerformBinaryOperationOnExpressions(AbstractExpressionNode* l_value, AbstractExpressionNode* r_value,
                                                      ECodeGeneratorBinaryOperators operation);

    AssemblyCode* AssignVariable(Variable* variable, AbstractExpressionNode* value);

    AssemblyCode* AssignFunction(std::string mangledName, Function* function, AssemblyCode* body);

    std::string MangleFunctionName(std::string functionName, std::vector<Variable*> arguments);

    AssemblyCode* CallFunction(std::string name, unsigned int argumentsCount);
    AssemblyCode* CallFunction(Function* function, Stack<Variable*> arguments);

    /// @brief Sets the environmentLinkedList to the environment of the relativeAccessVariable. Old linked list is
    /// lost. Don't forget to backup and restore
    void ActivateRelativeAccessVariableEnvironment(bool isStatic);

    unsigned int functionLabelCounter = 1;
    /// @brief Generates a new function label based on the functions mangled name
    std::string NewFunctionLabel(std::string mangledName)
    {
        // FL13-[mangledName]
        return "FL" + std::to_string(functionLabelCounter++) + AssemblyGenerator.LABEL_MANGLING_TOKEN + mangledName;
    }
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

    Variable* variable = new Variable(environmentLinkedList->GetType(declaration->type.GetIdentfier()), attributes);
    environmentLinkedList->AddVariable(declaration->name, variable);

    return AssignVariable(variable, declaration->value);
}

AssemblyCode* CodeGenerator::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    std::cout << "GenerateFuncDeclaration: " << declaration->name << std::endl;

    DeclarationAttributes attributes = DeclarationAttributes(
        declaration->attributes.scope, declaration->attributes.isFinal, declaration->attributes.isInline);

    // new environment for function
    environmentLinkedList->Push(new Environment());

    // Add return variable to environment
    Variable* returnVariable = nullptr;

    if (!declaration->returnType.IsVoid())
    {
        Type* returnType = environmentLinkedList->GetType(declaration->returnType.GetIdentfier());
        returnVariable = new Variable(returnType, DeclarationAttributes(EScopes::PRIVATE, false, false));

        environmentLinkedList->AddVariable(RETURN_VARIABLE_NAME, returnVariable);
    }

    // Add arguments to environment
    std::vector<Variable*> arguments;

    for (ParameterDeclarationNode* argument : *declaration->parameters)
    {
        Variable* variable = new Variable(environmentLinkedList->GetType(argument->type),
                                          DeclarationAttributes(EScopes::PRIVATE, false, false));
        environmentLinkedList->AddVariable(argument->name, variable);
        arguments.push_back(variable);
    }

    // Make function
    Function* function = new Function(returnVariable, arguments, attributes);

    std::string mangledName = MangleFunctionName(declaration->name, function->parameters);

    generatorTypeStack.Push(EGeneratorType::Function);

    AssemblyCode* body = GenerateBody(declaration->body, false);

    generatorTypeStack.Pop();
    // Leave function environment
    environmentLinkedList->Pop();

    // Add function to environment
    environmentLinkedList->AddFunction(mangledName, function);

    return AssignFunction(mangledName, function, body);
}

AssemblyCode* CodeGenerator::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    Type* type = new Type(declaration->name, declaration->isStatic);
    environmentLinkedList->AddType(declaration->name, std::shared_ptr<Type>(type));

    Environment* environment = new Environment();
    // TODO: Make static and non-static environments; will need to look how I do this
    environmentLinkedList->SetEnvironment(type, std::shared_ptr<Environment>(environment), false);

    generatorTypeStack.Push(EGeneratorType::Class);
    environmentLinkedList->Push(environment);

    AssemblyCode* body = GenerateBody(declaration->body, false);

    generatorTypeStack.Pop();
    environmentLinkedList->Pop();

    return body;
}

AssemblyCode* CodeGenerator::GenerateBody(BodyNode* body, bool newEnvironment)
{
    if (newEnvironment)
    {
        environmentLinkedList->Push(new Environment());
    }

    AssemblyCode* assemblyCode = traverser->GenerateCodeBlock(this, body->GetCodeBlock());

    if (newEnvironment)
    {
        environmentLinkedList->Pop();
    }

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateIfStatement(IfStatementNode* statement)
{
    std::cout << "GenerateIfStatement" << std::endl;
    // TODO: If statement
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateReturnStatement(ReturnStatementNode* statement)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    if (statement->expression != nullptr)
    {
        // return is defined in function environment
        Variable* returnVariable = environmentLinkedList->GetVariable(RETURN_VARIABLE_NAME);

        assemblyCode->AddLines(AssignVariable(returnVariable, statement->expression));
    }

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

    // Evaluate first r_value
    assemblyCode->AddLines(traverser->GenerateExpression(this, assignmentNode->value));

    for (Assignment* assignment : assignmentNode->assignments)
    {
        // Get l_value variable
        assemblyCode->AddLines(traverser->GenerateExpression(this, assignment->L_value));
        Variable* l_value = tempVariableStack.Pop();
        relativeAccessVariable = l_value;

        EAssignOperators assignOperator = assignment->assignOperator;

        if (assignOperator != EAssignOperators::ASSIGN)
        {
            ECodeGeneratorBinaryOperators binaryOperator;

            switch (assignOperator)
            {
                case EAssignOperators::ADD_ASSIGN:
                    binaryOperator = ECodeGeneratorBinaryOperators::ADD;
                    break;
                case EAssignOperators::SUB_ASSIGN:
                    binaryOperator = ECodeGeneratorBinaryOperators::SUB;
                    break;
                case EAssignOperators::MUL_ASSIGN:
                    binaryOperator = ECodeGeneratorBinaryOperators::MUL;
                    break;
                case EAssignOperators::DIV_ASSIGN:
                    binaryOperator = ECodeGeneratorBinaryOperators::DIV;
                    break;
                case EAssignOperators::MOD_ASSIGN:
                    binaryOperator = ECodeGeneratorBinaryOperators::MOD;
                    break;
            }

            // Old r_value is top of stack
            // l_value is relativeAccessVariable
            assemblyCode->AddLines(PerformBinaryOperationWithTempVariable(binaryOperator));
        }

        // Old r_value is top of stack (might also be the result of the preceding binary operation)
        // l_value is relativeAccessVariable
        assemblyCode->AddLines(PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators::ASSIGN));
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

        assemblyCode->AddLines(PerformBinaryOperationWithTempVariable(codeGeneratorOperator));
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

    // backup old environment
    EnvironmentLinkedList* oldEnvironment = environmentLinkedList;

    for (AbstractExpressionNode* value : valueChain->propertyAccesses)
    {
        assemblyCode->AddLines(traverser->GenerateExpression(this, value));

        Variable* expressionOutVariable = tempVariableStack.Pop();
        relativeAccessVariable = expressionOutVariable;

        // FIXME: delete new environment from memory
        ActivateRelativeAccessVariableEnvironment(false);
    }

    relativeAccessVariable = nullptr;
    environmentLinkedList = oldEnvironment;

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateStaticValueChain(StaticValueChainNode* valueChain)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    // backup old environment
    EnvironmentLinkedList* oldEnvironment = environmentLinkedList;

    for (AbstractExpressionNode* value : valueChain->propertyAccesses)
    {
        assemblyCode->AddLines(traverser->GenerateExpression(this, value));

        Variable* expressionOutVariable = tempVariableStack.Pop();
        relativeAccessVariable = expressionOutVariable;

        // FIXME: delete new environment from memory
        ActivateRelativeAccessVariableEnvironment(true);
    }

    relativeAccessVariable = nullptr;
    environmentLinkedList = oldEnvironment;

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateIDValue(IDValueNode* value)
{
    Variable* variable = environmentLinkedList->GetVariable(value->GetValue());
    tempVariableStack.Push(variable);
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateCall(CallNode* call)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    // Adding arguments in reverse order
    for (unsigned int i = call->arguments.size() - 1; i >= 0; i--)
    {
        assemblyCode->AddLines(traverser->GenerateExpression(this, call->arguments[i]));
    }

    return assemblyCode->AddLines(CallFunction(call->functionName, call->arguments.size()));
}

AssemblyCode* CodeGenerator::GenerateConstNumber(NumberConstValueNode* numberConst)
{
    std::cout << "GenerateConstNumber" << std::endl;

    Variable* variable =
        new Variable(environmentLinkedList->GetNumberConstType(), DeclarationAttributes(EScopes::PRIVATE, true, true));
    variable->SetGetLocation(AssemblyGenerator.GenerateNumberConst(numberConst->GetValue()));

    tempVariableStack.Push(variable);

    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateConstString(StringConstValueNode* stringConst)
{
    std::cout << "GenerateConstString" << std::endl;

    Variable* variable =
        new Variable(environmentLinkedList->GetStringConstType(), DeclarationAttributes(EScopes::PRIVATE, true, true));
    variable->SetGetLocation(AssemblyGenerator.GenerateStringConst(stringConst->GetValue()));

    tempVariableStack.Push(variable);

    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateConstLogical(LogicalConstValueNode* logicalConst)
{
    std::cout << "GenerateConstLogical" << std::endl;
    Variable* variable =
        new Variable(environmentLinkedList->GetLogicConstType(), DeclarationAttributes(EScopes::PRIVATE, true, true));
    variable->SetGetLocation(AssemblyGenerator.GenerateLogicConst(logicalConst->GetValue()));

    tempVariableStack.Push(variable);

    return nullptr;
}

#pragma endregion

AssemblyCode* CodeGenerator::PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators operation)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    // TODO: Generate function name
    std::string operatorFunctionName = GetOperationFunctionName(operation);

    // backup old environment
    EnvironmentLinkedList* oldEnvironment = environmentLinkedList;

    // activate l_value environment
    ActivateRelativeAccessVariableEnvironment(false);

    // only 1 argument as the l_value is seen as the method caller
    assemblyCode->AddLines(CallFunction(operatorFunctionName, 1));

    // restore old environment
    environmentLinkedList = oldEnvironment;

    return assemblyCode;
}

AssemblyCode* CodeGenerator::PerformBinaryOperationOnExpressions(AbstractExpressionNode* l_value,
                                                                 AbstractExpressionNode* r_value,
                                                                 ECodeGeneratorBinaryOperators operation)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    assemblyCode->AddLines(traverser->GenerateExpression(this, l_value));
    relativeAccessVariable = tempVariableStack.Pop();  // Pop l_value to relativeAccessVariable

    assemblyCode->AddLines(traverser->GenerateExpression(this, r_value));

    return assemblyCode->AddLines(PerformBinaryOperationWithTempVariable(operation));
}

AssemblyCode* CodeGenerator::AssignVariable(Variable* variable, AbstractExpressionNode* value)
{
    relativeAccessVariable = variable;
    AssemblyCode* assemblyCode = new AssemblyCode();
    assemblyCode->AddLines(traverser->GenerateExpression(this, value));

    return assemblyCode->AddLines(PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators::ASSIGN));
}

AssemblyCode* CodeGenerator::AssignFunction(std::string mangledName, Function* function, AssemblyCode* body)
{
    if (function->IsInline())
    {
        function->SetCallCode(Function::GenerateInlineFunctionCallCode(body));
        return nullptr;
    }

    std::string functionLabel = NewFunctionLabel(mangledName);
    function->SetCallCode(Function::GenerateCallInstructionFunctionCallCode(functionLabel));

    AssemblyCode* assemblyCode = AssemblyGenerator.GenerateLabel(functionLabel);
    return assemblyCode->AddLines(body);
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

    std::vector<Variable*> arguments;

    if (relativeAccessVariable != nullptr)
    {
        arguments.push_back(relativeAccessVariable);
    }

    for (unsigned int i = 0; i < argumentsCount; i++)
    {
        arguments.push_back(tempVariableStack.Pop());
    }

    std::string mangledName = MangleFunctionName(name, arguments);

    Function* function = environmentLinkedList->GetFunction(mangledName);

    if (function == nullptr)
    {
        return nullptr;
    }

    // assign arguments to the function argument variables
    for (unsigned int i = 0; i < arguments.size(); i++)
    {
        Variable* functionArgumentVar = function->parameters[i];
        Variable* argumentVar = arguments[i];

        if (functionArgumentVar == nullptr)
        {
            std::cout << "Function argument variable is null" << std::endl;
            continue;
        }

        if (argumentVar == nullptr)
        {
            std::cout << "Argument variable is null" << std::endl;
            continue;
        }

        relativeAccessVariable = functionArgumentVar;
        tempVariableStack.Push(argumentVar);
        PerformBinaryOperationWithTempVariable(ECodeGeneratorBinaryOperators::ASSIGN);
    }

    // Push return variable to tempVariableStack
    if (function->returnVariable != nullptr)
    {
        tempVariableStack.Push(function->returnVariable);
    }

    return assemblyCode->AddLines(function->GetFunctionCallCode());
}

AssemblyCode* CodeGenerator::CallFunction(Function* function, Stack<Variable*> arguments)
{
    if (function->IsInline())
    {
        // TODO: this
        environmentLinkedList->PushNew();
    }

    return nullptr;
}

void CodeGenerator::ActivateRelativeAccessVariableEnvironment(bool isStatic)
{
    if (relativeAccessVariable == nullptr)
    {
        std::cout << "Tried to activate relative access variable environment but it is null. Setting empty environment."
                  << std::endl;
        environmentLinkedList = new EnvironmentLinkedList();
        return;
    }

    EnvironmentLinkedList* newEnvironment = new EnvironmentLinkedList();

    Type* type = relativeAccessVariable->GetType();

    if (type == nullptr)
    {
        std::cout << "Relative access variable type is null" << std::endl;
        return;
    }

    IEnvironment* environment = environmentLinkedList->GetEnvironment(type, isStatic);

    newEnvironment->Push(environment);

    environmentLinkedList = newEnvironment;
}
