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
        AddType("int", std::shared_ptr<Type>(new IntType()));
        AddType("float", std::shared_ptr<Type>(new FloatType()));
        AddType("char", std::shared_ptr<Type>(new CharType()));
        AddType("bool", std::shared_ptr<Type>(new BoolType()));
    }

   public:
    CodeGenerator()
    {
        environmentLinkedList = EnvironmentLinkedList();
        PushNewEnvironment();
        AddPrimitiveTypes();
    }

    bool DoesVariableExist(std::string variableName) { return environmentLinkedList.DoesVariableExist(variableName); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return environmentLinkedList.GetVariable(variableName); }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { environmentLinkedList.AddVariable(variableName, variable); }

    bool DoesTypeExist(std::string typeName) { return environmentLinkedList.DoesTypeExist(typeName); }
    std::shared_ptr<Type> GetType(std::string typeName) { return environmentLinkedList.GetType(typeName); }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { environmentLinkedList.AddType(typeName, type); }

    std::shared_ptr<Variable> GetNewLocalVariable(std::shared_ptr<Type> type) { return nullptr; }

    IVariableLocation* ConstructLogicalConstVariableLocation(bool value) { return new BoolConstVarLocation(value); }
    IVariableLocation* ConstructIntConstVariableLocation(int value) { return new IntConstVarLocation(value); }
    IVariableLocation* ConstructFloatConstVaribaleLocation(float value) { return new FloatConstVarLocation(value); }

    void PushNewEnvironment() { environmentLinkedList.PushEnvironment(new Environment()); }
    void PopEnvironment() { environmentLinkedList.PopEnvironment(); }
};