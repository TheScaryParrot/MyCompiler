#pragma once

#include <memory>
#include <vector>

#include "../../types/Type.cpp"
#include "../DeclarationAttributes.cpp"
#include "../variables/Variable.cpp"
#include "../variables/VariableLocation.cpp"
#include "CallInstructionFunctionCallCode.cpp"
#include "IFunctionCallCode.cpp"
#include "InlineFunctionCallCode.cpp"

class Function
{
   public:
    Function(Variable* returnVariable, std::vector<Variable*> parameters, VarDeclarationAttributes attributes);

    /// @brief Sets this function's call code
    /// @param callCode unique pointer to the function call code; the function takes ownership of the pointer
    void SetCallCode(IFunctionCallCode* callCode);
    bool HasFunctionCallCode();
    AssemblyCode* GetFunctionCallCode();

    Variable* returnVariable;

    std::vector<Variable*> parameters;

    EScopes GetScope();
    bool IsFinal();
    bool IsInline();

    static InlineFunctionCallCode* GenerateInlineFunctionCallCode(AssemblyCode* functionBody);
    static CallInstructionFunctionCallCode* GenerateCallInstructionFunctionCallCode(std::string functionLabel);

   private:
    std::unique_ptr<IFunctionCallCode> callCode = nullptr;
    VarDeclarationAttributes attributes;
};

Function::Function(Variable* returnVariable, std::vector<Variable*> parameters, VarDeclarationAttributes attributes)
{
    this->returnVariable = returnVariable;
    this->parameters = parameters;
    this->attributes = attributes;
}

void Function::SetCallCode(IFunctionCallCode* callCode) { this->callCode = std::unique_ptr<IFunctionCallCode>(callCode); }

bool Function::HasFunctionCallCode() { return callCode != nullptr; }

AssemblyCode* Function::GetFunctionCallCode()
{
    if (!HasFunctionCallCode())
    {
        std::cerr << "Function call code not set\n";
        return nullptr;
    }

    return callCode->GenerateFunctionCallCode();
}

EScopes Function::GetScope() { return attributes.scope; }

bool Function::IsFinal() { return attributes.isFinal; }

bool Function::IsInline() { return attributes.isInline; }

InlineFunctionCallCode* Function::GenerateInlineFunctionCallCode(AssemblyCode* functionBody) { return new InlineFunctionCallCode(functionBody); }

CallInstructionFunctionCallCode* Function::GenerateCallInstructionFunctionCallCode(std::string functionLabel)
{
    return new CallInstructionFunctionCallCode(functionLabel);
}
