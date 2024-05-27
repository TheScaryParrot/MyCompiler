#pragma once

#include <memory>

#include "../types/Type.cpp"
#include "variableLocationGetters/IVariableLocationGetter.cpp"

class Variable
{
public:
    Variable(std::shared_ptr<Type> type, std::shared_ptr<IVariableLocationGetter> locationGetter, std::shared_ptr<IVariableLocationGetter> setLocation);

    std::shared_ptr<Type> GetType();

    VariableLocation GetLocation(VariableLocation parentLocation);
    VariableLocation SetLocation(VariableLocation parentLocation);

private:
    std::shared_ptr<Type> type;
    std::shared_ptr<IVariableLocationGetter> getLocation;
    std::shared_ptr<IVariableLocationGetter> setLocation;
};

Variable::Variable(std::shared_ptr<Type> type, std::shared_ptr<IVariableLocationGetter> getLocation, std::shared_ptr<IVariableLocationGetter> setLocation)
{
    this->type = type;
    this->getLocation = getLocation;
    this->setLocation = setLocation;
}

std::shared_ptr<Type> Variable::GetType()
{
    return type;
}

VariableLocation Variable::GetLocation(VariableLocation parentLocation)
{
    return this->getLocation->GetLocation(parentLocation);
}

VariableLocation Variable::SetLocation(VariableLocation parentLocation)
{
    return this->setLocation->GetLocation(parentLocation);
}
