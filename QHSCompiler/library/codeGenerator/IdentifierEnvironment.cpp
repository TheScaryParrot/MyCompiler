#pragma once

#include "Environment.cpp"
#include "Identifier.cpp"

class IdentifierEnvironment : Environment
{
   public:
    void AddIdentifier(std::string name, Identifier* identifier);
    Identifier* GetIdentifier(std::string name);
    void ExecuteIdentifier(std::string name, ICodeGenerator* codeGenerator);
};

void IdentifierEnvironment::AddIdentifier(std::string name, Identifier* identifier)
{
    this->AddCallable(name, identifier);
}

Identifier* IdentifierEnvironment::GetIdentifier(std::string name) { return (Identifier*)this->GetCallable(name); }

void IdentifierEnvironment::ExecuteIdentifier(std::string name, ICodeGenerator* codeGenerator)
{
    this->ExecuteCallable(name, codeGenerator);
}
