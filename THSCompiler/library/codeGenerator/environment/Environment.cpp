#pragma once

#include "../../utils/Map.cpp"
#include "../Function.cpp"
#include "../Variable.cpp"
#include "../types/Type.cpp"

class Environment
{
   private:
    Map<std::string, std::shared_ptr<Variable>> variables;
    Map<std::string, std::shared_ptr<Function>> functions;
    Map<std::string, std::shared_ptr<Type>> types;
    Map<std::string, std::string> jumpLabels;

   public:
    unsigned int* localVariableOffset;
    Environment(unsigned int localVariableOffset) { this->localVariableOffset = new unsigned int(localVariableOffset); }
    ~Environment() {}

    bool HasVariable(std::string variableName) { return variables.Contains(variableName); }
    std::shared_ptr<Variable> GetVariable(std::string variableName) { return variables.Get(variableName); }
    void AddVariable(std::string variableName, std::shared_ptr<Variable> variable) { variables.Insert(variableName, variable); }

    bool HasType(std::string typeName) { return types.Contains(typeName); }
    std::shared_ptr<Type> GetType(std::string typeName) { return types.Get(typeName); }
    void AddType(std::string typeName, std::shared_ptr<Type> type) { types.Insert(typeName, type); }

    bool HasFunction(std::string functionName) { return functions.Contains(functionName); }
    std::shared_ptr<Function> GetFunction(std::string functionName) { return functions.Get(functionName); }
    void AddFunction(std::string functionName, std::shared_ptr<Function> function) { functions.Insert(functionName, function); }

    bool HasJumpLabel(std::string labelName) { return jumpLabels.Contains(labelName); }
    std::string GetJumpLabel(std::string labelName) { return jumpLabels.Get(labelName); }
    void AddJumpLabel(std::string labelName, std::string label) { jumpLabels.Insert(labelName, label); }
};