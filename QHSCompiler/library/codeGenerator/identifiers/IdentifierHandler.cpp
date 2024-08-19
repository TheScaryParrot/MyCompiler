#pragma once

#include "EnvironmentLinkedList.cpp"

/// @brief Simple static wrapper for the EnvironmentLinkedList
static class IdentifierHandler
{
   private:
    EnvironmentLinkedList environment;

   public:
    void NewEnvironment() { this->environment.AddEnvironment(new Environment()); }

    void AddIdentifier(std::string name, Identifier* identifier) { this->environment.AddIdentifier(name, identifier); }
    Identifier* GetIdentifier(std::string name) { return this->environment.GetIdentifier(name); }
} IdentifierHandler;