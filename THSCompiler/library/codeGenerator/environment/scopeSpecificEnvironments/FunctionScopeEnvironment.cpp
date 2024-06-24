#pragma once

#include "ScopeSpecificEnvironment.cpp"

class FunctionScopeEnvironment : public ScopeSpecificEnvironment
{
   public:
    FunctionScopeEnvironment();
    FunctionScopeEnvironment(std::shared_ptr<Environment> environment);
};

FunctionScopeEnvironment::FunctionScopeEnvironment() : ScopeSpecificEnvironment() {}

FunctionScopeEnvironment::FunctionScopeEnvironment(std::shared_ptr<Environment> environment)
    : ScopeSpecificEnvironment(environment)
{
}