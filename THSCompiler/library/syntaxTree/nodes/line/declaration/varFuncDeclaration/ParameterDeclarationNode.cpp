#pragma once

#include "../../../AbstractTreeNode.cpp"
#include "declarationAttributes/SyntaxTreeParamAttributes.cpp"

class ParameterDeclarationNode : public AbstractTreeNode
{
   public:
    ParameterDeclarationNode(SyntaxTreeParamAttributes attributes, std::string type, std::string name);
    ~ParameterDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    std::string type;

    SyntaxTreeParamAttributes attributes;
};

ParameterDeclarationNode::ParameterDeclarationNode(SyntaxTreeParamAttributes attributes, std::string type,
                                                   std::string name)
    : AbstractTreeNode()
{
    this->attributes = attributes;
    this->type = type;
    this->name = name;
}

ParameterDeclarationNode::~ParameterDeclarationNode() {}

std::string ParameterDeclarationNode::ToString() { return attributes.ToString() + type + " " + name; }