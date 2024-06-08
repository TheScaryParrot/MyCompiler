#pragma once

#include <memory>

#include "generator/CodeGenerator.cpp"

#include "../syntaxTree/SyntaxTree.cpp"
#include "../assembly/AssemblyCode.cpp"

#include "../syntaxTree/nodes/line/declaration/AbstractDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/VarDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/varFuncDeclaration/FuncDeclarationNode.cpp"
#include "../syntaxTree/nodes/line/declaration/ClassDeclarationNode.cpp"


#include "../syntaxTree/nodes/line/statement/AbstractStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/AbstractKeywordStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/IfStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ReturnStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/WhileStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ForStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/ContinueStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/keywordStatement/BreakStatementNode.cpp"
#include "../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"

#include "../syntaxTree/nodes/line/expression/AssignmentNode.cpp"
#include "../syntaxTree/nodes/line/expression/OperatorExpressionNode.cpp"
#include "../syntaxTree/nodes/line/expression/UnaryExpressionNode.cpp"

static class SyntaxTreeTraverser
{
public:
    std::shared_ptr<AssemblyCode> GenerateCode(SyntaxTree* syntaxTree);

private:
    CodeGenerator codeGenerator;

    AssemblyCode* GenerateCodeBlock(CodeblockNode* codeBlock);

    AssemblyCode* GenerateLine(AbstractLineNode* line);

    AssemblyCode* GenerateDeclaration(AbstractDeclarationNode* declaration);
    AssemblyCode* GenerateVarDeclaration(VarDeclarationNode* declaration);
    AssemblyCode* GenerateFuncDeclaration(FuncDeclarationNode* declaration);
    AssemblyCode* GenerateClassDeclaration(ClassDeclarationNode* declaration);


    AssemblyCode* GenerateStatement(AbstractStatementNode* statement,  bool environmentLock);
    AssemblyCode* GenerateBody(BodyNode* body);

    AssemblyCode* GenerateKeywordStatement(AbstractKeywordStatementNode* statement);
    AssemblyCode* GenerateIfStatement(IfStatementNode* statement);
    AssemblyCode* GenerateIfStatement(IfStatementNode* statement, std::string finalLabel);
    AssemblyCode* GenerateReturnStatement(ReturnStatementNode* statement);
    AssemblyCode* GenerateWhileStatement(WhileStatementNode* whileStatement);
    AssemblyCode* GenerateForStatement(ForStatementNode* forStatement);
    AssemblyCode* GenerateContinueStatement(ContinueStatementNode* statement);
    AssemblyCode* GenerateBreakStatement(BreakStatementNode* statement);


    AssemblyCode* GenerateExpression(AbstractExpressionNode* expression);

    AssemblyCode* GenerateAssignment(AssignmentNode* assignment);
    AssemblyCode* GenerateBinaryOperation(OperatorExpressionNode* binaryOperation);
    AssemblyCode* GenerateUnaryOperation(UnaryExpressionNode* unaryOperation);

}SyntaxTreeTraverser;


std::shared_ptr<AssemblyCode> SyntaxTreeTraverser::GenerateCode(SyntaxTree* syntaxTree)
{
    codeGenerator = CodeGenerator(); // Initialize code generator

    return std::shared_ptr<AssemblyCode>(GenerateCodeBlock(syntaxTree->GetCodeBlock()));
}

AssemblyCode* SyntaxTreeTraverser::GenerateCodeBlock(CodeblockNode* codeBlock)
{
    AssemblyCode* assemblyCode = new AssemblyCode();

    for (size_t i = 0; i < codeBlock->GetLineCount(); i++)
    {
        assemblyCode->AddLines(GenerateLine(codeBlock->GetLine(i)));
    }

    return assemblyCode;
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
    return GenerateStatement(dynamic_cast<AbstractStatementNode*>(line), false);
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
    //FIXME: AddVariable should also return assembly code
    Variable* variable = codeGenerator.AddVariable(declaration->name, declaration->type.GetIdentfier());

    //TODO: Evaluate value
    AssemblyCode* assemblyCode = codeGenerator.AssignExpressionOutToVariable(declaration->name);
    return assemblyCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateFuncDeclaration(FuncDeclarationNode* declaration)
{
    Function* function;

    if (declaration->returnType.IsVoid())
    {
        function = codeGenerator.AddVoidFunction(declaration->name);
    }
    else
    {
        function = codeGenerator.AddFunction(declaration->name, declaration->returnType.GetIdentfier());
    }

    codeGenerator.PushEnvironment(std::make_shared<FunctionScopeEnvironment>());
    AssemblyCode* body = GenerateStatement(declaration->statement, true); // Lock environment as function environment was already created
    codeGenerator.PopEnvironment();

    AssemblyCode* assemblyCode = codeGenerator.SetFunctionBody(function, body);
    return assemblyCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateClassDeclaration(ClassDeclarationNode* declaration)
{
    Type* type = codeGenerator.AddType(declaration->name);
    ClassScopeEnvironment* classScopeEnvironment = codeGenerator.AddClassScopeEnvironmentToType(type);
    codeGenerator.PushEnvironment(std::shared_ptr<ScopeSpecificEnvironment>(classScopeEnvironment));
    //TODO: Generate Body
    return nullptr;
}


#pragma endregion

#pragma region Statements

AssemblyCode* SyntaxTreeTraverser::GenerateStatement(AbstractStatementNode* statement, bool environmentLock)
{
    if (dynamic_cast<EmptyStatementNode*>(statement) != nullptr)
    {
        return nullptr; // No code if empty statement
    }

    if (dynamic_cast<BodyNode*>(statement) != nullptr)
    {
        if (!environmentLock)
        {
            // TODO: New environment; where does it know what type of environment to create?
            codeGenerator.PushEnvironment(std::make_shared<ScopeSpecificEnvironment>());
            AssemblyCode* body = GenerateBody(dynamic_cast<BodyNode*>(statement));
            codeGenerator.PopEnvironment();
            return body;
        }

        return GenerateBody(dynamic_cast<BodyNode*>(statement));
    }

    if (dynamic_cast<AbstractKeywordStatementNode*>(statement) != nullptr)
    {
        return GenerateKeywordStatement(dynamic_cast<AbstractKeywordStatementNode*>(statement));
    }

    if (dynamic_cast<AbstractExpressionNode*>(statement) != nullptr)
    {
        return GenerateExpression(dynamic_cast<AbstractExpressionNode*>(statement));
    }

    //TODO: Check for other types of statements

    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateBody(BodyNode* body)
{
    // TODO: New environment; where does it know what type of environment to create?
    return GenerateCodeBlock(body->GetCodeBlock());
}


#pragma region Keyword statements

AssemblyCode* SyntaxTreeTraverser::GenerateKeywordStatement(AbstractKeywordStatementNode* statement)
{
    if (dynamic_cast<IfStatementNode*>(statement) != nullptr)
    {
        return GenerateIfStatement(dynamic_cast<IfStatementNode*>(statement));
    }

    if (dynamic_cast<ReturnStatementNode*>(statement) != nullptr)
    {
        return GenerateReturnStatement(dynamic_cast<ReturnStatementNode*>(statement));
    }

    if (dynamic_cast<WhileStatementNode*>(statement) != nullptr)
    {
        return GenerateWhileStatement(dynamic_cast<WhileStatementNode*>(statement));
    }

    if (dynamic_cast<ForStatementNode*>(statement) != nullptr)
    {
        return GenerateForStatement(dynamic_cast<ForStatementNode*>(statement));
    }

    if (dynamic_cast<ContinueStatementNode*>(statement) != nullptr)
    {
        return GenerateContinueStatement(dynamic_cast<ContinueStatementNode*>(statement));
    }

    if (dynamic_cast<BreakStatementNode*>(statement) != nullptr)
    {
        return GenerateBreakStatement(dynamic_cast<BreakStatementNode*>(statement));
    }

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
    //TODO: Generate expression code
    AssemblyCode* returnCode = codeGenerator.GenerateReturnStatement(nullptr);
    return returnCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateWhileStatement(WhileStatementNode* whileStatement)
{
    //TODO: assembly code and variablegetter for expression
    // Condition evaluated before InitWhile as InitWhile creates the while scope
    codeGenerator.InitLoopEnvironment();
    
    AssemblyCode* body = GenerateStatement(whileStatement->statement, true);
    return codeGenerator.GenerateWhile(nullptr, body);
}

AssemblyCode* SyntaxTreeTraverser::GenerateForStatement(ForStatementNode* forStatement)
{
    codeGenerator.InitLoopEnvironment();

    AssemblyCode* declaration = GenerateVarDeclaration(forStatement->initialization);
    //TODO: assembly code and variablegetter for condition
    AssemblyCode* increment = GenerateStatement(forStatement->increment, true);
    AssemblyCode* body = GenerateStatement(forStatement->statement, true);

    return codeGenerator.GenerateFor(declaration, nullptr, increment, body);
}

AssemblyCode* SyntaxTreeTraverser::GenerateContinueStatement(ContinueStatementNode* statement)
{
    return codeGenerator.GenerateContinueStatement();
}

AssemblyCode* SyntaxTreeTraverser::GenerateBreakStatement(BreakStatementNode* statement)
{
    return codeGenerator.GenerateBreakStatement();
}

#pragma endregion

#pragma endregion

#pragma region Expressions

AssemblyCode* SyntaxTreeTraverser::GenerateExpression(AbstractExpressionNode* expression)
{
    if (dynamic_cast<AssignmentNode*>(expression) != nullptr)
    {
        return GenerateAssignment(dynamic_cast<AssignmentNode*>(expression));
    }

    if (dynamic_cast<OperatorExpressionNode*>(expression) != nullptr)
    {
        return GenerateBinaryOperation(dynamic_cast<OperatorExpressionNode*>(expression));
    }

    if (dynamic_cast<UnaryExpressionNode*>(expression) != nullptr)
    {
        return GenerateUnaryOperation(dynamic_cast<UnaryExpressionNode*>(expression));
    }

    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateAssignment(AssignmentNode* assignment)
{
    AssemblyCode* assemblyCode = GenerateExpression(assignment->value); // Evaluate value

    for (Assignment* assignment : assignment->assignments)
    {
        EAssignOperators assignOperator = assignment->assignOperator;

        if (assignOperator == EAssignOperators::ASSIGN)
        {
            assemblyCode->AddLines(codeGenerator.AssignExpressionOutToVariable(assignment->variableName));
            continue;
        }

        ECodeGeneratorExpressionOperators codeGeneratorOperator;

        switch (assignOperator)
        {
        case EAssignOperators::ADD_ASSIGN: codeGeneratorOperator = ECodeGeneratorExpressionOperators::ADD;
        case EAssignOperators::SUB_ASSIGN: codeGeneratorOperator = ECodeGeneratorExpressionOperators::SUB;
        case EAssignOperators::MUL_ASSIGN: codeGeneratorOperator = ECodeGeneratorExpressionOperators::MUL;
        case EAssignOperators::DIV_ASSIGN: codeGeneratorOperator = ECodeGeneratorExpressionOperators::DIV;
        case EAssignOperators::MOD_ASSIGN: codeGeneratorOperator = ECodeGeneratorExpressionOperators::MOD;
        }

        assemblyCode->AddLines(codeGenerator.PerformOperation_LVariable_RExpressionOut(assignment->variableName, codeGeneratorOperator));
        assemblyCode->AddLines(codeGenerator.AssignExpressionOutToVariable(assignment->variableName));
    }

    return assemblyCode;
}

AssemblyCode* SyntaxTreeTraverser::GenerateBinaryOperation(OperatorExpressionNode* binaryOperation)
{
    return nullptr;
}

AssemblyCode* SyntaxTreeTraverser::GenerateUnaryOperation(UnaryExpressionNode* unaryOperation)
{
    return nullptr;
}

#pragma endregion