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
    
    /// @brief Generates the assembly code for the given variable declaration and adds it to the environment. Does not assign a value to the variable!
    virtual AssemblyCode* GenerateVariableDeclaration(VarDeclarationNode* declaration) = 0;

    //TODO: identifier not past in as string, but as IdentifierNode or something
    virtual VariableLocation GetVariableLocation(std::string identifier) = 0;


    // Functions:

    virtual AssemblyCode* GenerateFunctionDeclaration(FuncDeclarationNode* declaration) = 0;

    virtual AssemblyCode* GenerateFunctionCall(CallNode* call) = 0;
};