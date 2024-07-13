#pragma once

#include "../utils/Stack.cpp"
#include "VariableLocation.cpp"

class CodeGenerator
{
   public:
    VariableLocation* relAccessVarLocation;
    Stack<VariableLocation*> varLocationStack;
};