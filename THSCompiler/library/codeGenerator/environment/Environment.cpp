#pragma once

#include <memory>

#include "AbstractEnvironment.cpp"

#include "types/Type.cpp"
#include "variables/Variable.cpp"
#include "functions/Function.cpp"

class Environment
{
public:
    /// @brief Adds the given variable to the current environment with the given identifier
    void AddVariable(std::string identifier, std::shared_ptr<Variable> variable);
    /// @brief Returns a variable that is defined in the current environment
    std::shared_ptr<Variable> GetVariable(std::string identifier);
    /// @brief Returns a variable that is defined in the given type
    std::shared_ptr<Variable> GetVariable(std::shared_ptr<Type> type, std::string identifier);


    /// @brief Adds the given type to the current environment with the given identifier
    void AddType(std::string identifier, std::shared_ptr<Type> type);
    /// @brief Returns a type that is defined in the current environment
    std::shared_ptr<Type> GetType(std::string identifier);
    /// @brief Returns a type that is defined in the given type
    std::shared_ptr<Type> GetType(std::shared_ptr<Type> type, std::string identifier);


    /// @brief Adds the given function to the current environment with the given identifier
    void AddFunction(std::string identifier, std::shared_ptr<Function> function);
    /// @brief Returns a function that is defined in the current environment
    std::shared_ptr<Function> GetFunction(std::string identifier);
    /// @brief Returns a function that is defined in the given type
    std::shared_ptr<Function> GetFunction(std::shared_ptr<Type> type, std::string identifier);


private:
    AbstractEnvironment<Type> types;
    AbstractEnvironment<Variable> variables;
    AbstractEnvironment<Function> functions;

    typedef std::pair<std::shared_ptr<Type>, std::unique_ptr<Environment>> TypeEnvironment;

    /// List of pairs of types and their corresponding environments
    std::vector<TypeEnvironment> typeEnvironments;

};


void Environment::AddVariable(std::string identifier, std::shared_ptr<Variable> variable)
{
    variables.AddElement(identifier, variable);
}

std::shared_ptr<Variable> Environment::GetVariable(std::string identifier)
{
    return variables.GetElement(identifier);
}

std::shared_ptr<Variable> Environment::GetVariable(std::shared_ptr<Type> type, std::string identifier)
{
    for (TypeEnvironment const& typeEnvironment : typeEnvironments)
    {
        if (typeEnvironment.first == type)
        {
            return typeEnvironment.second->GetVariable(identifier);
        }
    }

    return nullptr;
}


void Environment::AddType(std::string identifier, std::shared_ptr<Type> type)
{
    types.AddElement(identifier, type);
}

std::shared_ptr<Type> Environment::GetType(std::string identifier)
{
    return types.GetElement(identifier);
}

std::shared_ptr<Type> Environment::GetType(std::shared_ptr<Type> type, std::string identifier)
{
    for (TypeEnvironment const& typeEnvironment : typeEnvironments)
    {
        if (typeEnvironment.first == type)
        {
            return typeEnvironment.second->GetType(identifier);
        }
    }

    return nullptr;
}


void Environment::AddFunction(std::string identifier, std::shared_ptr<Function> function)
{
    functions.AddElement(identifier, function);
}

std::shared_ptr<Function> Environment::GetFunction(std::string identifier)
{
    return functions.GetElement(identifier);
}

std::shared_ptr<Function> Environment::GetFunction(std::shared_ptr<Type> type, std::string identifier)
{
    for (TypeEnvironment const& typeEnvironment : typeEnvironments)
    {
        if (typeEnvironment.first == type)
        {
            return typeEnvironment.second->GetFunction(identifier);
        }
    }

    return nullptr;
}