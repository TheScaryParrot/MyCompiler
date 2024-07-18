#pragma once

#include "../../utils/Map.cpp"
#include "../Variable.cpp"
#include "../types/Type.cpp"

class Environment
{
   private:
    Map<std::string, Variable*> variables;
    Map<std::string, Type*> types;

   public:
    bool HasVariable(std::string variableName) { return variables.Contains(variableName); }
    Variable* GetVariable(std::string variableName) { return variables.Get(variableName); }
    void AddVariable(std::string variableName, Variable* variable) { variables.Insert(variableName, variable); }

    bool HasType(std::string typeName) { return types.Contains(typeName); }
    Type* GetType(std::string typeName) { return types.Get(typeName); }
    void AddType(std::string typeName, Type* type) { types.Insert(typeName, type); }
};