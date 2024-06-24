#pragma once

#include "AbstractDeclarationNode.cpp"
#include "BodyNode.cpp"

class ClassDeclarationNode : public AbstractDeclarationNode
{
   public:
    ClassDeclarationNode(bool isStatic, std::string name, BodyNode* body);
    ~ClassDeclarationNode();

    virtual std::string ToString() override;

    std::string name;
    bool isStatic;
    BodyNode* body;
};

ClassDeclarationNode::ClassDeclarationNode(bool isStatic, std::string name, BodyNode* body) : AbstractDeclarationNode()
{
    this->isStatic = isStatic;
    this->name = name;
    this->body = body;
}

ClassDeclarationNode::~ClassDeclarationNode() { delete body; }

std::string ClassDeclarationNode::ToString()
{
    std::string result = "";

    if (isStatic)
    {
        result += "static ";
    }

    result += "class " + name + " " + body->ToString();

    return result;
}