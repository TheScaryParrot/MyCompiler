#pragma once

#include "AbstractDeclarationNode.cpp"

class ClassDeclarationNode : public AbstractDeclarationNode
{
public:
    ClassDeclarationNode(bool isStatic, std::string name);
    ~ClassDeclarationNode();

    virtual std::string ToString() override;

private:
    std::string name;
    bool isStatic;
};

ClassDeclarationNode::ClassDeclarationNode(bool isStatic, std::string name) : AbstractDeclarationNode()
{
    this->isStatic = isStatic;
    this->name = name;
}

ClassDeclarationNode::~ClassDeclarationNode()
{
}

std::string ClassDeclarationNode::ToString()
{
    std::string result = "";

    if (isStatic)
    {
        result += "static ";
    }

    result += "class " + name;

    return result;
}