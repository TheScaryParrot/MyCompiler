#include "CodeGenerator.hpp"

AssemblyCode* CodeGenerator::GenerateDeclaration(AbstractDeclarationNode* declaration)
{
    if (dynamic_cast<VarDeclarationNode*>(declaration) != nullptr)
    {
        return GenerateVarDeclaration(dynamic_cast<VarDeclarationNode*>(declaration));
    }
    
    if (dynamic_cast<FuncDeclarationNode*>(declaration) != nullptr)
    {
        return GenerateFuncDeclaration(dynamic_cast<FuncDeclarationNode*>(declaration));
    }

    return GenerateClassDeclaration(dynamic_cast<ClassDeclarationNode*>(declaration));
}

AssemblyCode* CodeGenerator::GenerateVarDeclaration(VarDeclarationNode* declaration)
{
    AssemblyCode* assemblyCode = this->environmentLinkedList.GenerateVariableDeclaration(declaration);
    // TODO: Set variable value
    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    AssemblyCode* assemblyCode = this->environmentLinkedList.GenerateFunctionDeclaration(declaration);
    // TODO: New environment for function
    // TODO: Generate function code
    return assemblyCode;
}

AssemblyCode* CodeGenerator::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    // TODO: New environment for class
    //TODO: Add to current environment as type
    // TODO: Generate class code
    return nullptr;
}