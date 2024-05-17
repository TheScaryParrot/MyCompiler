#pragma once

#include <memory>

#include "Type.cpp"
#include "variableLocationGetters/IVariableLocationGetter.cpp"

class Variable
{
public:
    Variable(std::shared_ptr<Type> type, std::auto_ptr<IVariableLocationGetter> locationGetter);

    std::shared_ptr<Type> GetType();

    VariableLocation GetLocation(VariableLocation parentLocation);

private:
    std::shared_ptr<Type> type;
    std::auto_ptr<IVariableLocationGetter> locationGetter;
};

Variable::Variable(std::shared_ptr<Type> type, std::auto_ptr<IVariableLocationGetter> locationGetter)
{
    this->type = type;
    this->locationGetter = locationGetter;
}

std::shared_ptr<Type> Variable::GetType()
{
    return type;
}

VariableLocation Variable::GetLocation(VariableLocation parentLocation)
{
    return locationGetter->GetLocation(parentLocation);
}