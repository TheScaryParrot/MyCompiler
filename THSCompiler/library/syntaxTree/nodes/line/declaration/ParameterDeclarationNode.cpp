#pragma once

#include "AbstractDeclarationNode.cpp"
#include "DeclarationAttributes.cpp"

class ParameterDeclarationNode : public AbstractDeclarationNode
{
   public:
    ParameterDeclarationNode(DeclarationAttributes attributes, std::string type, std::string name);
    ~ParameterDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    std::string type;

    DeclarationAttributes attributes;
};

ParameterDeclarationNode::ParameterDeclarationNode(DeclarationAttributes attributes, std::string type, std::string name) : AbstractDeclarationNode()
{
    this->attributes = attributes;
    this->type = type;
    this->name = name;
}

ParameterDeclarationNode::~ParameterDeclarationNode() {}

std::string ParameterDeclarationNode::ToString() { return "param: " + attributes.ToString() + type + " " + name; }