#pragma once

#include <iostream>
#include <memory>

#include "AbstractEnvironment.cpp"
#include "IEnvironment.cpp"
#include "funcVars/functions/Function.cpp"
#include "funcVars/variables/Variable.cpp"
#include "jumpLabels/JumpLabel.cpp"
#include "types/Type.cpp"

class Environment : IEnvironment
{
   public:
    /// @brief Adds the given variable to the current environment with the given identifier
    virtual void AddVariable(std::string identifier, Variable* variable) override;
    /// @brief Returns a variable that is defined in the current environment
    virtual Variable* GetVariable(std::string identifier) override;
    /// @brief Returns true if the given variable is in the current environment
    virtual bool HasVariable(std::string identifier) override;
    /// @brief Returns true if the given variable is in the current environment
    virtual bool HasVariable(Variable* variable) override;

    /// @brief Adds the given function to the current environment with the given identifier
    virtual void AddFunction(std::string identifier, Function* function) override;
    /// @brief Returns a function that is defined in the current environment
    virtual Function* GetFunction(std::string identifier) override;
    /// @brief Returns true if the given function is in the current environment
    virtual bool HasFunction(std::string identifier) override;
    /// @brief Returns true if the given function is in the current environment
    virtual bool HasFunction(Function* function) override;

    /// @brief Adds the given type to the current environment with the given identifier
    virtual void AddType(std::string identifier, std::shared_ptr<Type> type) override;
    /// @brief Returns a type that is defined in the current environment
    virtual Type* GetType(std::string identifier) override;
    /// @brief Returns true if the given type is in the current environment
    virtual bool HasType(std::string identifier) override;
    /// @brief Returns true if the given type is in the current environment
    virtual bool HasType(Type* type) override;

    /// @brief Adds the given label to the current environment with the given identifier
    virtual void AddLabel(std::string identifier, JumpLabel* jumpLabel) override;
    /// @brief Returns a label that is defined in the current environment
    virtual JumpLabel* GetLabel(std::string identifier) override;
    /// @brief Returns true if the given label is in the current environment
    virtual bool HasLabel(std::string identifier) override;

    /// @brief Sets the environment of the given type identifier
    /// @param staticEnvironment If true, sets the static environment
    virtual void SetEnvironment(Type* type, std::shared_ptr<IEnvironment> environment, bool staticEnvironment) override;
    /// @brief Returns the environment of the given type identifier
    /// @param staticEnvironment If true, returns the static environment
    virtual IEnvironment* GetEnvironment(std::string typeIdentifier, bool staticEnvironment) override;
    /// @brief Returns the environment of the given type
    /// @param staticEnvironment If true, returns the static environment
    virtual IEnvironment* GetEnvironment(Type* type, bool staticEnvironment) override;

    typedef struct
    {
       public:
        std::shared_ptr<Type> type;
        std::shared_ptr<IEnvironment> environment;
        std::shared_ptr<IEnvironment> staticEnvironment;
    } TypeEnvironment;

   private:
    AbstractEnvironment<Variable> variables;
    AbstractEnvironment<Function> functions;
    AbstractEnvironment<TypeEnvironment> typeEnvironments;
    AbstractEnvironment<JumpLabel> jumpLabels;

    /// @brief Returns the typeEnvironment of the given type identifier
    TypeEnvironment* GetTypeEnvironment(std::string typeIdentifier);

    /// @brief Returns the typeEnvironment of the given type
    TypeEnvironment* GetTypeEnvironment(Type* type);
};

void Environment::AddVariable(std::string identifier, Variable* variable)
{
    variables.AddElement(identifier, std::unique_ptr<Variable>(variable));
}

Variable* Environment::GetVariable(std::string identifier) { return variables.GetElement(identifier).get(); }

bool Environment::HasVariable(std::string identifier) { return variables.HasElement(identifier); }

bool Environment::HasVariable(Variable* variable) { return variables.HasElement(variable); }

void Environment::AddFunction(std::string identifier, Function* function)
{
    functions.AddElement(identifier, std::unique_ptr<Function>(function));
}

Function* Environment::GetFunction(std::string identifier) { return functions.GetElement(identifier).get(); }

bool Environment::HasFunction(std::string identifier) { return functions.HasElement(identifier); }

bool Environment::HasFunction(Function* function) { return functions.HasElement(function); }

void Environment::AddType(std::string identifier, std::shared_ptr<Type> type)
{
    TypeEnvironment* typeEnvironment = new TypeEnvironment();

    typeEnvironment->type = type;
    typeEnvironment->environment = nullptr;
    typeEnvironment->staticEnvironment = nullptr;

    typeEnvironments.AddElement(identifier, std::shared_ptr<TypeEnvironment>(typeEnvironment));
}

Type* Environment::GetType(std::string identifier) { return GetTypeEnvironment(identifier)->type.get(); }

bool Environment::HasType(std::string identifier) { return typeEnvironments.HasElement(identifier); }

bool Environment::HasType(Type* type) { return GetTypeEnvironment(type)->type.get() == type; }

void Environment::AddLabel(std::string identifier, JumpLabel* jumpLabel)
{
    jumpLabels.AddElement(identifier, std::unique_ptr<JumpLabel>(jumpLabel));
}

JumpLabel* Environment::GetLabel(std::string identifier) { return jumpLabels.GetElement(identifier).get(); }

bool Environment::HasLabel(std::string identifier) { return jumpLabels.HasElement(identifier); }

void Environment::SetEnvironment(Type* type, std::shared_ptr<IEnvironment> environment, bool staticEnvironment)
{
    if (staticEnvironment)
        GetTypeEnvironment(type)->staticEnvironment = environment;
    else
        GetTypeEnvironment(type)->environment = environment;
}

IEnvironment* Environment::GetEnvironment(std::string typeIdentifier, bool staticEnvironment)
{
    if (staticEnvironment) return GetTypeEnvironment(typeIdentifier)->staticEnvironment.get();

    return GetTypeEnvironment(typeIdentifier)->environment.get();
}

IEnvironment* Environment::GetEnvironment(Type* type, bool staticEnvironment)
{
    if (staticEnvironment) return GetTypeEnvironment(type)->staticEnvironment.get();

    return GetTypeEnvironment(type)->environment.get();
}

Environment::TypeEnvironment* Environment::GetTypeEnvironment(std::string typeIdentifier)
{
    // Finds the TypeEnvironment in the list of typeEnvironments that has the given type identifier
    return typeEnvironments.GetElement(typeIdentifier).get();
}

Environment::TypeEnvironment* Environment::GetTypeEnvironment(Type* type)
{
    // Finds the TypeEnvironment in the list of typeEnvironments that has the given type
    return typeEnvironments
        .FindElement([type](std::shared_ptr<EnvironmentElement<TypeEnvironment>> typeEnvironment) -> bool
                     { return typeEnvironment->GetElement()->type.get() == type; })
        .get();
}