#pragma once

#include "../../../assembly/AssemblyCode.cpp"

#include "../variables/Variable.cpp"
#include "../functions/Function.cpp"
#include "../types/Type.cpp"
#include "../jumpLabels/JumpLabel.cpp"

class IScopeSpecificEnvironment
{
public:
    #pragma region Variables
    
    virtual void AddVariable(std::string identifier, Variable* variable) = 0;

    virtual bool HasVariable(std::string identifier) = 0;
    virtual bool HasVariable(Variable* variable) = 0;

    #pragma endregion

    #pragma region Functions

    virtual void AddFunction(std::string identifier, Function* function) = 0;

    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) = 0;

    virtual AssemblyCode* GenerateFunctionCall(Function* function, std::vector<Variable*> arguments) = 0;

    virtual bool HasFunction(std::string identifier) = 0;
    virtual bool HasFunction(Function* function) = 0;

    #pragma endregion

    #pragma region Types
    
    virtual void AddType(std::string identifier, Type* type) = 0;
    virtual Type* GetType(std::string identifier) = 0;
    virtual bool HasType(std::string identifier) = 0;
    virtual bool HasType(Type* type) = 0;

    virtual void SetTypeEnvironment(Type* type, IScopeSpecificEnvironment* environment) = 0;
    virtual bool HasTypeEnvironment(Type* type) = 0;

    #pragma endregion

    #pragma region JumpLabels

    virtual void AddJumpLabel(std::string identifier, JumpLabel* jumpLabel) = 0;

    virtual JumpLabel* GetJumpLabel(std::string identifier) = 0;

    virtual bool HasJumpLabel(std::string identifier) = 0;
    
    #pragma endregion
    
};