#pragma once

#include <memory>

#include "generator/CodeGenerator.cpp"

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
#include "../../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"

static class SyntaxTreeTraverser
{
public:
    std::shared_ptr<AssemblyCode> GenerateCode(SyntaxTree* syntaxTree);

private:
    CodeGenerator codeGenerator;

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

}SyntaxTreeTraverser;


std::shared_ptr<AssemblyCode> SyntaxTreeTraverser::GenerateCode(SyntaxTree* syntaxTree)
{
    codeGenerator = CodeGenerator(); // Initialize code generator

    AssemblyCode* assemblyCode = new AssemblyCode();

    for (size_t i = 0; i < syntaxTree->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(syntaxTree->GetLine(i)));
    }

    return std::shared_ptr<AssemblyCode>(assemblyCode);
}


AssemblyCode* SyntaxTreeTraverser::GenerateLine(AbstractLineNode* line)
{
    if (line == nullptr)
    {
        std::cout << "Line is null\n";
        return nullptr;
    }

    //FIXME: Solve this without dynamic_cast; visitor pattern with ISyntaxTreeTraverser?
    if (dynamic_cast<AbstractDeclarationNode*>(line) != nullptr)
    {
        return GenerateDeclaration(dynamic_cast<AbstractDeclarationNode*>(line));
    }


    // Generate statement
    return GenerateStatement(dynamic_cast<AbstractStatementNode*>(line));
};


#pragma region Declarations
AssemblyCode* SyntaxTreeTraverser::GenerateDeclaration(AbstractDeclarationNode* declaration)
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

AssemblyCode* SyntaxTreeTraverser::GenerateVarDeclaration(VarDeclarationNode* declaration)
{
    Variable* variable = codeGenerator.AddVariable(declaration->name, declaration->type.GetIdentfier());

    //TODO: Evaluate value
    AssemblyCode* assemblyCode = codeGenerator.SetVariable(declaration->name, nullptr);
    return assemblyCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    Function* function = codeGenerator.AddFunction(declaration->name, declaration->returnType.GetIdentfier());

    //TODO: Construct function environment
    AssemblyCode* body = GenerateStatement(declaration->statement);

    AssemblyCode* assemblyCode = codeGenerator.SetFunctionBody(function, body);
    return assemblyCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    // TODO: New environment for class
    //TODO: Add to current environment as type
    // TODO: Generate class code
    return nullptr;
}


#pragma endregion

#pragma region Statements

AssemblyCode* SyntaxTreeTraverser::GenerateStatement(AbstractStatementNode* statement)
{
    if (dynamic_cast<EmptyStatementNode*>(statement) != nullptr)
    {
        return nullptr; // No code if empty statement
    }

    if (dynamic_cast<BodyNode*>(statement) != nullptr)
    {
        return GenerateBody(dynamic_cast<BodyNode*>(statement));
    }

    if (dynamic_cast<AbstractKeywordStatementNode*>(statement) != nullptr)
    {
        return GenerateKeywordStatement(dynamic_cast<AbstractKeywordStatementNode*>(statement));
    }

    //TODO: check for other statement types

    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateBody(BodyNode* body)
{
    // TODO: New environment; where does it know what type of environment to create?
    // TODO: Generate body code
    return nullptr;
}

#pragma region Keyword statements

AssemblyCode* SyntaxTreeTraverser::GenerateKeywordStatement(AbstractKeywordStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateIfStatement(IfStatementNode* statement)
{
    // TODO: Get label for final
    return GenerateIfStatement(statement, "final");
}

AssemblyCode* SyntaxTreeTraverser::GenerateIfStatement(IfStatementNode* statement, std::string finalLabel)
{
    // TODO: Generate if statement
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateReturnStatement(ReturnStatementNode* statement)
{
    //TODO: Get return Variable from Environment
    //TODO: Assign return Variable to return value
    //TODO: Write RET instruction
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateWhileStatement(WhileStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateForStatement(ForStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateContinueStatement(ContinueStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateBreakStatement(BreakStatementNode* statement)
{
    return nullptr;
}

#pragma endregion

#pragma endregion