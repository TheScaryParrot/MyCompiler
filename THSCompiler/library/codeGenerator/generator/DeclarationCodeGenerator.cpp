#include "CodeGenerator.hpp"

AssemblyCode* CodeGenerator::GenerateDeclaration(AbstractDeclarationNode* declaration)
{
    if (typeid(*declaration) == typeid(VarDeclarationNode))
    {
        return GenerateVarDeclaration(dynamic_cast<VarDeclarationNode*>(declaration));
    }
    
    if (typeid(*declaration) == typeid(FuncDeclarationNode))
    {
        return GenerateFuncDeclaration(dynamic_cast<FuncDeclarationNode*>(declaration));
    }

    return GenerateClassDeclaration(dynamic_cast<ClassDeclarationNode*>(declaration));
}

AssemblyCode* CodeGenerator::GenerateVarDeclaration(VarDeclarationNode* declaration)
{
    // TODO: Add to current environment
    // TODO: Set variable value
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    //TODO: Add to current environment
    // TODO: New environment for function
    // TODO: Generate function code
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    // TODO: New environment for class
    //TODO: Add to current environment as type
    // TODO: Generate class code
    return nullptr;
}