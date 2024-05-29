#pragma once


#include "ScopeSpecificEnvironment.cpp"


class GlobalScopeEnvironment : public ScopeSpecificEnvironment
{
public:
    GlobalScopeEnvironment();
    GlobalScopeEnvironment(std::shared_ptr<Environment> environment);
};

GlobalScopeEnvironment::GlobalScopeEnvironment() : ScopeSpecificEnvironment()
{
}

GlobalScopeEnvironment::GlobalScopeEnvironment(std::shared_ptr<Environment> environment) : ScopeSpecificEnvironment(environment)
{
}