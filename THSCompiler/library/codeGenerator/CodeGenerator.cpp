#pragma once

#include "../assembly/AssemblyInstructionLine.cpp"
#include "../assembly/instructions/AssemblyInstructions.cpp"
#include "../utils/Stack.cpp"
#include "environment/EnvironmentLinkedList.cpp"
#include "varLocation/IVariableLocation.cpp"
#include "varLocation/RegistryVarLocation.cpp"

class CodeGenerator
{
   public:
    enum class CodeGeneratorStates
    {
        GLOBAL,
        FUNCTION,
        CLASS
    } state;

    IVariableLocation* relAccessBaseVarLocation;
    EnvironmentLinkedList* environmentList;

    const std::string CLASS_SIZE_COMPILE_VAR = "classSize";

    CodeGenerator()
    {
        state = CodeGeneratorStates::GLOBAL;
        relAccessBaseVarLocation = nullptr;
        environmentList = new EnvironmentLinkedList();
        environmentList->Push(new Environment());
    }

    IVariableLocation* AllocateNewVariableLocation(Type* type, AssemblyCode* assemblyCode)
    {
        // TODO: Look for registries, allocate on stack, stuff like that
        AssemblyInstructionLine* line = new AssemblyInstructionLine(AssemblyInstructions::ADD);
        line->AddArgument("esp");
        line->AddArgument("TEST");
        assemblyCode->AddLine(line);

        return new RegistryVarLocation("eax", 0, type);
    }
};