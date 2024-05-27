#pragma once

#include <memory>

#include "../ScopeSpecificEnvironment.cpp"

// inherits from IScopeSpecificEnvironment so that it can be used in the same way as ScopeSpecificEnvironment
class ScopeSpecificEnvironmentLinkedListElement : IScopeSpecificEnvironment
{
public:
    ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> environment, std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent);

    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> GetParent();

    #pragma region IScopeSpecificEnvironment implementation

    /// @brief Generates the assembly code for the given variable declaration and adds it to the environment. Does not assign a value to the variable!
    virtual AssemblyCode* GenerateVariableDeclaration(VarDeclarationNode* declaration) override;

    //TODO: identifier not past in as string, but as IdentifierNode or something ?
    virtual VariableLocation GetVariableLocation(std::string identifier) override;

    virtual AssemblyCode* GenerateFunctionDeclaration(FuncDeclarationNode* declaration) override;

    virtual AssemblyCode* GenerateFunctionCall(CallNode* call) override;

    #pragma endregion

private:
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent;
    std::shared_ptr<ScopeSpecificEnvironment> environment;
};

ScopeSpecificEnvironmentLinkedListElement::ScopeSpecificEnvironmentLinkedListElement(std::shared_ptr<ScopeSpecificEnvironment> environment, std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> parent)
{
    this->environment = environment;
    this->parent = parent;
}

std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> ScopeSpecificEnvironmentLinkedListElement::GetParent()
{
    return parent;
}

#pragma region IScopeSpecificEnvironment implementation

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::GenerateVariableDeclaration(VarDeclarationNode* declaration)
{
    return environment->GenerateVariableDeclaration(declaration);
}

VariableLocation ScopeSpecificEnvironmentLinkedListElement::GetVariableLocation(std::string identifier)
{
    if (environment->HasVariable(identifier))
    {
        return environment->GetVariableLocation(identifier);
    }

    if (parent == nullptr)
    {
        std::cout << "Variable " << identifier << " not found in environment\n";
        return VariableLocation();
    }
    
    return parent->GetVariableLocation(identifier);
}

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::GenerateFunctionDeclaration(FuncDeclarationNode* declaration)
{
    return environment->GenerateFunctionDeclaration(declaration);
}

AssemblyCode* ScopeSpecificEnvironmentLinkedListElement::GenerateFunctionCall(CallNode* call)
{
    if (environment->HasFunction(call->functionName))
    {
        return environment->GenerateFunctionCall(call);
    }

    if (parent == nullptr)
    {
        std::cout << "Function " << call->functionName << " not found in environment\n";
        return nullptr;
    }

    return parent->GenerateFunctionCall(call);
}

#pragma endregion
