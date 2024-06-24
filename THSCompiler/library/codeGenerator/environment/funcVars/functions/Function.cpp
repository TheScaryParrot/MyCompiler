#pragma once

#include <memory>
#include <vector>

#include "../../types/Type.cpp"
#include "../DeclarationAttributes.cpp"
#include "../variables/Variable.cpp"
#include "../variables/VariableLocation.cpp"
#include "IFunctionCallCode.cpp"

class Function
{
   public:
    Function(std::string label, Variable* returnVariable, DeclarationAttributes attributes);

    /// @brief Sets this function's call code
    /// @param callCode unique pointer to the function call code; the function takes ownership of the pointer
    void SetCallCode(std::unique_ptr<IFunctionCallCode> callCode);
    bool HasFunctionCallCode();
    AssemblyCode* GetFunctionCallCode();

    std::string label;
    Variable* returnVariable;

    std::vector<Variable*> parameters;

    EScopes GetScope();
    bool IsFinal();
    bool IsInline();

   private:
    std::unique_ptr<IFunctionCallCode> callCode = nullptr;
    DeclarationAttributes attributes;
};

Function::Function(std::string label, Variable* returnVariable, DeclarationAttributes attributes)
{
    this->label = label;
    this->returnVariable = returnVariable;
    this->attributes = attributes;
}

void Function::SetCallCode(std::unique_ptr<IFunctionCallCode> callCode)
{
    this->callCode = std::unique_ptr<IFunctionCallCode>(callCode.release());  // Take ownership of the pointer
}

bool Function::HasFunctionCallCode() { return callCode != nullptr; }

AssemblyCode* Function::GetFunctionCallCode()
{
    if (!HasFunctionCallCode())
    {
        std::cerr << "Function call code not set for function " << label << std::endl;
    }

    return callCode->GenerateFunctionCallCode();
}

EScopes Function::GetScope() { return attributes.scope; }

bool Function::IsFinal() { return attributes.isFinal; }

bool Function::IsInline() { return attributes.isInline; }
