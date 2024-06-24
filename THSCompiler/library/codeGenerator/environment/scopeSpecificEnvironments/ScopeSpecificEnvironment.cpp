#pragma once

#include <memory>

#include "../Environment.cpp"

#include "IScopeSpecificEnvironment.cpp"

class ScopeSpecificEnvironment : public IScopeSpecificEnvironment
{
public:
    ScopeSpecificEnvironment();
    ScopeSpecificEnvironment(std::shared_ptr<Environment> environment);

    virtual void AddVariable(std::string identifer, Variable *variable) override;
    virtual Variable *GetVariable(std::string identifier) override;
    virtual bool HasVariable(std::string identifier) override;
    virtual bool HasVariable(Variable *variable) override;

    virtual void AddFunction(std::string identifier, Function *function) override;
    virtual AssemblyCode *SetFunctionBody(Function *function, AssemblyCode *body) override;
    virtual bool HasFunction(std::string identifier) override;
    virtual bool HasFunction(Function *function) override;

    virtual void AddType(std::string identifier, Type *type) override;
    virtual Type *GetType(std::string identifier) override;
    virtual bool HasType(std::string identifier) override;
    virtual bool HasType(Type *type) override;

    virtual void SetTypeEnvironment(Type *type, IScopeSpecificEnvironment *environment) override;
    virtual IScopeSpecificEnvironment *GetTypeEnvironment(Type *type) override;
    virtual bool HasTypeEnvironment(Type *type) override;

    virtual void AddJumpLabel(std::string identifier, JumpLabel *jumpLabel) override;
    virtual JumpLabel *GetJumpLabel(std::string identifier) override;
    virtual bool HasJumpLabel(std::string identifier) override;

private:
    /// @brief The environment that holds variables, functions and types (types with their own environment)
    std::shared_ptr<Environment> environment;
};

ScopeSpecificEnvironment::ScopeSpecificEnvironment()
{
    this->environment = std::make_shared<Environment>();
}

ScopeSpecificEnvironment::ScopeSpecificEnvironment(std::shared_ptr<Environment> environment)
{
    this->environment = environment;
}

#pragma region Variables

void ScopeSpecificEnvironment::AddVariable(std::string identifer, Variable *variable)
{
    this->environment->AddVariable(identifer, variable);
}

Variable *ScopeSpecificEnvironment::GetVariable(std::string identifier)
{
    return environment->GetVariable(identifier).get();
}

bool ScopeSpecificEnvironment::HasVariable(std::string identifier)
{
    return environment->HasVariable(identifier);
}

bool ScopeSpecificEnvironment::HasVariable(Variable *variable)
{
    return environment->HasVariable(variable);
}

#pragma endregion

#pragma region Functions

void ScopeSpecificEnvironment::AddFunction(std::string identifier, Function *function)
{
    this->environment->AddFunction(identifier, function);
}

AssemblyCode *ScopeSpecificEnvironment::SetFunctionBody(Function *function, AssemblyCode *body)
{
    // TODO: Add basic behaviour
    return nullptr;
}

bool ScopeSpecificEnvironment::HasFunction(std::string identifier)
{
    return environment->HasFunction(identifier);
}

bool ScopeSpecificEnvironment::HasFunction(Function *function)
{
    return environment->HasFunction(function);
}

#pragma endregion

#pragma region Types

void ScopeSpecificEnvironment::AddType(std::string identifier, Type *type)
{
    environment->AddType(identifier, std::shared_ptr<Type>(type));
}

Type *ScopeSpecificEnvironment::GetType(std::string identifier)
{
    return environment->GetType(identifier);
}

bool ScopeSpecificEnvironment::HasType(std::string identifier)
{
    return environment->HasType(identifier);
}

bool ScopeSpecificEnvironment::HasType(Type *type)
{
    return environment->HasType(type);
}

void ScopeSpecificEnvironment::SetTypeEnvironment(Type *type, IScopeSpecificEnvironment *environment)
{
    this->environment->SetEnvironment(type, std::shared_ptr<IScopeSpecificEnvironment>(environment));
}

IScopeSpecificEnvironment *ScopeSpecificEnvironment::GetTypeEnvironment(Type *type)
{
    return environment->GetEnvironment(type).get();
}

bool ScopeSpecificEnvironment::HasTypeEnvironment(Type *type)
{
    return environment->GetEnvironment(type) != nullptr;
}

#pragma endregion

#pragma region JumpLabels

void ScopeSpecificEnvironment::AddJumpLabel(std::string identifier, JumpLabel *jumpLabel)
{
    environment->AddLabel(identifier, jumpLabel);
}

JumpLabel *ScopeSpecificEnvironment::GetJumpLabel(std::string identifier)
{
    return environment->GetLabel(identifier);
}

bool ScopeSpecificEnvironment::HasJumpLabel(std::string identifier)
{
    return environment->HasLabel(identifier);
}

#pragma endregion