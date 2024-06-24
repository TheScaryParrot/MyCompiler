#pragma once

#include <memory>

#include "../types/Type.cpp"
#include "variableLocationGetters/IVariableLocationGetter.cpp"

class Variable
{
   public:
    Variable(Type* type);
    Variable(Type* type, IVariableLocationGetter* locationGetter, IVariableLocationGetter* setLocation);

    Type* GetType();

    VariableLocation GetLocation(VariableLocation parentLocation);
    VariableLocation SetLocation(VariableLocation parentLocation);

   private:
    Type* type;
    std::unique_ptr<IVariableLocationGetter> getLocation;
    std::unique_ptr<IVariableLocationGetter> setLocation;
};

Variable::Variable(Type* type) { this->type = type; }

Variable::Variable(Type* type, IVariableLocationGetter* locationGetter, IVariableLocationGetter* setLocation)
{
    this->type = type;
    this->getLocation = std::unique_ptr<IVariableLocationGetter>(locationGetter);
    this->setLocation = std::unique_ptr<IVariableLocationGetter>(setLocation);
}

Type* Variable::GetType() { return type; }

VariableLocation Variable::GetLocation(VariableLocation parentLocation)
{
    return this->getLocation->GetLocation(parentLocation);
}

VariableLocation Variable::SetLocation(VariableLocation parentLocation)
{
    return this->setLocation->GetLocation(parentLocation);
}
