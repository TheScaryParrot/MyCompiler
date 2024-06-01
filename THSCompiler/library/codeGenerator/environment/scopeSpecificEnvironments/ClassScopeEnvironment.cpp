#pragma once

#include "ScopeSpecificEnvironment.cpp"

class ClassScopeEnvironment : public ScopeSpecificEnvironment
{
public:
    ClassScopeEnvironment();
    ClassScopeEnvironment(std::shared_ptr<Environment> environment);
};

ClassScopeEnvironment::ClassScopeEnvironment() : ScopeSpecificEnvironment()
{
}

ClassScopeEnvironment::ClassScopeEnvironment(std::shared_ptr<Environment> environment) : ScopeSpecificEnvironment(environment)
{
}