#pragma once

#include "../utils/Stack.cpp"
#include "VariableLocation.cpp"
#include "environment/EnvironmentLinkedList.cpp"

class CodeGenerator
{
   public:
    enum class CodeGeneratorStates
    {
        GLOBAL,
        FUNCTION,
        CLASS
    } state;

    VariableLocation* relAccessVarLocation;
    EnvironmentLinkedList* environmentList;

    const std::string CLASS_SIZE_COMPILE_VAR = "classSize";

    CodeGenerator()
    {
        state = CodeGeneratorStates::GLOBAL;
        relAccessVarLocation = nullptr;
        environmentList = new EnvironmentLinkedList();
        environmentList->Push(new Environment());
    }
};