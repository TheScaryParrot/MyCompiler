#pragma once

#include <memory>

#include "../../syntaxTree/SyntaxTree.cpp"
#include "../../assembly/AssemblyCode.cpp"

#include "../../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"


#include "../../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"

static class CodeGenerator
{
public:
    std::unique_ptr<AssemblyCode> GenerateCode(SyntaxTree* syntaxTree);

private:
    AssemblyCode* GenerateLine(AbstractLineNode* line);


    AssemblyCode* GenerateDeclaration(const AbstractDeclarationNode* declaration);
    AssemblyCode* GenerateVarDeclaration(VarDeclarationNode* declaration);
    AssemblyCode* GenerateFuncDeclaration(FuncDeclarationNode* declaration);
    AssemblyCode* GenerateClassDeclaration(ClassDeclarationNode* declaration);


    AssemblyCode* GenerateStatement(AbstractStatementNode* statement);
    AssemblyCode* GenerateBody(BodyNode* body);

    AssemblyCode* GenerateKeywordStatement(AbstractKeywordStatementNode* statement);
    AssemblyCode* GenerateIfStatement(IfStatementNode* statement);
    AssemblyCode* GenerateIfStatement(IfStatementNode* statement, std::string finalLabel);
    AssemblyCode* GenerateReturnStatement(ReturnStatementNode* statement);
    AssemblyCode* GenerateWhileStatement(WhileStatementNode* statement);
    AssemblyCode* GenerateForStatement(ForStatementNode* statement);
    AssemblyCode* GenerateContinueStatement(ContinueStatementNode* statement);
    AssemblyCode* GenerateBreakStatement(BreakStatementNode* statement);

}CodeGenerator;

std::unique_ptr<AssemblyCode> CodeGenerator::GenerateCode(SyntaxTree* syntaxTree)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (size_t i = 0; i < syntaxTree->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(syntaxTree->GetLine(i)));
    }

    return std::unique_ptr<AssemblyCode>(assemblyCode);
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