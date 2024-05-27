#pragma once

#include <memory>

#include "../environment/scopeSpecificEnvironments/environmentLinkedList/ScopeSpecificEnvironmentLinkedList.cpp"
#include "../environment/scopeSpecificEnvironments/GlobalScopeEnvironment.cpp"

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
    std::shared_ptr<AssemblyCode> GenerateCode(SyntaxTree* syntaxTree);

private:
    ScopeSpecificEnvironmentLinkedList environmentLinkedList;

    AssemblyCode* GenerateLine(AbstractLineNode* line);


    AssemblyCode* GenerateDeclaration(AbstractDeclarationNode* declaration);
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

std::shared_ptr<AssemblyCode> CodeGenerator::GenerateCode(SyntaxTree* syntaxTree)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    std::shared_ptr<Environment> environment = std::shared_ptr<Environment>(new Environment());
    std::shared_ptr<GlobalScopeEnvironment> globalScopeEnvironment = std::shared_ptr<GlobalScopeEnvironment>(new GlobalScopeEnvironment(environment));
    this->environmentLinkedList.PushEnvironment(std::shared_ptr<GlobalScopeEnvironment>(globalScopeEnvironment));

    for (size_t i = 0; i < syntaxTree->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(syntaxTree->GetLine(i)));
    }

    return std::shared_ptr<AssemblyCode>(assemblyCode);
}

AssemblyCode* CodeGenerator::GenerateLine(AbstractLineNode* line)
{
    if (line == nullptr)
    {
        std::cout << "Line is null\n";
        return nullptr;
    }

    //FIXME: Solve this without dynamic_cast; visitor pattern with ICodeGenerator?
    if (dynamic_cast<AbstractDeclarationNode*>(line) != nullptr)
    {
        return GenerateDeclaration(dynamic_cast<AbstractDeclarationNode*>(line));
    }


    // Generate statement
    return GenerateStatement(dynamic_cast<AbstractStatementNode*>(line));
};