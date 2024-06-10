#pragma once

#include <memory>
#include <stack>

#include "ECodeGeneratorExpressionOperators.cpp"

#include "../environment/scopeSpecificEnvironments/environmentLinkedList/ScopeSpecificEnvironmentLinkedList.cpp"
#include "../environment/scopeSpecificEnvironments/GlobalScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/FunctionScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/ClassScopeEnvironment.cpp"

#include "../../assembly/AssemblyGenerator.cpp"

class CodeGenerator
{
public:
    CodeGenerator();

    void PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment);
    void PopEnvironment();

    Variable* AddVariable(std::string name, std::string typeIdentifier);
    //AssemblyCode* SetVariable(std::string variableName, IVariableLocationGetter* assignValueLocation);

    Function* AddVoidFunction(std::string name /*TODO: Add parameters*/);
    Function* AddFunction(std::string name, std::string returnTypeIdentifier /*TODO: Add parameters*/);
    AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body);

    Type* AddType(std::string name);
    ClassScopeEnvironment* AddClassScopeEnvironmentToType(Type* type);

    AssemblyCode* GenerateReturnStatement(AssemblyCode* expression);
    AssemblyCode* GenerateContinueStatement();
    AssemblyCode* GenerateBreakStatement();

    void InitLoopEnvironment();
    AssemblyCode* GenerateWhile(AssemblyCode* condition, AssemblyCode* body);
    AssemblyCode* GenerateFor(AssemblyCode* declaration, AssemblyCode* condition, AssemblyCode* increment, AssemblyCode* body);

    AssemblyCode* AssignExpressionOutToVariable(std::string variableName);

    /// @brief Generates code for an expression with variable on the left and ExpressionOut on the right. Output is stored in expression output variable.
    AssemblyCode* PerformOperation_LVariable_RExpressionOut(std::string variableName, ECodeGeneratorExpressionOperators operation);

    /// @brief Generates code for an expression with ExpressionOut on the left and a VariableLocationGetter on the right.
    AssemblyCode* PerformOperation_LExpressionOut_RVariableLocation(IVariableLocationGetter* locationGetter, ECodeGeneratorExpressionOperators operation);

private:
    ScopeSpecificEnvironmentLinkedList environmentLinkedList;

    ScopeSpecificEnvironmentLinkedListElement* GetCurrentEnvironment();

    Function* AddFunction(std::string name, Type* returnType /*TODO: Add parameters*/);

    unsigned int jumpLabelCounter = 0;

    std::string GetNewJumpLabel();
    JumpLabel* AddJumpLabel(std::string name);

    /// @brief Stack of currently used temporary variables (used for: expression output, function return)
    std::stack<Variable*> TempVariableStack;
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

void CodeGenerator::PopEnvironment()
{
    return environmentLinkedList.PopEnvironment();
}


ScopeSpecificEnvironmentLinkedListElement* CodeGenerator::GetCurrentEnvironment()
{
    return environmentLinkedList.GetHead();
}

Variable* CodeGenerator::AddVariable(std::string name, std::string typeIdentifier)
{
    Type* type = GetCurrentEnvironment()->GetType(typeIdentifier);
    
    Variable* variable = new Variable(type);

    GetCurrentEnvironment()->AddVariable(name, variable);

    return variable;
}

/*AssemblyCode* CodeGenerator::SetVariable(std::string variableName, IVariableLocationGetter* assignValueLocation)
{
    //TODO: Assign variable
    return nullptr;
}*/

Function* CodeGenerator::AddVoidFunction(std::string name /*TODO: Add parameters*/)
{
    return AddFunction(name, nullptr);
}

Function* CodeGenerator::AddFunction(std::string name, std::string returnTypeIdentifier)
{
    Type* returnType = GetCurrentEnvironment()->GetType(returnTypeIdentifier);

    return AddFunction(name, returnType);
}

Function* CodeGenerator::AddFunction(std::string name, Type* returnType /*TODO: Add parameters*/)
{
     // TODO: Construct parameters from type and name; requires locationGetter and locationSetter
    Function* function = new Function(returnType); // TODO: Add parameters

    GetCurrentEnvironment()->AddFunction(name, function);

    return function;
}

AssemblyCode* CodeGenerator::SetFunctionBody(Function* function, AssemblyCode* body)
{
    return GetCurrentEnvironment()->SetFunctionBody(function, body);
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
    //assemblyCode->AddLines(this->SetVariable("return", nullptr));
    return AssemblyGenerator.GenerateReturnInstruction();
}

AssemblyCode* CodeGenerator::GenerateContinueStatement()
{
    return AssemblyGenerator.GenerateJumpToLabel(GetCurrentEnvironment()->GetJumpLabel("continue"));
}

AssemblyCode* CodeGenerator::GenerateBreakStatement()
{
    return AssemblyGenerator.GenerateJumpToLabel(GetCurrentEnvironment()->GetJumpLabel("break"));
}

void CodeGenerator::InitLoopEnvironment()
{
    environmentLinkedList.PushEnvironment(std::make_shared<FunctionScopeEnvironment>());
    AddJumpLabel("continue"); // eval label
    AddJumpLabel("break"); // final label
}

AssemblyCode* CodeGenerator::GenerateWhile(AssemblyCode* condition, AssemblyCode* body)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    JumpLabel* continueLabel = GetCurrentEnvironment()->GetJumpLabel("continue");
    JumpLabel* breakLabel = GetCurrentEnvironment()->GetJumpLabel("break");

    assemblyCode->AddLines(AssemblyGenerator.GenerateLabel(continueLabel)); // eval label
    assemblyCode->AddLines(condition); // condition
    
    //TODO: Add jump to break label if condition is false
    assemblyCode->AddLines(body); // body

    assemblyCode->AddLines(AssemblyGenerator.GenerateJumpToLabel(continueLabel));

    assemblyCode->AddLines(AssemblyGenerator.GenerateLabel(breakLabel));

    environmentLinkedList.PopEnvironment();

    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateFor(AssemblyCode* declaration, AssemblyCode* condition, AssemblyCode* increment, AssemblyCode* body)
{
    //TODO: Generate FOR loop
    return nullptr;
} 

AssemblyCode* CodeGenerator::AssignExpressionOutToVariable(std::string variableName)
{
    //TODO: Assign expression output to variable
    return nullptr;
}

AssemblyCode* CodeGenerator::PerformOperation_LVariable_RExpressionOut(std::string variableName, ECodeGeneratorExpressionOperators operation)
{
    Variable* tempVariable = TempVariableStack.top();
    TempVariableStack.pop();

    //TODO: Perform operation

    return nullptr;
}

AssemblyCode* CodeGenerator::PerformOperation_LExpressionOut_RVariableLocation(IVariableLocationGetter* locationGetter, ECodeGeneratorExpressionOperators operation)
{
    //TODO: Perform operation
    return nullptr;
}

std::string CodeGenerator::GetNewJumpLabel()
{
    return "JL" + std::to_string(jumpLabelCounter++);
}

JumpLabel* CodeGenerator::AddJumpLabel(std::string name)
{
    JumpLabel* jumpLabel = new JumpLabel(GetNewJumpLabel());

    GetCurrentEnvironment()->AddJumpLabel(name, jumpLabel);

    return jumpLabel;
}
