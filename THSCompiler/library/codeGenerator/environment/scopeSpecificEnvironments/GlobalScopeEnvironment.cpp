#pragma once

#include <iostream>

#include "ScopeSpecificEnvironment.cpp"

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "../../../assembly/instructions/AssemblyInstructions.cpp"

class GlobalScopeEnvironment : public ScopeSpecificEnvironment
{
public:
    GlobalScopeEnvironment(std::shared_ptr<Environment> environment);

    virtual AssemblyCode* AddVariable(VarDeclarationNode* declaration) override;
};

GlobalScopeEnvironment::GlobalScopeEnvironment(std::shared_ptr<Environment> environment) : ScopeSpecificEnvironment(environment)
{
}

AssemblyCode* GlobalScopeEnvironment::AddVariable(VarDeclarationNode* declaration)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    AssemblyInstructionLine* instruction = new AssemblyInstructionLine(AssemblyInstructions::MOV);
    instruction->AddArgument("rax");

    assemblyCode->AddLine(std::shared_ptr<AssemblyInstructionLine>(instruction));

    return assemblyCode;
}