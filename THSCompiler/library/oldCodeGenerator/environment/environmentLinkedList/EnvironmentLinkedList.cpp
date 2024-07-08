#pragma once

#include "../Environment.cpp"

class EnvironmentLinkedListElement
{
   public:
    EnvironmentLinkedListElement(IEnvironment* environment, EnvironmentLinkedListElement* next)
    {
        this->environment = environment;
        this->next = next;
    }

    IEnvironment* environment;
    EnvironmentLinkedListElement* next;
};

class EnvironmentLinkedList : IEnvironment
{
   public:
    IEnvironment* Top();

    void Push(IEnvironment* environment);

    /// @brief Pushes a new/empty environment to the top of the stack
    void PushNew();

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

    /// @brief Sets the given type to number consts
    virtual void SetNumberConstType(Type* type) override;
    /// @brief Gets the given type of number consts
    virtual Type* GetNumberConstType() override;
    /// @brief Sets the given type to string consts
    virtual void SetStringConstType(Type* type) override;
    /// @brief Gets the given type of string consts
    virtual Type* GetStringConstType() override;
    /// @brief Sets the given type to logic consts
    virtual void SetLogicConstType(Type* type) override;
    /// @brief Gets the given type of logic consts
    virtual Type* GetLogicConstType() override;

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

IEnvironment* EnvironmentLinkedList::Top() { return head->environment; }

void EnvironmentLinkedList::Push(IEnvironment* environment)
{
    head = new EnvironmentLinkedListElement(environment, head);
}

void EnvironmentLinkedList::PushNew() { Push(new Environment()); }

void EnvironmentLinkedList::Pop() { head = head->next; }

void EnvironmentLinkedList::AddVariable(std::string identifier, Variable* variable)
{
    head->environment->AddVariable(identifier, variable);
}
Variable* EnvironmentLinkedList::GetVariable(std::string identifier)
{
    if (head == nullptr)
    {
        std::cerr << "No environment to get variable from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->HasVariable(identifier))
        {
            return current->environment->GetVariable(identifier);
        }

        current = current->next;
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
    if (head == nullptr)
    {
        std::cerr << "No environment to get function from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->HasFunction(identifier))
        {
            return current->environment->GetFunction(identifier);
        }

        current = current->next;
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
    if (head == nullptr)
    {
        std::cerr << "No environment to get type from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->HasType(identifier))
        {
            return current->environment->GetType(identifier);
        }

        current = current->next;
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

void EnvironmentLinkedList::SetNumberConstType(Type* type) { head->environment->SetNumberConstType(type); }
Type* EnvironmentLinkedList::GetNumberConstType()
{
    // TODO: This is a short term solution; will be replaced by compiler instruction
    return GetType("int");

    if (head == nullptr)
    {
        std::cerr << "No environment to get number const type from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->GetNumberConstType() != nullptr)
        {
            return current->environment->GetNumberConstType();
        }

        current = current->next;
    }
}

void EnvironmentLinkedList::SetStringConstType(Type* type) { head->environment->SetStringConstType(type); }
Type* EnvironmentLinkedList::GetStringConstType()
{
    // TODO: This is a short term solution; will be replaced by compiler instruction
    return GetType("string");

    if (head == nullptr)
    {
        std::cerr << "No environment to get string const type from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->GetStringConstType() != nullptr)
        {
            return current->environment->GetStringConstType();
        }

        current = current->next;
    }
}

void EnvironmentLinkedList::SetLogicConstType(Type* type) { head->environment->SetLogicConstType(type); }
Type* EnvironmentLinkedList::GetLogicConstType()
{
    // TODO: This is a short term solution; will be replaced by compiler instruction
    return GetType("bool");

    if (head == nullptr)
    {
        std::cerr << "No environment to get logic const type from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->GetLogicConstType() != nullptr)
        {
            return current->environment->GetLogicConstType();
        }

        current = current->next;
    }
}

void EnvironmentLinkedList::AddLabel(std::string identifier, JumpLabel* jumpLabel)
{
    head->environment->AddLabel(identifier, jumpLabel);
}
JumpLabel* EnvironmentLinkedList::GetLabel(std::string identifier)
{
    if (head == nullptr)
    {
        std::cerr << "No environment to get label from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->HasLabel(identifier))
        {
            return current->environment->GetLabel(identifier);
        }

        current = current->next;
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
    if (head == nullptr)
    {
        std::cerr << "No environment to get environment from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->HasType(typeIdentifier))
        {
            return current->environment->GetEnvironment(typeIdentifier, staticEnvironment);
        }

        current = current->next;
    }

    std::cerr << "Environment to " << typeIdentifier << " not found\n";
    return nullptr;
}
IEnvironment* EnvironmentLinkedList::GetEnvironment(Type* type, bool staticEnvironment)
{
    if (head == nullptr)
    {
        std::cerr << "No environment to get environment from. Linked list head is nullptr\n";
        return nullptr;
    }

    EnvironmentLinkedListElement* current = head;

    while (current != nullptr)
    {
        if (current->environment == nullptr)
        {
            std::cerr << "Environment is nullptr. This should not happen\n";
        }
        else if (current->environment->HasType(type))
        {
            return current->environment->GetEnvironment(type, staticEnvironment);
        }

        current = current->next;
    }

    std::cerr << "Environment to " << type->name << " not found\n";
    return nullptr;
}
