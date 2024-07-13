#pragma once

#include "../utils/Stack.cpp"
#include "EnvironmentLinkedList.cpp"
#include "VariableLocation.cpp"

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
    Stack<VariableLocation*> varLocationStack;
    EnvironmentLinkedList* environmentList;
};