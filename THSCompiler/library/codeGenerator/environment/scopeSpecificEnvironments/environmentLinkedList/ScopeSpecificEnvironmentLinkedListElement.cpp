#pragma once

#include <memory>

#include "../ScopeSpecificEnvironment.cpp"

class ScopeSpecificEnvironmentLinkedListElement
{
public:
    ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> environment, std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent);

    std::shared_ptr<ScopeSpecificEnvironment> GetEnvironment();

    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> GetParent();

private:
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent;
    std::shared_ptr<ScopeSpecificEnvironment> environment;
};

ScopeSpecificEnvironmentLinkedListElement::ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> environment, std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent)
{
    this->environment = environment;
    this->parent = parent;
}

std::shared_ptr<ScopeSpecificEnvironment> ScopeSpecificEnvironmentLinkedListElement::GetEnvironment()
{
    return environment;
}

std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> ScopeSpecificEnvironmentLinkedListElement::GetParent()
{
    return parent;
}
