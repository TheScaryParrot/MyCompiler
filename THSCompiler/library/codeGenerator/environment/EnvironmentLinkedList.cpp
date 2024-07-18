#pragma once

#include "Environment.cpp"

struct EnvironmentLinkedListElement
{
    Environment* environment;
    EnvironmentLinkedListElement* next;
};

class EnvironmentLinkedList
{
   private:
    EnvironmentLinkedListElement* head;

   public:
    bool DoesVariableExist(std::string variableName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasVariable(variableName))
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    Variable* GetVariable(std::string variableName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasVariable(variableName))
            {
                return current->environment->GetVariable(variableName);
            }

            current = current->next;
        }

        return nullptr;
    }

    void AddVariable(std::string variableName, Variable* variable) { head->environment->AddVariable(variableName, variable); }

    bool DoesTypeExist(std::string typeName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasType(typeName))
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    Type* GetType(std::string typeName)
    {
        EnvironmentLinkedListElement* current = head;
        while (current != nullptr)
        {
            if (current->environment->HasType(typeName))
            {
                return current->environment->GetType(typeName);
            }

            current = current->next;
        }

        return nullptr;
    }

    void AddType(std::string typeName, Type* type) { head->environment->AddType(typeName, type); }

    void PushEnvironment(Environment* environment)
    {
        EnvironmentLinkedListElement* newElement = new EnvironmentLinkedListElement();
        newElement->environment = environment;
        newElement->next = head;
        head = newElement;
    }

    void PopEnvironment()
    {
        Environment* environment = head->environment;
        EnvironmentLinkedListElement* newHead = head->next;

        delete head;
        delete environment;

        head = newHead;
    }
};