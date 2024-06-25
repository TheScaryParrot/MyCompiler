#pragma once

#include "../Environment.cpp"

class EnvironmentLinkedListElement
{
   public:
    EnvironmentLinkedListElement(Environment* environment, EnvironmentLinkedListElement* next)
    {
        this->environment = environment;
        this->next = next;
    }

    Environment* environment;
    EnvironmentLinkedListElement* next;
};

class EnvironmentLinkedList : IEnvironment
{
   public:
    Environment* Top();
    void Push(Environment* environment);
    void Pop();

    /// @brief Adds the given variable to the current environment with the given identifier
    virtual void AddVariable(std::string identifier, Variable* variable) override;
    /// @brief Returns a variable that is defined in the current environment
    virtual Variable* GetVariable(std::string identifier) override;
    /// @brief Returns true if the given variable is in the current environment
    virtual bool HasVariable(std::string identifier) override;
    /// @brief Returns true if the given variable is in the current environment
    virtual bool HasVariable(Variable* variable) override;

    /// @brief Adds the given function to the current environment with the given identifier
    virtual void AddFunction(std::string identifier, Function* function) override;
    /// @brief Returns a function that is defined in the current environment
    virtual Function* GetFunction(std::string identifier) override;
    /// @brief Returns true if the given function is in the current environment
    virtual bool HasFunction(std::string identifier) override;
    /// @brief Returns true if the given function is in the current environment
    virtual bool HasFunction(Function* function) override;

    /// @brief Adds the given type to the current environment with the given identifier
    virtual void AddType(std::string identifier, std::shared_ptr<Type> type) override;
    /// @brief Returns a type that is defined in the current environment
    virtual Type* GetType(std::string identifier) override;
    /// @brief Returns true if the given type is in the current environment
    virtual bool HasType(std::string identifier) override;
    /// @brief Returns true if the given type is in the current environment
    virtual bool HasType(Type* type) override;

    /// @brief Adds the given label to the current environment with the given identifier
    virtual void AddLabel(std::string identifier, JumpLabel* jumpLabel) override;
    /// @brief Returns a label that is defined in the current environment
    virtual JumpLabel* GetLabel(std::string identifier) override;
    /// @brief Returns true if the given label is in the current environment
    virtual bool HasLabel(std::string identifier) override;

    /// @brief Sets the environment of the given type identifier
    /// @param staticEnvironment If true, sets the static environment
    virtual void SetEnvironment(Type* type, std::shared_ptr<IEnvironment> environment, bool staticEnvironment) override;
    /// @brief Returns the environment of the given type identifier
    /// @param staticEnvironment If true, returns the static environment
    virtual IEnvironment* GetEnvironment(std::string typeIdentifier, bool staticEnvironment) override;
    /// @brief Returns the environment of the given type
    /// @param staticEnvironment If true, returns the static environment
    virtual IEnvironment* GetEnvironment(Type* type, bool staticEnvironment) override;

   private:
    EnvironmentLinkedListElement* head = nullptr;
};

Environment* EnvironmentLinkedList::Top() { return head->environment; }

void EnvironmentLinkedList::Push(Environment* environment)
{
    head = new EnvironmentLinkedListElement(environment, head);
}

void EnvironmentLinkedList::Pop() { head = head->next; }

void EnvironmentLinkedList::AddVariable(std::string identifier, Variable* variable)
{
    head->environment->AddVariable(identifier, variable);
}

Variable* EnvironmentLinkedList::GetVariable(std::string identifier)
{
    if (head->environment->HasVariable(identifier))
    {
        return head->environment->GetVariable(identifier);
    }

    if (head->next != nullptr)
    {
        return head->next->environment->GetVariable(identifier);
    }

    std::cerr << "Variable " << identifier << " not found\n";
    return nullptr;
}

bool EnvironmentLinkedList::HasVariable(std::string identifier)
{
    return head->environment->HasVariable(identifier) ||
           (head->next != nullptr && head->next->environment->HasVariable(identifier));
}

bool EnvironmentLinkedList::HasVariable(Variable* variable)
{
    return head->environment->HasVariable(variable) ||
           (head->next != nullptr && head->next->environment->HasVariable(variable));
}

void EnvironmentLinkedList::AddFunction(std::string identifier, Function* function)
{
    head->environment->AddFunction(identifier, function);
}

Function* EnvironmentLinkedList::GetFunction(std::string identifier)
{
    if (head->environment->HasFunction(identifier))
    {
        return head->environment->GetFunction(identifier);
    }

    if (head->next != nullptr)
    {
        return head->next->environment->GetFunction(identifier);
    }

    std::cerr << "Function " << identifier << " not found\n";
    return nullptr;
}

bool EnvironmentLinkedList::HasFunction(std::string identifier)
{
    return head->environment->HasFunction(identifier) ||
           (head->next != nullptr && head->next->environment->HasFunction(identifier));
}

bool EnvironmentLinkedList::HasFunction(Function* function)
{
    return head->environment->HasFunction(function) ||
           (head->next != nullptr && head->next->environment->HasFunction(function));
}

void EnvironmentLinkedList::AddType(std::string identifier, std::shared_ptr<Type> type)
{
    head->environment->AddType(identifier, type);
}

Type* EnvironmentLinkedList::GetType(std::string identifier)
{
    if (head->environment->HasType(identifier))
    {
        return head->environment->GetType(identifier);
    }

    if (head->next != nullptr)
    {
        return head->next->environment->GetType(identifier);
    }

    std::cerr << "Type " << identifier << " not found\n";
    return nullptr;
}

bool EnvironmentLinkedList::HasType(std::string identifier)
{
    return head->environment->HasType(identifier) ||
           (head->next != nullptr && head->next->environment->HasType(identifier));
}

bool EnvironmentLinkedList::HasType(Type* type)
{
    return head->environment->HasType(type) || (head->next != nullptr && head->next->environment->HasType(type));
}

void EnvironmentLinkedList::AddLabel(std::string identifier, JumpLabel* jumpLabel)
{
    head->environment->AddLabel(identifier, jumpLabel);
}

JumpLabel* EnvironmentLinkedList::GetLabel(std::string identifier)
{
    if (head->environment->HasLabel(identifier))
    {
        return head->environment->GetLabel(identifier);
    }

    if (head->next != nullptr)
    {
        return head->next->environment->GetLabel(identifier);
    }

    std::cerr << "Label " << identifier << " not found\n";
    return nullptr;
}

bool EnvironmentLinkedList::HasLabel(std::string identifier)
{
    return head->environment->HasLabel(identifier) ||
           (head->next != nullptr && head->next->environment->HasLabel(identifier));
}

void EnvironmentLinkedList::SetEnvironment(Type* type, std::shared_ptr<IEnvironment> environment,
                                           bool staticEnvironment)
{
    head->environment->SetEnvironment(type, environment, staticEnvironment);
}

IEnvironment* EnvironmentLinkedList::GetEnvironment(std::string typeIdentifier, bool staticEnvironment)
{
    if (head->environment->HasType(typeIdentifier))
    {
        return head->environment->GetEnvironment(typeIdentifier, staticEnvironment);
    }

    if (head->next != nullptr)
    {
        return head->next->environment->GetEnvironment(typeIdentifier, staticEnvironment);
    }

    std::cerr << "Environment to type " << typeIdentifier << " not found\n";
    return nullptr;
}

IEnvironment* EnvironmentLinkedList::GetEnvironment(Type* type, bool staticEnvironment)
{
    if (head->environment->HasType(type))
    {
        return head->environment->GetEnvironment(type, staticEnvironment);
    }

    if (head->next != nullptr)
    {
        return head->next->environment->GetEnvironment(type, staticEnvironment);
    }

    std::cerr << "Environment to type " << type->ToString() << " not found\n";
    return nullptr;
}
