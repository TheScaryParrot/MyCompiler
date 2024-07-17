#pragma once

#include "../../TypeDefCodeNode.cpp"
#include "AbstractDeclarationNode.cpp"

class TypeDeclarationNode : public AbstractDeclarationNode
{
   public:
    std::string name;
    TypeDefCodeNode* typeDefCode;

    TypeDeclarationNode(std::string name, TypeDefCodeNode* typeDefCode) : AbstractDeclarationNode()
    {
        this->name = name;
        this->typeDefCode = typeDefCode;
    }

    virtual std::string ToString() override { return "typedef " + typeDefCode->ToString() + name + ";"; }
};