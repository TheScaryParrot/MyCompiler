#pragma once

#include <memory>

#include "../../types/Type.cpp"
#include "../DeclarationAttributes.cpp"
#include "variableLocationGetters/IVariableLocationGetter.cpp"

class Variable
{
   public:
    Variable(Type* type, VarDeclarationAttributes attributes);

    Type* GetType();

    void SetGetLocation(IVariableLocationGetter* locationGetter);
    void SetSetLocation(IVariableLocationGetter* setLocation);

    VariableLocation GetLocation(VariableLocation parentLocation);
    VariableLocation SetLocation(VariableLocation parentLocation);

    EScopes GetScope();
    bool IsFinal();
    bool IsInline();

   private:
    Type* type;
    std::unique_ptr<IVariableLocationGetter> getLocation;
    std::unique_ptr<IVariableLocationGetter> setLocation;
    VarDeclarationAttributes attributes;
};

Variable::Variable(Type* type, VarDeclarationAttributes attributes)
{
    this->type = type;
    this->attributes = attributes;
}

Type* Variable::GetType() { return type; }

void Variable::SetGetLocation(IVariableLocationGetter* locationGetter)
{
    this->getLocation = std::unique_ptr<IVariableLocationGetter>(locationGetter);
}

void Variable::SetSetLocation(IVariableLocationGetter* setLocation) { this->setLocation = std::unique_ptr<IVariableLocationGetter>(setLocation); }

VariableLocation Variable::GetLocation(VariableLocation parentLocation) { return this->getLocation->GetLocation(parentLocation); }

VariableLocation Variable::SetLocation(VariableLocation parentLocation) { return this->setLocation->GetLocation(parentLocation); }

EScopes Variable::GetScope() { return attributes.scope; }

bool Variable::IsFinal() { return attributes.isFinal; }

bool Variable::IsInline() { return attributes.isInline; }