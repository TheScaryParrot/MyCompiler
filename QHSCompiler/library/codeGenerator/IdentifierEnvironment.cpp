#pragma once

#include "Environment.cpp"
#include "Identifier.cpp"

class IdentifierEnvironment : Environment
{
   public:
    void AddIdentifier(std::string name, Identifier* identifier) { this->AddCallable(name, identifier); }
    Identifier* GetIdentifier(std::string name) { return (Identifier*)this->GetCallable(name); }
    void ExecuteIdentifier(std::string name, ICodeGenerator* codeGenerator) { ExecuteCallable(name, codeGenerator); }
};
