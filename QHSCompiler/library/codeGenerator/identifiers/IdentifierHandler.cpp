#pragma once

#include "EnvironmentLinkedList.cpp"

/// @brief Simple static wrapper for the EnvironmentLinkedList
static class IdentifierHandler
{
   private:
    EnvironmentLinkedList environment;

   public:
    IdentifierHandler() { PushEnvironment(); }

    void PushEnvironment() { this->environment.PushEnvironment(new Environment()); }
    void PopEnvironment() { this->environment.PopEnvironment(); }

    void AddIdentifier(std::string name, Identifier* identifier) { this->environment.AddIdentifier(name, identifier); }
    Identifier* GetIdentifier(std::string name) { return this->environment.GetIdentifier(name); }
} IdentifierHandler;