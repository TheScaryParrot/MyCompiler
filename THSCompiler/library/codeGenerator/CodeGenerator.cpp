#pragma once

#include <string>

#include "Variable.cpp"
#include "types/Type.cpp"

class CodeGenerator
{
   public:
    bool DoesVariableExist(std::string variableName) { return false; }
    Variable* GetVariable(std::string variableName) { return nullptr; }
    void AddVariable(std::string variableName, Variable* variable) {}

    Type* GetType(std::string typeName) { return nullptr; }
    void AddType(std::string typeName, Type* type) {}

    Variable* GetNewLocalVariable(Type* type) { return nullptr; }

    IVariableLocation* ConstructLogicalConstVariableLocation(bool value) { return nullptr; }
    IVariableLocation* ConstructIntConstVariableLocation(std::string value) { return nullptr; }
    IVariableLocation* ConstructFloatConstVaribaleLocation(std::string value) { return nullptr; }
};