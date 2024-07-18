#pragma once

#include <string>

#include "Variable.cpp"
#include "environment/EnvironmentLinkedList.cpp"
#include "types/Type.cpp"
#include "types/primitiveTypes/BoolType.cpp"
#include "types/primitiveTypes/CharType.cpp"
#include "types/primitiveTypes/FloatType.cpp"
#include "types/primitiveTypes/IntType.cpp"
#include "varLocation/constVarLocations/BoolConstVarLocation.cpp"
#include "varLocation/constVarLocations/FloatConstVarLocation.cpp"
#include "varLocation/constVarLocations/IntConstVarLocation.cpp"

class CodeGenerator
{
   private:
    EnvironmentLinkedList environmentLinkedList;

    void AddPrimitiveTypes()
    {
        AddType("int", new IntType());
        AddType("float", new FloatType());
        AddType("char", new CharType());
        AddType("bool", new BoolType());
    }

   public:
    CodeGenerator()
    {
        environmentLinkedList = EnvironmentLinkedList();
        PushNewEnvironment();
        AddPrimitiveTypes();
    }

    bool DoesVariableExist(std::string variableName) { return environmentLinkedList.DoesVariableExist(variableName); }
    Variable* GetVariable(std::string variableName) { return environmentLinkedList.GetVariable(variableName); }
    void AddVariable(std::string variableName, Variable* variable) { environmentLinkedList.AddVariable(variableName, variable); }

    bool DoesTypeExist(std::string typeName) { return environmentLinkedList.DoesTypeExist(typeName); }
    Type* GetType(std::string typeName) { return environmentLinkedList.GetType(typeName); }
    void AddType(std::string typeName, Type* type) { environmentLinkedList.AddType(typeName, type); }

    Variable* GetNewLocalVariable(Type* type) { return nullptr; }

    IVariableLocation* ConstructLogicalConstVariableLocation(bool value) { return new BoolConstVarLocation(value); }
    IVariableLocation* ConstructIntConstVariableLocation(int value) { return new IntConstVarLocation(value); }
    IVariableLocation* ConstructFloatConstVaribaleLocation(float value) { return new FloatConstVarLocation(value); }

    void PushNewEnvironment() { environmentLinkedList.PushEnvironment(new Environment()); }
    void PopEnvironment() { environmentLinkedList.PopEnvironment(); }
};