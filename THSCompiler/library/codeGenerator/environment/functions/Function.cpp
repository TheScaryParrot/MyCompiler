#pragma once

#include <memory>
#include <vector>

#include "../types/Type.cpp"
#include "../variables/Variable.cpp"
#include "../variables/VariableLocation.cpp"

class Function
{
public:
    Function(Type* returnType);

    Type* GetReturnType();

    //TODO: Implement Call

private:
    Type* returnType;

    Variable* returnVariable;

    std::vector<Variable*> parameters;
};

