#pragma once

#include <vector>

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"
#include "ElifStatementNode.cpp"

class IfStatementNode : public AbstractKeywordStatementNode
{
   public:
    IfStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement,
                    std::vector<ElifStatementNode*>* elifStatements, AbstractStatementNode* elseStatement);
    ~IfStatementNode();

    virtual std::string ToString() override;

    AbstractExpressionNode* expression;
    AbstractStatementNode* statement;

    std::vector<ElifStatementNode*>* elifStatements;

    AbstractStatementNode* elseStatement;
};

IfStatementNode::IfStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement,
                                 std::vector<ElifStatementNode*>* elifStatements, AbstractStatementNode* elseStatement)
    : AbstractKeywordStatementNode()
{
    this->expression = expression;
    this->statement = statement;
    this->elifStatements = elifStatements;
    this->elseStatement = elseStatement;
}

IfStatementNode::~IfStatementNode()
{
    delete expression;
    delete statement;

    if (elifStatements != nullptr)
    {
        for (ElifStatementNode* elifStatement : *elifStatements)
        {
            delete elifStatement;
        }
        delete elifStatements;
    }

    delete elseStatement;
}

std::string IfStatementNode::ToString()
{
    std::string result = "if (";

    result += expression->ToString() + ")\n";
    result += statement->ToString();

    if (elifStatements != nullptr)
    {
        for (ElifStatementNode* elifStatement : *elifStatements)
        {
            result += elifStatement->ToString();
        }
    }

    if (elseStatement != nullptr)
    {
        result += "else\n";
        result += elseStatement->ToString();
    }

    return result;
}