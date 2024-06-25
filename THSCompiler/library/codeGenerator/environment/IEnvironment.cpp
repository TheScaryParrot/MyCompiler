#pragma once

#include <memory>
#include <string>

#include "AbstractEnvironment.cpp"
#include "funcVars/functions/Function.cpp"
#include "funcVars/variables/Variable.cpp"
#include "jumpLabels/JumpLabel.cpp"
#include "types/Type.cpp"

class IEnvironment
{
   public:
    /// @brief Adds the given variable to the current environment with the given identifier
    virtual void AddVariable(std::string identifier, Variable* variable) = 0;
    /// @brief Returns a variable that is defined in the current environment
    virtual Variable* GetVariable(std::string identifier) = 0;
    /// @brief Returns true if the given variable is in the current environment
    virtual bool HasVariable(std::string identifier) = 0;
    /// @brief Returns true if the given variable is in the current environment
    virtual bool HasVariable(Variable* variable) = 0;

    /// @brief Adds the given function to the current environment with the given identifier
    virtual void AddFunction(std::string identifier, Function* function) = 0;
    /// @brief Returns a function that is defined in the current environment
    virtual Function* GetFunction(std::string identifier) = 0;
    /// @brief Returns true if the given function is in the current environment
    virtual bool HasFunction(std::string identifier) = 0;
    /// @brief Returns true if the given function is in the current environment
    virtual bool HasFunction(Function* function) = 0;

    /// @brief Adds the given type to the current environment with the given identifier
    virtual void AddType(std::string identifier, std::shared_ptr<Type> type) = 0;
    /// @brief Returns a type that is defined in the current environment
    virtual Type* GetType(std::string identifier) = 0;
    /// @brief Returns true if the given type is in the current environment
    virtual bool HasType(std::string identifier) = 0;
    /// @brief Returns true if the given type is in the current environment
    virtual bool HasType(Type* type) = 0;

    /// @brief Adds the given label to the current environment with the given identifier
    virtual void AddLabel(std::string identifier, JumpLabel* jumpLabel) = 0;
    /// @brief Returns a label that is defined in the current environment
    virtual JumpLabel* GetLabel(std::string identifier) = 0;
    /// @brief Returns true if the given label is in the current environment
    virtual bool HasLabel(std::string identifier) = 0;

    /// @brief Sets the environment of the given type identifier
    /// @param staticEnvironment If true, sets the static environment
    virtual void SetEnvironment(Type* type, std::shared_ptr<IEnvironment> environment, bool staticEnvironment) = 0;
    /// @brief Returns the environment of the given type identifier
    /// @param staticEnvironment If true, returns the static environment
    virtual IEnvironment* GetEnvironment(std::string typeIdentifier, bool staticEnvironment) = 0;
    /// @brief Returns the environment of the given type
    /// @param staticEnvironment If true, returns the static environment
    virtual IEnvironment* GetEnvironment(Type* type, bool staticEnvironment) = 0;
};