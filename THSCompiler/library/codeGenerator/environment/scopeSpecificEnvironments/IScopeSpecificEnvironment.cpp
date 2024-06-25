#pragma once

#include "../../../assembly/AssemblyCode.cpp"
#include "../funcVars/functions/Function.cpp"
#include "../funcVars/variables/Variable.cpp"
#include "../jumpLabels/JumpLabel.cpp"
#include "../types/Type.cpp"

class IScopeSpecificEnvironment
{
   public:
#pragma region Variables

    virtual void AddVariable(std::string identifier, Variable* variable) = 0;

    virtual Variable* GetVariable(std::string identifier) = 0;

    virtual bool HasVariable(std::string identifier) = 0;
    virtual bool HasVariable(Variable* variable) = 0;

#pragma endregion

#pragma region Functions

    virtual void AddFunction(std::string identifier, Function* function) = 0;

    /// @brief Generates body of a function and updates the functions FunctionCallCode
    /// @param function Function to set the body
    /// @param body The AssemblyCode that represents the body of the function
    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) = 0;

    virtual bool HasFunction(std::string identifier) = 0;
    virtual bool HasFunction(Function* function) = 0;

#pragma endregion

#pragma region Types

    virtual void AddType(std::string identifier, Type* type) = 0;
    virtual Type* GetType(std::string identifier) = 0;
    virtual bool HasType(std::string identifier) = 0;
    virtual bool HasType(Type* type) = 0;

    virtual void SetTypeEnvironment(Type* type, IScopeSpecificEnvironment* environment, bool staticEnvironment) = 0;
    virtual IScopeSpecificEnvironment* GetTypeEnvironment(Type* type, bool staticEnvironment) = 0;
    virtual bool HasTypeEnvironment(Type* type, bool staticEnvironment) = 0;

#pragma endregion

#pragma region JumpLabels

    virtual void AddJumpLabel(std::string identifier, JumpLabel* jumpLabel) = 0;

    virtual JumpLabel* GetJumpLabel(std::string identifier) = 0;

    virtual bool HasJumpLabel(std::string identifier) = 0;

#pragma endregion
};