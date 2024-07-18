#pragma once

#include <memory>
#include <vector>

#include "line/declaration/PropertyDeclarationNode.cpp"

class TypeDefCodeNode : AbstractTreeNode
{
   public:
    ~TypeDefCodeNode()
    {
        for (auto& line : lines)
        {
            delete line;
        }
    }

    void AddProperty(PropertyDeclarationNode* line);
    PropertyDeclarationNode* GetProperty(int index);
    unsigned int GetLineCount();

    std::string ToString();

   private:
    std::vector<PropertyDeclarationNode*> lines;
};

void TypeDefCodeNode::AddProperty(PropertyDeclarationNode* codeLine) { lines.push_back(codeLine); }

PropertyDeclarationNode* TypeDefCodeNode::GetProperty(int index) { return lines[index]; }

unsigned int TypeDefCodeNode::GetLineCount() { return lines.size(); }

std::string TypeDefCodeNode::ToString()
{
    std::string result = "{\n";

    for (auto& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}