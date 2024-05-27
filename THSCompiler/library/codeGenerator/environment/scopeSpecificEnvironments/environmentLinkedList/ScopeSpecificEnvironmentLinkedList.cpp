#pragma once

#include <iostream>

#include "ScopeSpecificEnvironmentLinkedListElement.cpp"

// Inherits IScopeSpecificEnvironment so that it can be used in the same way as ScopeSpecificEnvironment
class ScopeSpecificEnvironmentLinkedList : IScopeSpecificEnvironment
{
public:
    ScopeSpecificEnvironmentLinkedList();

    /// @brief Adds the given environment to the linked list
    void PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment);

    /// @brief Removes the current head of the linked list
    void PopEnvironment();


    #pragma region IScopeSpecificEnvironment implementation

    /// @brief Generates the assembly code for the given variable declaration and adds it to the environment. Does not assign a value to the variable!
    virtual AssemblyCode* GenerateVariableDeclaration(VarDeclarationNode* declaration) override;

    //TODO: identifier not past in as string, but as IdentifierNode or something
    virtual VariableLocation GetVariableLocation(std::string identifier) override;

    virtual AssemblyCode* GenerateFunctionDeclaration(FuncDeclarationNode* declaration) override;

    virtual AssemblyCode* GenerateFunctionCall(CallNode* call) override;

    #pragma endregion

private:
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> head;

    /// @brief Finds the first environment that satisfies the given predicate; for example, to find the first environment that has a variable
    /// @return Returns a shared_ptr to the found ScopeSpecificEnvironment; nullptr if no environment satisfies the predicate
    std::shared_ptr<ScopeSpecificEnvironment> FindEnvironment(std::function<bool(std::shared_ptr<ScopeSpecificEnvironment>)> predicate);
};

ScopeSpecificEnvironmentLinkedList::ScopeSpecificEnvironmentLinkedList()
{
    head = nullptr;
}

void ScopeSpecificEnvironmentLinkedList::PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment)
{
    head = std::make_shared<ScopeSpecificEnvironmentLinkedListElement>(environment, head);
}

void ScopeSpecificEnvironmentLinkedList::PopEnvironment()
{
    head = head->GetParent();
}

#pragma region IScopeSpecificEnvironment implementation

AssemblyCode* ScopeSpecificEnvironmentLinkedList::GenerateVariableDeclaration(VarDeclarationNode* declaration)
{
    return head->GenerateVariableDeclaration(declaration);
};

VariableLocation ScopeSpecificEnvironmentLinkedList::GetVariableLocation(std::string identifier)
{
    return head->GetVariableLocation(identifier);
};

AssemblyCode* ScopeSpecificEnvironmentLinkedList::GenerateFunctionDeclaration(FuncDeclarationNode* declaration)
{
    return head->GenerateFunctionDeclaration(declaration);
};

AssemblyCode* ScopeSpecificEnvironmentLinkedList::GenerateFunctionCall(CallNode* call)
{
    return head->GenerateFunctionCall(call);
};

# pragma endregion