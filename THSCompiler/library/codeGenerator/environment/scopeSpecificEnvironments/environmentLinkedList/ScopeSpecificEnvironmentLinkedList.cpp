#pragma once

#include <iostream>

#include "ScopeSpecificEnvironmentLinkedListElement.cpp"

class ScopeSpecificEnvironmentLinkedList
{
   public:
    ScopeSpecificEnvironmentLinkedList();

    /// @brief Adds the given environment to the linked list
    void PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment);

    /// @brief Removes the current head of the linked list
    void PopEnvironment();

    ScopeSpecificEnvironmentLinkedListElement* GetHead();

   private:
    std::shared_ptr<ScopeSpecificEnvironmentLinkedListElement> head;

    /// @brief Finds the first environment that satisfies the given predicate; for example, to find the first
    /// environment that has a variable
    /// @return Returns a shared_ptr to the found ScopeSpecificEnvironment; nullptr if no environment satisfies the
    /// predicate
    std::shared_ptr<ScopeSpecificEnvironment> FindEnvironment(
        std::function<bool(std::shared_ptr<ScopeSpecificEnvironment>)> predicate);
};

ScopeSpecificEnvironmentLinkedList::ScopeSpecificEnvironmentLinkedList() { head = nullptr; }

void ScopeSpecificEnvironmentLinkedList::PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment> environment)
{
    head = std::make_shared<ScopeSpecificEnvironmentLinkedListElement>(environment, head);
}

void ScopeSpecificEnvironmentLinkedList::PopEnvironment() { head = head->GetParent(); }

ScopeSpecificEnvironmentLinkedListElement* ScopeSpecificEnvironmentLinkedList::GetHead() { return head.get(); }