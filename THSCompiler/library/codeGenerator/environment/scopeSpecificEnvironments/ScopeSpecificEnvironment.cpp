#pragma once

#include <memory>

#include "../Environment.cpp"

#include "IScopeSpecificEnvironment.cpp"


class ScopeSpecificEnvironment : IScopeSpecificEnvironment
{
public:
    ScopeSpecificEnvironment(std::shared_ptr<Environment> environment);

    virtual void AddVariable(std::string identifer, Variable* variable) override;

    virtual VariableLocation GetVariableLocation(std::string identifier) override;

    virtual void AddFunction(std::string identifier, Function* function) override;
    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) override;

    virtual AssemblyCode* GenerateFunctionCall(Function* function, std::vector<Variable*> arguments) override;

    /// @brief Gets the identifier of the function; depends on function name and parameters (function name mangling)
    virtual std::string GetFunctionIdentifier(std::string functionName, std::vector<std::shared_ptr<Type>> parameterTypes);

    virtual Type* GetType(std::string identifier) override;

    virtual bool HasVariable(std::string identifier) override;
    virtual bool HasVariable(Variable* variable) override;

    virtual bool HasFunction(std::string identifier) override;
    virtual bool HasFunction(Function* function) override;

    virtual bool HasTypeEnvironment(std::shared_ptr<Type> type) override;
    

private:
    /// @brief The environment that holds variables, functions and types (types with their own environment)
    std::shared_ptr<Environment> environment;
};

ScopeSpecificEnvironment::ScopeSpecificEnvironment(std::shared_ptr<Environment> environment)
{
    this->environment = environment;
}

void ScopeSpecificEnvironment::AddVariable(std::string identifer, Variable* variable)
{
    this->environment->AddVariable(identifer, variable);
}

VariableLocation ScopeSpecificEnvironment::GetVariableLocation(std::string identifier)
{
    //TODO: Add basic behaviour
    return VariableLocation();
}

void ScopeSpecificEnvironment::AddFunction(std::string identifier, Function* function)
{
    this->environment->AddFunction(identifier, function);
}

AssemblyCode* ScopeSpecificEnvironment::SetFunctionBody(Function* function, AssemblyCode* body)
{
    //TODO: Add basic behaviour
    return nullptr;
}

AssemblyCode* ScopeSpecificEnvironment::GenerateFunctionCall(Function* function, std::vector<Variable*> arguments)
{
    //TODO: Add basic behaviour
    return nullptr;
}

std::string ScopeSpecificEnvironment::GetFunctionIdentifier(std::string functionName, std::vector<std::shared_ptr<Type>> parameterTypes)
{
    //TODO: Do proper function name mangling
    std::string result = functionName + "_";

    for (std::shared_ptr<Type> type : parameterTypes)
    {
        result += type->ToString() + "_";
    }

    return result;
}

Type* ScopeSpecificEnvironment::GetType(std::string identifier)
{
    return environment->GetType(identifier);
}

bool ScopeSpecificEnvironment::HasVariable(std::string identifier)
{
    return environment->HasVariable(identifier);
}

bool ScopeSpecificEnvironment::HasFunction(std::string identifier)
{
    return environment->HasFunction(identifier);
}

bool ScopeSpecificEnvironment::HasFunction(Function* function)
{
    return environment->HasFunction(function);
}

bool ScopeSpecificEnvironment::HasTypeEnvironment(std::shared_ptr<Type> type)
{
    return environment->GetEnvironment(type) != nullptr;
}