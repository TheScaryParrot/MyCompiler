#pragma once

#include <memory>
#include <iostream>

#include "../ScopeSpecificEnvironment.cpp"

// inherits from IScopeSpecificEnvironment so that it can be used in the same way as ScopeSpecificEnvironment
class ScopeSpecificEnvironmentLinkedListElement : IScopeSpecificEnvironment
{
public:
    ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> environment, std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent);

    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> GetParent();

    #pragma region IScopeSpecificEnvironment implementation

    virtual void AddVariable(std::string identifier, Variable* variable) override;

    //TODO: identifier not past in as string, but as IdentifierNode or something ?
    virtual VariableLocation GetVariableLocation(std::string identifier) override;

    virtual void AddFunction(std::string identifier, Function* function) override;
    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) override;
    virtual AssemblyCode* GenerateFunctionCall(Function* function, std::vector<Variable*> arguments) override;

    virtual Type* GetType(std::string identifier) override;

    #pragma endregion

private:
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent;
    std::shared_ptr<ScopeSpecificEnvironment> environment;
};

ScopeSpecificEnvironmentLinkedListElement::ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> environment, std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent)
{
    this->environment = environment;
    this->parent = parent;
}

std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> ScopeSpecificEnvironmentLinkedListElement::GetParent()
{
    return parent;
}

#pragma region IScopeSpecificEnvironment implementation

void ScopeSpecificEnvironmentLinkedListElement::AddVariable(std::string identifier, Variable* variable)
{
    return environment->AddVariable(identifier, variable);
}

VariableLocation ScopeSpecificEnvironmentLinkedListElement::GetVariableLocation(std::string identifier)
{
    if (environment->HasVariable(identifier))
    {
        return environment->GetVariableLocation(identifier);
    }

    if (parent == nullptr)
    {
        std::cerr << "Variable " << identifier << " not found in environment\n";
        return VariableLocation();
    }
    
    return parent->GetVariableLocation(identifier);
}

void ScopeSpecificEnvironmentLinkedListElement::AddFunction(std::string identifier, Function* function)
{
    environment->AddFunction(identifier, function);
}

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::SetFunctionBody(Function* function, AssemblyCode* body)
{
    return environment->SetFunctionBody(function, body);
}

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::GenerateFunctionCall(Function* function, std::vector<Variable*> arguments)
{
    if (environment->HasFunction(function))
    {
        return environment->GenerateFunctionCall(function, arguments);
    }

    if (parent == nullptr)
    {
        std::cerr << "Function " << function << " not found in environment\n";
        return nullptr;
    }

    return parent->GenerateFunctionCall(function, arguments);
}

#pragma endregion
