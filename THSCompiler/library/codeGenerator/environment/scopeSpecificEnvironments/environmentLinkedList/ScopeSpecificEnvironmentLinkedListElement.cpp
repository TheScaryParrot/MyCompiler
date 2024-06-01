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
    virtual bool HasVariable(std::string identifier) override;
    virtual bool HasVariable(Variable* variable) override;

    virtual void AddFunction(std::string identifier, Function* function) override;
    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) override;
    virtual AssemblyCode* GenerateFunctionCall(Function* function, std::vector<Variable*> arguments) override;
    virtual bool HasFunction(std::string identifier)  override;
    virtual bool HasFunction(Function* function) override;

    virtual void AddType(std::string identifier, Type* type) override;
    virtual Type* GetType(std::string identifier) override;
    virtual bool HasType(std::string identifier) override;
    virtual bool HasType(Type* type) override;

    virtual void SetTypeEnvironment(Type* type, IScopeSpecificEnvironment* typeEnvironment) override;
    virtual bool HasTypeEnvironment(Type* type) override;

    virtual void AddJumpLabel(std::string identifier, JumpLabel* jumpLabel) override;
    virtual JumpLabel* GetJumpLabel(std::string identifier) override;
    virtual bool HasJumpLabel(std::string identifier) override;

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

bool ScopeSpecificEnvironmentLinkedListElement::HasVariable(std::string identifier)
{
    if (environment->HasVariable(identifier))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasVariable(identifier);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasVariable(Variable* variable)
{
    if (environment->HasVariable(variable))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasVariable(variable);
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

bool ScopeSpecificEnvironmentLinkedListElement::HasFunction(std::string identifier)
{
    if (environment->HasFunction(identifier))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasFunction(identifier);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasFunction(Function* function)
{
    if (environment->HasFunction(function))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasFunction(function);
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

void ScopeSpecificEnvironmentLinkedListElement::AddType(std::string identifier, Type* type)
{
    environment->AddType(identifier, type);
}

Type* ScopeSpecificEnvironmentLinkedListElement::GetType(std::string identifier)
{
    if (environment->HasType(identifier))
    {
        return environment->GetType(identifier);
    }

    if (parent == nullptr)
    {
        std::cerr << "Type " << identifier << " not found in environment\n";
        return nullptr;
    }

    return parent->GetType(identifier);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasType(std::string identifier)
{
    if (environment->HasType(identifier))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasType(identifier);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasType(Type* type)
{
    if (environment->HasType(type))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasType(type);
}

void ScopeSpecificEnvironmentLinkedListElement::SetTypeEnvironment(Type* type, IScopeSpecificEnvironment* typeEnvironment)
{
    if (this->environment->HasType(type))
    {
        this->environment->SetTypeEnvironment(type, typeEnvironment);
        return;
    }

    if (parent == nullptr)
    {
        std::cerr << "Type " << type->ToString() << " not found in environment, can't add environment\n";
        return;
    }

    parent->SetTypeEnvironment(type, typeEnvironment);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasTypeEnvironment(Type* type)
{
    if (environment->HasType(type))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasTypeEnvironment(type);
}

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

bool ScopeSpecificEnvironmentLinkedListElement::HasJumpLabel(std::string identifier)
{
    if (environment->HasJumpLabel(identifier))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasJumpLabel(identifier);
}

#pragma endregion
