#pragma once

#include "../utils/Stack.cpp"
#include "environment/EnvironmentLinkedList.cpp"
#include "varLocation/IVariableLocation.cpp"

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
};