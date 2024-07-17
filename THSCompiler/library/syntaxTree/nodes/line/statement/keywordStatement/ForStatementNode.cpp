#pragma once

#include "../../declaration/VarDeclarationNode.cpp"
#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"

class ForStatementNode : public AbstractKeywordStatementNode
{
   public:
    ForStatementNode(VarDeclarationNode* initialization, AbstractExpressionNode* condition, AbstractStatementNode* increment,
                     AbstractStatementNode* statement);
    ~ForStatementNode();

    virtual std::string ToString() override;

    VarDeclarationNode* initialization;
    AbstractExpressionNode* condition;
    AbstractStatementNode* increment;
    AbstractStatementNode* statement;
};

ForStatementNode::ForStatementNode(VarDeclarationNode* initialization, AbstractExpressionNode* condition, AbstractStatementNode* increment,
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
