#pragma once

#include <memory>
#include <vector>

#include "../types/Type.cpp"
#include "../variables/Variable.cpp"
#include "../variables/VariableLocation.cpp"

class Function
{
public:
    Function(std::shared_ptr<Type> returnType);

    std::shared_ptr<Type> GetReturnType();

    //TODO: Implement Call

private:
    std::shared_ptr<Type> returnType;

    std::shared_ptr<Variable> returnVariable;

    std::vector<std::shared_ptr<Variable>> parameters;
};

