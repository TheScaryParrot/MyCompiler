#pragma once

#include <memory>

#include "../environment/scopeSpecificEnvironments/environmentLinkedList/ScopeSpecificEnvironmentLinkedList.cpp"
#include "../environment/scopeSpecificEnvironments/GlobalScopeEnvironment.cpp"
#include "../environment/scopeSpecificEnvironments/FunctionScopeEnvironment.cpp"

#include "../../assembly/AssemblyCode.cpp"
#include "../../assembly/AssemblyLabelLine.cpp"

class CodeGenerator
{
public:
    CodeGenerator();

    Variable* AddVariable(std::string name, std::string typeIdentifier);
    AssemblyCode* SetVariable(std::string name, IVariableLocationGetter* valueLocation);

    Function* AddFunction(std::string name, std::string returnTypeIdentifier /*TODO: Add parameters*/);
    AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body);

    void InitWhileEnvironment();
    AssemblyCode* GenerateWhile(AssemblyCode* condition, AssemblyCode* body);

private:
    ScopeSpecificEnvironmentLinkedList environmentLinkedList;

    ScopeSpecificEnvironmentLinkedListElement* GetCurrentEnvironment();

    unsigned int jumpLabelCounter = 0;

    std::string GetNewJumpLabel();
    JumpLabel* AddJumpLabel(std::string name);

    AssemblyCode* GenerateLabel(JumpLabel* jumpLabel);
};

CodeGenerator::CodeGenerator()
{
    environmentLinkedList = ScopeSpecificEnvironmentLinkedList();
    environmentLinkedList.PushEnvironment(std::make_shared<GlobalScopeEnvironment>());
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

AssemblyCode* CodeGenerator::SetVariable(std::string name, IVariableLocationGetter* valueLocation)
{
    //TODO: Assign variable
    return nullptr;
}

Function* CodeGenerator::AddFunction(std::string name, std::string returnTypeIdentifier)
{
    Type* returnType = GetCurrentEnvironment()->GetType(returnTypeIdentifier);

    // TODO: Construct parameters from type and name; requires locationGetter and locationSetter
    Function* function = new Function(returnType); // TODO: Add parameters

    GetCurrentEnvironment()->AddFunction(name, function);
}

AssemblyCode* CodeGenerator::SetFunctionBody(Function* function, AssemblyCode* body)
{
    //TODO: Set function body
    return nullptr;
}

void CodeGenerator::InitWhileEnvironment()
{
    environmentLinkedList.PushEnvironment(std::make_shared<FunctionScopeEnvironment>());
    AddJumpLabel("continue"); // eval label
    AddJumpLabel("break"); // final label
}

AssemblyCode* CodeGenerator::GenerateWhile(AssemblyCode* condition, AssemblyCode* body)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    assemblyCode->AddLines(GenerateLabel(GetCurrentEnvironment()->GetJumpLabel("continue"))); // eval label
    assemblyCode->AddLines(condition); // condition
    
    //TODO: Add jump to break label if condition is false
    assemblyCode->AddLines(body); // body

    //TODO: Add jump to continue label

    assemblyCode->AddLines(GenerateLabel(GetCurrentEnvironment()->GetJumpLabel("break")));

    environmentLinkedList.PopEnvironment();

    return assemblyCode;
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

AssemblyCode* CodeGenerator::GenerateLabel(JumpLabel* jumpLabel)
{
    AssemblyCode* assemblyCode = new AssemblyCode();
    assemblyCode->AddLine(std::make_shared<AssemblyLabelLine>(jumpLabel->GetName()));
};
