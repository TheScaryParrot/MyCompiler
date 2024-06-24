#pragma once

#include <memory>
#include <stack>

#include "../../assembly/AssemblyGenerator.cpp"
#include "../environment/scopeSpecificEnvironments/ClassScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/FunctionScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/GlobalScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/environmentLinkedList/ScopeSpecificEnvironmentLinkedList.cpp"
#include "ECodeGeneratorBinaryOperators.cpp"

class CodeGenerator
{
   public:
    CodeGenerator();

    void PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment);
    void PopEnvironment();

    Variable* AddVariable(std::string name, std::string typeIdentifier, DeclarationAttributes attributes);

    Function* AddVoidFunction(std::string name /*TODO: Add parameters*/, DeclarationAttributes attributes);
    Function* AddFunction(std::string name, std::string returnTypeIdentifier /*TODO: Add parameters*/,
                          DeclarationAttributes attributes);
    AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body);

    /// @brief Generates a call to a function. Arguments are poped from TempVariableStack
    /// @brief How many are poped is determined by argumentsCount
    /// @brief The function return is pushed to TempVariableStack
    AssemblyCode* CallFunction(std::string name, unsigned int argumentsCount);

    Type* AddType(std::string name);
    ClassScopeEnvironment* AddClassScopeEnvironmentToType(Type* type);

    AssemblyCode* GenerateReturnStatement(AssemblyCode* expression);
    AssemblyCode* GenerateContinueStatement();
    AssemblyCode* GenerateBreakStatement();

    void InitLoopEnvironment();
    AssemblyCode* GenerateWhile(AssemblyCode* condition, AssemblyCode* body);
    AssemblyCode* GenerateFor(AssemblyCode* declaration, AssemblyCode* condition, AssemblyCode* increment,
                              AssemblyCode* body);

    /// @brief Pops temporary varibales from TempVariableStack, performs operations on them and pushes the result back
    AssemblyCode* PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators operation);

    /// @brief Pushes the environment of the top TempVariable to the environment stack
    void ActivateTempVariableEnvironment();

    /// @brief Sets the current TempVariableEnvironment to nullptr
    void ClearTempVariableEnvironment();

    void PushVariableToTempVariable(std::string variableName);

    void PushNumberConstToTempVariable(std::string number);
    void PushStringConstToTempVariable(std::string string);
    void PushLogicalConstToTempVariable(bool isTrue);

   private:
    ScopeSpecificEnvironmentLinkedList environmentLinkedList;

    ScopeSpecificEnvironmentLinkedListElement* GetCurrentEnvironment();

    Function* AddFunction(std::string name, Type* returnType /*TODO: Add parameters*/,
                          DeclarationAttributes attributes);

    unsigned int jumpLabelCounter = 0;

    std::string GetNewJumpLabel();
    JumpLabel* AddJumpLabel(std::string name);

    /// @brief Stack of currently used temporary variables (used for: expression output, function return)
    std::stack<Variable*> tempVariableStack;

    /// @brief Environment of the top environment variable; Has to be set by ActivateTempVariableEnvironment
    IScopeSpecificEnvironment* tempVariableEnvironment;
};

CodeGenerator::CodeGenerator()
{
    environmentLinkedList = ScopeSpecificEnvironmentLinkedList();
    environmentLinkedList.PushEnvironment(std::make_shared<GlobalScopeEnvironment>());
}

void CodeGenerator::PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment)
{
    environmentLinkedList.PushEnvironment(environment);
}

void CodeGenerator::PopEnvironment() { return environmentLinkedList.PopEnvironment(); }

ScopeSpecificEnvironmentLinkedListElement* CodeGenerator::GetCurrentEnvironment()
{
    return environmentLinkedList.GetHead();
}

Variable* CodeGenerator::AddVariable(std::string name, std::string typeIdentifier, DeclarationAttributes attributes)
{
    Type* type = GetCurrentEnvironment()->GetType(typeIdentifier);

    Variable* variable = new Variable(type, attributes);

    GetCurrentEnvironment()->AddVariable(name, variable);

    return variable;
}

Function* CodeGenerator::AddVoidFunction(std::string name /*TODO: Add parameters*/, DeclarationAttributes attributes)
{
    return AddFunction(name, nullptr, attributes);
}

Function* CodeGenerator::AddFunction(std::string name, std::string returnTypeIdentifier,
                                     DeclarationAttributes attributes)
{
    Type* returnType = GetCurrentEnvironment()->GetType(returnTypeIdentifier);

    return AddFunction(name, returnType, attributes);
}

Function* CodeGenerator::AddFunction(std::string name, Type* returnType /*TODO: Add parameters*/,
                                     DeclarationAttributes attributes)
{
    // TODO: Construct parameters from type and name
    // TODO: Get return Variable from type
    Function* function = new Function(name, nullptr, attributes);  // TODO: Add parameters

    // TODO: Function name mangling using parameters
    GetCurrentEnvironment()->AddFunction(name, function);

    return function;
}

AssemblyCode* CodeGenerator::SetFunctionBody(Function* function, AssemblyCode* body)
{
    return GetCurrentEnvironment()->SetFunctionBody(function, body);
}

AssemblyCode* CodeGenerator::CallFunction(std::string name, unsigned int argumentsCount)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    // TODO: Call function
    return assemblyCode;
}

Type* CodeGenerator::AddType(std::string name)
{
    Type* type = new Type(name);
    GetCurrentEnvironment()->AddType(name, type);
    return type;
}

ClassScopeEnvironment* CodeGenerator::AddClassScopeEnvironmentToType(Type* type)
{
    ClassScopeEnvironment* classScopeEnvironment = new ClassScopeEnvironment();
    GetCurrentEnvironment()->SetTypeEnvironment(type, classScopeEnvironment);
    return classScopeEnvironment;
}

AssemblyCode* CodeGenerator::GenerateReturnStatement(AssemblyCode* expression)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    // TODO: Assign return
    // assemblyCode->AddLines(this->SetVariable("return", nullptr));
    return AssemblyGenerator.GenerateReturnInstruction();
}

AssemblyCode* CodeGenerator::GenerateContinueStatement()
{
    return AssemblyGenerator.GenerateJumpToJumpLabel(GetCurrentEnvironment()->GetJumpLabel("continue"));
}

AssemblyCode* CodeGenerator::GenerateBreakStatement()
{
    return AssemblyGenerator.GenerateJumpToJumpLabel(GetCurrentEnvironment()->GetJumpLabel("break"));
}

void CodeGenerator::InitLoopEnvironment()
{
    environmentLinkedList.PushEnvironment(std::make_shared<FunctionScopeEnvironment>());
    AddJumpLabel("continue");  // eval label
    AddJumpLabel("break");     // final label
}

AssemblyCode* CodeGenerator::GenerateWhile(AssemblyCode* condition, AssemblyCode* body)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    JumpLabel* continueLabel = GetCurrentEnvironment()->GetJumpLabel("continue");
    JumpLabel* breakLabel = GetCurrentEnvironment()->GetJumpLabel("break");

    assemblyCode->AddLines(AssemblyGenerator.GenerateLabel(continueLabel->GetName()));  // eval label
    assemblyCode->AddLines(condition);                                                  // condition

    // TODO: Add jump to break label if condition is false
    assemblyCode->AddLines(body);  // body

    assemblyCode->AddLines(AssemblyGenerator.GenerateJumpToJumpLabel(continueLabel));

    assemblyCode->AddLines(AssemblyGenerator.GenerateLabel(breakLabel->GetName()));

    environmentLinkedList.PopEnvironment();

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateFor(AssemblyCode* declaration, AssemblyCode* condition, AssemblyCode* increment,
                                         AssemblyCode* body)
{
    // TODO: Generate FOR loop
    return nullptr;
}

AssemblyCode* CodeGenerator::PerformBinaryOperationOnTempVariables(ECodeGeneratorBinaryOperators operation)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    // TODO: Generate function name
    std::string operatorFunctionName = "";

    // only 1 argument as the l_value is seen as the method caller and
    // added because TempVariableEnvironment was activated
    assemblyCode->AddLines(CallFunction(operatorFunctionName, 1));

    return assemblyCode;
}

void CodeGenerator::ActivateTempVariableEnvironment()
{
    if (tempVariableStack.empty())
    {
        std::cerr << "Error: TempVariableStack is empty\n";
        return;
    }

    Variable* tempVariable = tempVariableStack.top();

    if (tempVariable == nullptr)
    {
        std::cerr << "Error: TempVariable is nullptr\n";
        return;
    }

    Type* tempVariableType = tempVariable->GetType();

    if (tempVariableType == nullptr)
    {
        std::cerr << "Error: TempVariable is nullptr\n";
        return;
    }

    // Sets tempVariableEnvironment to the environment of the top TempVariables type
    tempVariableEnvironment = GetCurrentEnvironment()->GetTypeEnvironment(tempVariableType);
}

void CodeGenerator::ClearTempVariableEnvironment() { tempVariableEnvironment = nullptr; }

void CodeGenerator::PushVariableToTempVariable(std::string variableName)
{
    tempVariableStack.push(GetCurrentEnvironment()->GetVariable(variableName));
}

void CodeGenerator::PushNumberConstToTempVariable(std::string number)
{
    // TODO: Do this
}

void CodeGenerator::PushStringConstToTempVariable(std::string string)
{
    // TODO: Do this
}

void CodeGenerator::PushLogicalConstToTempVariable(bool isTrue)
{
    // TODO: Do this
}

std::string CodeGenerator::GetNewJumpLabel() { return "JL" + std::to_string(jumpLabelCounter++); }

JumpLabel* CodeGenerator::AddJumpLabel(std::string name)
{
    JumpLabel* jumpLabel = new JumpLabel(GetNewJumpLabel());

    GetCurrentEnvironment()->AddJumpLabel(name, jumpLabel);

    return jumpLabel;
}
