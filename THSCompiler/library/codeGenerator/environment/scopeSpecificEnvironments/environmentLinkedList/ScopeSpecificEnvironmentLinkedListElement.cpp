#pragma once

#include <iostream>
#include <memory>

#include "../ScopeSpecificEnvironment.cpp"

// inherits from IScopeSpecificEnvironment so that it can be used in the same way as ScopeSpecificEnvironment
class ScopeSpecificEnvironmentLinkedListElement : IScopeSpecificEnvironment
{
   public:
    ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> scopeEnvironment,
                                              std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent);

    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> GetParent();

    virtual void AddVariable(std::string identifier, Variable* variable) override;
    virtual Variable* GetVariable(std::string identifier) override;
    virtual bool HasVariable(std::string identifier) override;
    virtual bool HasVariable(Variable* variable) override;

    virtual void AddFunction(std::string identifier, Function* function) override;
    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) override;
    virtual bool HasFunction(std::string identifier) override;
    virtual bool HasFunction(Function* function) override;

    virtual void AddType(std::string identifier, Type* type) override;
    virtual Type* GetType(std::string identifier) override;
    virtual bool HasType(std::string identifier) override;
    virtual bool HasType(Type* type) override;

    virtual void SetTypeEnvironment(Type* type, IScopeSpecificEnvironment* typeEnvironment) override;
    virtual IScopeSpecificEnvironment* GetTypeEnvironment(Type* type) override;
    virtual bool HasTypeEnvironment(Type* type) override;

    virtual void AddJumpLabel(std::string identifier, JumpLabel* jumpLabel) override;
    virtual JumpLabel* GetJumpLabel(std::string identifier) override;
    virtual bool HasJumpLabel(std::string identifier) override;

   private:
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent;
    std::shared_ptr<ScopeSpecificEnvironment> scopeEnvironment;
};

ScopeSpecificEnvironmentLinkedListElement::ScopeSpecificEnvironmentLinkedListElement(
    std::shared_ptr<ScopeSpecificEnvironment> scopeEnvironment,
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent)
{
    this->scopeEnvironment = scopeEnvironment;
    this->parent = parent;
}

std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> ScopeSpecificEnvironmentLinkedListElement::GetParent()
{
    return parent;
}

#pragma region IScopeSpecificEnvironment implementation

void ScopeSpecificEnvironmentLinkedListElement::AddVariable(std::string identifier, Variable* variable)
{
    return scopeEnvironment->AddVariable(identifier, variable);
}

Variable* ScopeSpecificEnvironmentLinkedListElement::GetVariable(std::string identifier)
{
    if (scopeEnvironment->HasVariable(identifier))
    {
        return scopeEnvironment->GetVariable(identifier);
    }

    if (parent == nullptr)
    {
        std::cerr << "Variable " << identifier << " not found in environment\n";
        return nullptr;
    }

    return parent->GetVariable(identifier);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasVariable(std::string identifier)
{
    if (scopeEnvironment->HasVariable(identifier))
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
    if (scopeEnvironment->HasVariable(variable))
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
    scopeEnvironment->AddFunction(identifier, function);
}

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::SetFunctionBody(Function* function, AssemblyCode* body)
{
    return scopeEnvironment->SetFunctionBody(function, body);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasFunction(std::string identifier)
{
    if (scopeEnvironment->HasFunction(identifier))
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
    if (scopeEnvironment->HasFunction(function))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasFunction(function);
}

/*AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::GenerateFunctionCall(Function* function,
std::vector<Variable*> arguments)
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
    scopeEnvironment->AddType(identifier, type);
}

Type* ScopeSpecificEnvironmentLinkedListElement::GetType(std::string identifier)
{
    if (scopeEnvironment->HasType(identifier))
    {
        return scopeEnvironment->GetType(identifier);
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
    if (scopeEnvironment->HasType(identifier))
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
    if (scopeEnvironment->HasType(type))
    {
        return true;
    }

    if (parent == nullptr)
    {
        return false;
    }

    return parent->HasType(type);
}

void ScopeSpecificEnvironmentLinkedListElement::SetTypeEnvironment(Type* type,
                                                                   IScopeSpecificEnvironment* typeEnvironment)
{
    if (this->scopeEnvironment->HasType(type))
    {
        this->scopeEnvironment->SetTypeEnvironment(type, typeEnvironment);
        return;
    }

    if (parent == nullptr)
    {
        std::cerr << "Type " << type->ToString() << " not found in environment, can't add environment\n";
        return;
    }

    parent->SetTypeEnvironment(type, typeEnvironment);
}

IScopeSpecificEnvironment* ScopeSpecificEnvironmentLinkedListElement::GetTypeEnvironment(Type* type)
{
    if (scopeEnvironment->HasType(type))
    {
        return scopeEnvironment->GetTypeEnvironment(type);
    }

    if (parent == nullptr)
    {
        std::cerr << "Type " << type->ToString() << " not found in environment\n";
        return nullptr;
    }

    return parent->GetTypeEnvironment(type);
}

bool ScopeSpecificEnvironmentLinkedListElement::HasTypeEnvironment(Type* type)
{
    if (scopeEnvironment->HasType(type))
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
    scopeEnvironment->AddJumpLabel(identifier, jumpLabel);
}

JumpLabel* ScopeSpecificEnvironmentLinkedListElement::GetJumpLabel(std::string identifier)
{
    if (scopeEnvironment->HasJumpLabel(identifier))
    {
        return scopeEnvironment->GetJumpLabel(identifier);
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
    if (scopeEnvironment->HasJumpLabel(identifier))
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
