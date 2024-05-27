#include "CodeGenerator.hpp"

#include "../../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"

AssemblyCode* CodeGenerator::GenerateStatement(AbstractStatementNode* statement)
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

AssemblyCode* CodeGenerator::GenerateBody(BodyNode* body)
{
    // TODO: New environment; where does it know what type of environment to create?
    // TODO: Generate body code
    return nullptr;
}

#pragma region Keyword statements

AssemblyCode* CodeGenerator::GenerateKeywordStatement(AbstractKeywordStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateIfStatement(IfStatementNode* statement)
{
    // TODO: Get label for final
    return GenerateIfStatement(statement, "final");
}

AssemblyCode* CodeGenerator::GenerateIfStatement(IfStatementNode* statement, std::string finalLabel)
{
    // TODO: Generate if statement
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateReturnStatement(ReturnStatementNode* statement)
{
    //TODO: Get return Variable from Environment
    //TODO: Assign return Variable to return value
    //TODO: Write RET instruction
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateWhileStatement(WhileStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateForStatement(ForStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateContinueStatement(ContinueStatementNode* statement)
{
    return nullptr;
}

AssemblyCode* CodeGenerator::GenerateBreakStatement(BreakStatementNode* statement)
{
    return nullptr;
}

#pragma endregion