#pragma once

#include <memory>

#include "../Environment.cpp"

#include "IScopeSpecificEnvironment.cpp"


class ScopeSpecificEnvironment : IScopeSpecificEnvironment
{
public:
    ScopeSpecificEnvironment(std::shared_ptr<Environment> environment);

    virtual AssemblyCode* GenerateVariableDeclaration(VarDeclarationNode* declaration) override;

    virtual VariableLocation GetVariableLocation(std::string identifier) override;

    virtual AssemblyCode* GenerateFunctionDeclaration(FuncDeclarationNode* declaration) override;

    virtual AssemblyCode* GenerateFunctionCall(CallNode* call) override;

    /// @brief Gets the identifier of the function; depends on function name and parameters (function name mangling)
    virtual std::string GetFunctionIdentifier(std::string functionName, std::vector<std::shared_ptr<Type>> parameterTypes);

    bool HasVariable(std::string identifier);

    bool HasFunction(std::string identifier);

    bool HasTypeEnvironment(std::shared_ptr<Type> type);
    

private:
    /// @brief The environment that holds variables, functions and types (types with their own environment)
    std::shared_ptr<Environment> environment;
};

ScopeSpecificEnvironment::ScopeSpecificEnvironment(std::shared_ptr<Environment> environment)
{
    this->environment = environment;
}

AssemblyCode* ScopeSpecificEnvironment::GenerateVariableDeclaration(VarDeclarationNode* declaration)
{
    //TODO: Add basic behaviour
    return nullptr;
}

VariableLocation ScopeSpecificEnvironment::GetVariableLocation(std::string identifier)
{
    //TODO: Add basic behaviour
    return VariableLocation();
}

AssemblyCode* ScopeSpecificEnvironment::GenerateFunctionDeclaration(FuncDeclarationNode* declaration)
{
    //TODO: Add basic behaviour
    return nullptr;
}

AssemblyCode* ScopeSpecificEnvironment::GenerateFunctionCall(CallNode* call)
{
    //TODO: Add basic behaviour
    return nullptr;
}

std::string ScopeSpecificEnvironment::GetFunctionIdentifier(std::string functionName, std::vector<std::shared_ptr<Type>> parameterTypes)
{
    std::string result = functionName + "_";

    for (std::shared_ptr<Type> type : parameterTypes)
    {
        result += type->ToString() + "_";
    }

    return result;
}

bool ScopeSpecificEnvironment::HasVariable(std::string identifier)
{
    return environment->GetVariable(identifier) != nullptr;
}

bool ScopeSpecificEnvironment::HasFunction(std::string identifier)
{
    return environment->GetFunction(identifier) != nullptr;
}

bool ScopeSpecificEnvironment::HasTypeEnvironment(std::shared_ptr<Type> type)
{
    return environment->GetEnvironment(type) != nullptr;
}