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
    /// @brief Returns a variable that is defined in the given type identifier
    std::shared_ptr<Variable> GetVariable(std::string typeIdentifier, std::string identifier);
    /// @brief Returns a variable that is defined in the given type
    std::shared_ptr<Variable> GetVariable(std::shared_ptr<Type> type, std::string identifier);


    /// @brief Adds the given function to the current environment with the given identifier
    void AddFunction(std::string identifier, std::shared_ptr<Function> function);
    /// @brief Returns a function that is defined in the current environment
    std::shared_ptr<Function> GetFunction(std::string identifier);
    /// @brief Returns a function that is defined in the given type identifier
    std::shared_ptr<Function> GetFunction(std::string typeIdentifier, std::string identifier);
    /// @brief Returns a function that is defined in the given type
    std::shared_ptr<Function> GetFunction(std::shared_ptr<Type> type, std::string identifier);


    /// @brief Adds the given type to the current environment with the given identifier
    void AddType(std::string identifier, std::shared_ptr<Type> type, std::shared_ptr<Environment> environment);
    /// @brief Returns a type that is defined in the current environment
    std::shared_ptr<Type> GetType(std::string identifier);
    /// @brief Returns a type that is defined in the given type identifier
    std::shared_ptr<Type> GetType(std::string typeIdentifier, std::string identifier);
    /// @brief Returns a type that is defined in the given type
    std::shared_ptr<Type> GetType(std::shared_ptr<Type> type, std::string identifier);


private:
    typedef std::pair<std::shared_ptr<Type>, std::shared_ptr<Environment>> TypeEnvironment;

    AbstractEnvironment<Variable> variables;
    AbstractEnvironment<Function> functions;
    AbstractEnvironment<TypeEnvironment> typeEnvironments;

    /// @brief Returns the typeEnvironment of the given type identifier
    std::shared_ptr<TypeEnvironment> GetTypeEnvironment(std::string typeIdentifier);

    /// @brief Returns the typeEnvironment of the given type
    std::shared_ptr<TypeEnvironment> GetTypeEnvironment(std::shared_ptr<Type> type);

    /// @brief Returns the type stored in the given typeEnvironment
    std::shared_ptr<Type> GetType(std::shared_ptr<TypeEnvironment> typeEnvironment);

    /// @brief Returns the environment stored in the given typeEnvironment
    std::shared_ptr<Environment> GetEnvironment(std::shared_ptr<TypeEnvironment> typeEnvironment);
};


void Environment::AddVariable(std::string identifier, std::shared_ptr<Variable> variable)
{
    variables.AddElement(identifier, variable);
}

std::shared_ptr<Variable> Environment::GetVariable(std::string identifier)
{
    return variables.GetElement(identifier);
}

std::shared_ptr<Variable> Environment::GetVariable(std::string typeIdentifier, std::string identifier)
{
    return GetEnvironment(GetTypeEnvironment(typeIdentifier))->GetVariable(identifier);
}

std::shared_ptr<Variable> Environment::GetVariable(std::shared_ptr<Type> type, std::string identifier)
{
    return GetEnvironment(GetTypeEnvironment(type))->GetVariable(identifier);
}


void Environment::AddFunction(std::string identifier, std::shared_ptr<Function> function)
{
    functions.AddElement(identifier, function);
}

std::shared_ptr<Function> Environment::GetFunction(std::string identifier)
{
    return functions.GetElement(identifier);
}

std::shared_ptr<Function> Environment::GetFunction(std::string typeIdentifier, std::string identifier)
{
    return GetEnvironment(GetTypeEnvironment(typeIdentifier))->GetFunction(identifier);
}

std::shared_ptr<Function> Environment::GetFunction(std::shared_ptr<Type> type, std::string identifier)
{
    return GetEnvironment(GetTypeEnvironment(type))->GetFunction(identifier);
}


void Environment::AddType(std::string identifier, std::shared_ptr<Type> type, std::shared_ptr<Environment> environment)
{
    typeEnvironments.AddElement(identifier, std::make_shared<TypeEnvironment>(type, environment));
}

std::shared_ptr<Type> Environment::GetType(std::string identifier)
{
    return GetType(GetTypeEnvironment(identifier));
}

std::shared_ptr<Type> Environment::GetType(std::string typeIdentifier, std::string identifier)
{
    return GetEnvironment(GetTypeEnvironment(typeIdentifier))->GetType(identifier);
}

std::shared_ptr<Type> Environment::GetType(std::shared_ptr<Type> type, std::string identifier)
{
    return GetEnvironment(GetTypeEnvironment(type))->GetType(identifier);
}


std::shared_ptr<Environment::TypeEnvironment> Environment::GetTypeEnvironment(std::string typeIdentifier)
{
    // Finds the TypeEnvironment in the list of typeEnvironments that has the given type identifier
    return typeEnvironments.GetElement(typeIdentifier);
}

std::shared_ptr<Environment::TypeEnvironment> Environment::GetTypeEnvironment(std::shared_ptr<Type> type)
{
    // Finds the TypeEnvironment in the list of typeEnvironments that has the given type
    return typeEnvironments.FindElement([type](std::shared_ptr<EnvironmentElement<TypeEnvironment>> typeEnvironment) -> bool
    {
        return typeEnvironment->GetElement()->first == type;
    });
}

std::shared_ptr<Type> Environment::GetType(std::shared_ptr<TypeEnvironment> typeEnvironment)
{
    return typeEnvironment->first;
}

std::shared_ptr<Environment> Environment::GetEnvironment(std::shared_ptr<TypeEnvironment> typeEnvironment)
{
    return typeEnvironment->second;
}
