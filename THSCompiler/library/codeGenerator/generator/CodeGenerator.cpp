#pragma once

#include <memory>

#include "../environment/scopeSpecificEnvironments/environmentLinkedList/ScopeSpecificEnvironmentLinkedList.cpp"
#include "../environment/scopeSpecificEnvironments/GlobalScopeEnvironment.cpp"

#include "../../assembly/AssemblyCode.cpp"

class CodeGenerator
{
public:
    CodeGenerator();

    Variable* AddVariable(std::string name, std::string typeIdentifier);
    AssemblyCode* SetVariable(std::string name, IVariableLocationGetter* valueLocation);

    Function* AddFunction(std::string name, std::string returnTypeIdentifier /*TODO: Add parameters*/);
    AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body);

private:
    ScopeSpecificEnvironmentLinkedList environmentLinkedList;

    ScopeSpecificEnvironmentLinkedListElement* GetCurrentEnvironment();
};

CodeGenerator::CodeGenerator()
{
    environmentLinkedList = ScopeSpecificEnvironmentLinkedList();
    environmentLinkedList.PushEnvironment(std::make_shared<GlobalScopeEnvironment>(new Environment()));
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
