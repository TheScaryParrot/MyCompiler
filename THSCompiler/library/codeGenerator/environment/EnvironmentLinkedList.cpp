#pragma once

#include <functional>

#include "Environment.cpp"

struct EnvironmentLinkedListElement
{
    IEnvironment* self;
    EnvironmentLinkedListElement* next;
};

class EnvironmentLinkedList : public IEnvironment
{
   private:
    EnvironmentLinkedListElement* head;

   public:
    void Push(IEnvironment* environment)
    {
        EnvironmentLinkedListElement* newElement = new EnvironmentLinkedListElement();
        newElement->self = environment;
        newElement->next = head;
        head = newElement;
    }

    IEnvironment* Pop()
    {
        if (head == nullptr) return nullptr;

        EnvironmentLinkedListElement* oldHead = head;
        IEnvironment* oldEnvironment = oldHead->self;
        head = head->next;
        delete oldHead;  // deleting does not delete the Environment, only the EnvironmentLinkedListElement
        return oldEnvironment;
    }

    /// @brief Sets head to nullptr; Does not delete the Environment objects!
    void Clear() { head = nullptr; }

    virtual Map<std::string, IVariableLocation*>* GetVariableMap() override { return head->self->GetVariableMap(); }
    IVariableLocation* GetVariable(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetVariableMap()->Contains(key))
            {
                return current->self->GetVariableMap()->Get(key);
            }
        }

        return nullptr;
    }
    bool HasVariable(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetVariableMap()->Contains(key))
            {
                return true;
            }
        }

        return false;
    }

    virtual Map<std::string, Type*>* GetTypeMap() override { return head->self->GetTypeMap(); }
    Type* GetType(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetTypeMap()->Contains(key))
            {
                return current->self->GetTypeMap()->Get(key);
            }
        }

        return nullptr;
    }
    bool HasType(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetTypeMap()->Contains(key))
            {
                return true;
            }
        }

        return false;
    }

    virtual Map<std::string, std::string*>* GetCompilerVarStringMap() override { return head->self->GetCompilerVarStringMap(); }
    std::string* GetCompilerVarString(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetCompilerVarStringMap()->Contains(key))
            {
                return current->self->GetCompilerVarStringMap()->Get(key);
            }
        }

        return nullptr;
    }
    bool HasCompilerVarString(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetCompilerVarStringMap()->Contains(key))
            {
                return true;
            }
        }

        return false;
    }

    virtual Map<std::string, int*>* GetCompilerVarIntMap() override { return head->self->GetCompilerVarIntMap(); }
    int* GetCompilerVarInt(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetCompilerVarIntMap()->Contains(key))
            {
                return current->self->GetCompilerVarIntMap()->Get(key);
            }
        }

        return nullptr;
    }
    bool HasCompilerVarInt(std::string key)
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            if (current->self->GetCompilerVarIntMap()->Contains(key))
            {
                return true;
            }
        }

        return false;
    }

    virtual Type* GetNumConstType() override
    {
        for (EnvironmentLinkedListElement* current = head; current != nullptr; current = current->next)
        {
            Type* type = current->self->GetNumConstType();

            if (type != nullptr)
            {
                return type;
            }
        }

        return nullptr;
    }
    virtual void SetNumConstType(Type* type) override { head->self->SetNumConstType(type); }
};
