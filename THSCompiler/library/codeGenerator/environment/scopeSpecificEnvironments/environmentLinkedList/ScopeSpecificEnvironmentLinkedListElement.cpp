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

    virtual void AddFunction(std::string identifier, Function* function) override;
    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) override;

    virtual Type* GetType(std::string identifier) override;

    virtual void AddJumpLabel(std::string identifier, JumpLabel* jumpLabel) override;
    virtual JumpLabel* GetJumpLabel(std::string identifier) override;

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

void ScopeSpecificEnvironmentLinkedListElement::AddFunction(std::string identifier, Function* function)
{
    environment->AddFunction(identifier, function);
}

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::SetFunctionBody(Function* function, AssemblyCode* body)
{
    return environment->SetFunctionBody(function, body);
}

/*AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::GenerateFunctionCall(Function* function, std::vector<Variable*> arguments)
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
}*/

void ScopeSpecificEnvironmentLinkedListElement::AddJumpLabel(std::string identifier, JumpLabel* jumpLabel)
{
    environment->AddJumpLabel(identifier, jumpLabel);
}

JumpLabel* ScopeSpecificEnvironmentLinkedListElement::GetJumpLabel(std::string identifier)
{
    if (environment->HasJumpLabel(identifier))
    {
        return environment->GetJumpLabel(identifier);
    }

    if (parent == nullptr)
    {
        std::cerr << "Jump label " << identifier << " not found in environment\n";
        return nullptr;
    }

    return parent->GetJumpLabel(identifier);
}

#pragma endregion
