#pragma once

#include "../../../assembly/AssemblyCode.cpp"

#include "../variables/VariableLocation.cpp"

#include "../../../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../../../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../../../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"

#include "../../../syntaxTree/nodes/line/expression/functionCall/CallNode.cpp"

class IScopeSpecificEnvironment
{
public:
    // Variables:
    
    virtual void AddVariable(std::string identifier, Variable* variable) = 0;

    //TODO: identifier not past in as string, but as IdentifierNode or something
    virtual VariableLocation GetVariableLocation(std::string identifier) = 0;


    // Functions:

    virtual void AddFunction(std::string identifier, Function* function) = 0;

    virtual AssemblyCode* SetFunctionBody(Function* function, AssemblyCode* body) = 0;

    virtual AssemblyCode* GenerateFunctionCall(Function* function, std::vector<Variable*> arguments) = 0;

    // Types:

    virtual Type* GetType(std::string identifier) = 0;

    

    virtual bool HasVariable(std::string identifier) = 0;
    virtual bool HasVariable(Variable* variable) = 0;

    virtual bool HasFunction(std::string identifier) = 0;
    virtual bool HasFunction(Function* function) = 0;

    virtual bool HasTypeEnvironment(std::shared_ptr<Type> type) = 0;
};