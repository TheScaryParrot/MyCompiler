#pragma once

#include <memory>

#include "../../syntaxTree/SyntaxTree.cpp"
#include "../../assembly/AssemblyCode.cpp"

#include "../../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"


#include "../../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"

static class CodeGenerator
{
public:
    std::auto_ptr<AssemblyCode> GenerateCode(SyntaxTree* syntaxTree);

private:
    AssemblyCode* GenerateLine(AbstractLineNode* line);

    AssemblyCode* GenerateDeclaration(AbstractDeclarationNode* declaration);
    AssemblyCode* GenerateVarDeclaration(VarDeclarationNode* declaration);
    AssemblyCode* GenerateFuncDeclaration(FuncDeclarationNode* declaration);
    AssemblyCode* GenerateClassDeclaration(ClassDeclarationNode* declaration);

    AssemblyCode* GenerateStatement(AbstractStatementNode* statement);

}CodeGenerator;

std::auto_ptr<AssemblyCode> CodeGenerator::GenerateCode(SyntaxTree* syntaxTree)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (size_t i = 0; i < syntaxTree->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(syntaxTree->GetLine(i)));
    }

    return std::auto_ptr<AssemblyCode>(assemblyCode);
}

AssemblyCode* CodeGenerator::GenerateLine(AbstractLineNode* line)
{
    //FIXME: Solve this without typeid and dynamic_cast; visitor pattern with ICodeGenerator?
    if (typeid(*line) == typeid(AbstractDeclarationNode))
    {
        return GenerateDeclaration(dynamic_cast<AbstractDeclarationNode*>(line));
    }
    
    // Generate statement
    return GenerateStatement(dynamic_cast<AbstractStatementNode*>(line));
};

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