#pragma once

#include "../../utils/Map.cpp"
#include "../Variable.cpp"
#include "../types/Type.cpp"

class Environment
{
   private:
    Map<std::string, std::shared_ptr<Variable>> variables;
    Map<std::string, std::shared_ptr<Type>> types;

   public:
    bool HasVariable(std::string variableName) { return variables.Contains(variableName); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return variables.Get(variableName); }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { variables.Insert(variableName, variable); }

    bool HasType(std::string typeName) { return types.Contains(typeName); }
    std::shared_ptr<Type> GetType(std::string typeName) { return types.Get(typeName); }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { types.Insert(typeName, type); }
};