#pragma once

#include <memory>

#include "AbstractEnvironment.cpp"

#include "types/Type.cpp"
#include "variables/Variable.cpp"
#include "functions/Function.cpp"
#include "jumpLabels/JumpLabel.cpp"

class Environment
{
public:
    /// @brief Adds the given variable to the current environment with the given identifier
    void AddVariable(std::string identifier, Variable* variable);
    /// @brief Returns a variable that is defined in the current environment
    std::shared_ptr<Variable> GetVariable(std::string identifier);
    /// @brief Returns true if the given variable is in the current environment
    bool HasVariable(std::string identifier)
    {
        return variables.HasElement(identifier);
    }
    /// @brief Returns true if the given variable is in the current environment
    bool HasVariable(Variable* variable)
    {
        return variables.HasElement(variable);
    }



    /// @brief Adds the given function to the current environment with the given identifier
    void AddFunction(std::string identifier, Function* function);
    /// @brief Returns a function that is defined in the current environment
    std::shared_ptr<Function> GetFunction(std::string identifier);
    /// @brief Returns true if the given function is in the current environment
    bool HasFunction(std::string identifier)
    {
        return functions.HasElement(identifier);
    }
    /// @brief Returns true if the given function is in the current environment
    bool HasFunction(Function* function)
    {
        return functions.HasElement(function);
    }


    /// @brief Adds the given type to the current environment with the given identifier
    void AddType(std::string identifier, std::shared_ptr<Type> type, std::shared_ptr<Environment> environment);
    /// @brief Returns a type that is defined in the current environment
    Type* GetType(std::string identifier);
    /// @brief Returns true if the given type is in the current environment
    bool HasType(std::string identifier)
    {
        return typeEnvironments.HasElement(identifier);
    }
    /// @brief Returns true if the given type is in the current environment
    bool HasType(std::shared_ptr<Type> type)
    {
        return typeEnvironments.FindElement([type](std::shared_ptr<EnvironmentElement<TypeEnvironment>> typeEnvironment) -> bool
        {
            return typeEnvironment->GetElement()->first == type;
        }) != nullptr;
    }

    /// @brief Adds the given label to the current environment with the given identifier
    void AddLabel(std::string identifier, JumpLabel* jumpLabel)
    {
        jumpLabels.AddElement(identifier, std::unique_ptr<JumpLabel>(jumpLabel));
    }
    /// @brief Returns a label that is defined in the current environment
    JumpLabel* GetLabel(std::string identifier)
    {
        return jumpLabels.GetElement(identifier).get();
    }
    /// @brief Returns true if the given label is in the current environment
    bool HasLabel(std::string identifier)
    {
        return jumpLabels.HasElement(identifier);
    }

    /// @brief Returns the environment of the given type identifier
    std::shared_ptr<Environment> GetEnvironment(std::string typeIdentifier);
    /// @brief Returns the environment of the given type
    std::shared_ptr<Environment> GetEnvironment(std::shared_ptr<Type> type);


private:
    typedef std::pair<std::shared_ptr<Type>, std::shared_ptr<Environment>> TypeEnvironment;

    AbstractEnvironment<Variable> variables;
    AbstractEnvironment<Function> functions;
    AbstractEnvironment<TypeEnvironment> typeEnvironments;
    AbstractEnvironment<JumpLabel> jumpLabels;

    /// @brief Returns the typeEnvironment of the given type identifier
    std::shared_ptr<TypeEnvironment> GetTypeEnvironment(std::string typeIdentifier);

    /// @brief Returns the typeEnvironment of the given type
    std::shared_ptr<TypeEnvironment> GetTypeEnvironment(std::shared_ptr<Type> type);

    /// @brief Returns the type stored in the given typeEnvironment
    Type* GetType(std::shared_ptr<TypeEnvironment> typeEnvironment);

    /// @brief Returns the environment stored in the given typeEnvironment
    std::shared_ptr<Environment> GetEnvironment(std::shared_ptr<TypeEnvironment> typeEnvironment);
};


void Environment::AddVariable(std::string identifier, Variable* variable)
{
    variables.AddElement(identifier, std::unique_ptr<Variable>(variable));
}

std::shared_ptr<Variable> Environment::GetVariable(std::string identifier)
{
    return variables.GetElement(identifier);
}


void Environment::AddFunction(std::string identifier, Function* function)
{
    functions.AddElement(identifier, std::unique_ptr<Function>(function));
}

std::shared_ptr<Function> Environment::GetFunction(std::string identifier)
{
    return functions.GetElement(identifier);
}


void Environment::AddType(std::string identifier, std::shared_ptr<Type> type, std::shared_ptr<Environment> environment)
{
    typeEnvironments.AddElement(identifier, std::make_shared<TypeEnvironment>(type, environment));
}

Type* Environment::GetType(std::string identifier)
{
    return GetType(GetTypeEnvironment(identifier));
}


std::shared_ptr<Environment> Environment::GetEnvironment(std::string typeIdentifier)
{
    return GetEnvironment(GetTypeEnvironment(typeIdentifier));
}

std::shared_ptr<Environment> Environment::GetEnvironment(std::shared_ptr<Type> type)
{
    return GetEnvironment(GetTypeEnvironment(type));
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

Type* Environment::GetType(std::shared_ptr<TypeEnvironment> typeEnvironment)
{
    return typeEnvironment->first.get();
}

std::shared_ptr<Environment> Environment::GetEnvironment(std::shared_ptr<TypeEnvironment> typeEnvironment)
{
    return typeEnvironment->second;
}
