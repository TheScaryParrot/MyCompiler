#pragma once

#include "../../declaration/AbstractVarDeclarationNode.cpp"
#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ForStatementNode : public AbstractKeywordStatementNode
{
   public:
    ForStatementNode(AbstractVarDeclarationNode* initialization, AbstractExpressionNode* condition, AbstractStatementNode* increment,
                     AbstractStatementNode* statement);
    ~ForStatementNode();

    virtual std::string ToString() override;

    AbstractVarDeclarationNode* initialization;
    AbstractExpressionNode* condition;
    AbstractStatementNode* increment;
    AbstractStatementNode* statement;
};

ForStatementNode::ForStatementNode(AbstractVarDeclarationNode* initialization, AbstractExpressionNode* condition, AbstractStatementNode* increment,
                                   AbstractStatementNode* statement)
    : AbstractKeywordStatementNode()
{
    this->initialization = initialization;
    this->condition = condition;
    this->increment = increment;
    this->statement = statement;
}

ForStatementNode::~ForStatementNode()
{
    delete initialization;
    delete condition;
    delete increment;
    delete statement;
}

std::string ForStatementNode::ToString()
{
    return "for (" + initialization->ToString() + " " + condition->ToString() + "; " + increment->ToString() + ";)\n" + statement->ToString();
}
