#include "CodeGenerator.hpp"

#include "../../syntaxTree/nodes/line/statement/EmptyStatementNode.cpp"

AssemblyCode* CodeGenerator::GenerateStatement(AbstractStatementNode* statement)
{
    // TODO: Generate statement
    if (typeid(*statement) == typeid(EmptyStatementNode))
    {
        return nullptr; // No code if empty statement
    }

    if (typeid(*statement) == typeid(BodyNode))
    {
        return GenerateBody(dynamic_cast<BodyNode*>(statement));
    }

    if (typeid(*statement) == typeid(AbstractKeywordStatementNode))
    {
        return GenerateKeywordStatement(dynamic_cast<AbstractKeywordStatementNode*>(statement));
    }

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

}

AssemblyCode* CodeGenerator::GenerateIfStatement(IfStatementNode* statement)
{
    // TODO: Get label for final
    return GenerateIfStatement(statement, "final");
}

AssemblyCode* CodeGenerator::GenerateIfStatement(IfStatementNode* statement, std::string finalLabel)
{
    // TODO: Generate if statement
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

}

AssemblyCode* CodeGenerator::GenerateForStatement(ForStatementNode* statement)
{

}

AssemblyCode* CodeGenerator::GenerateContinueStatement(ContinueStatementNode* statement)
{

}

AssemblyCode* CodeGenerator::GenerateBreakStatement(BreakStatementNode* statement)
{

}

#pragma endregion