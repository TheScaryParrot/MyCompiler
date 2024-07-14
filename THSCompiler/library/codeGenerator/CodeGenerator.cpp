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
};