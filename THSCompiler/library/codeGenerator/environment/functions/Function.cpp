#pragma once

#include <memory>
#include <vector>

#include "../types/Type.cpp"
#include "../variables/Variable.cpp"
#include "../variables/VariableLocation.cpp"
#include "IFunctionCallCode.cpp"

class Function
{
public:
    Function(Type* returnType);

    /// @brief Sets this function's call code
    /// @param callCode unique pointer to the function call code; the function takes ownership of the pointer
    void SetCallCode(std::unique_ptr<IFunctionCallCode> callCode);
    AssemblyCode* GetFunctionCallCode();

    Type* returnType;

    Variable* returnVariable;

    std::vector<Variable*> parameters;

private:
    std::unique_ptr<IFunctionCallCode> callCode;
};

Function::Function(Type* returnType)
{
    this->returnType = returnType;
}

void Function::SetCallCode(std::unique_ptr<IFunctionCallCode> callCode)
{
    this->callCode = std::unique_ptr<IFunctionCallCode>(callCode.release()); // Take ownership of the pointer
}

AssemblyCode* Function::GetFunctionCallCode()
{
    return callCode->GenerateFunctionCallCode();
}

