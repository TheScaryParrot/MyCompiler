#pragma once

#include <memory>
#include <vector>

#include "line/declaration/PropertyDeclarationNode.cpp"

class TypeDefCodeNode : AbstractTreeNode
{
   public:
    void AddProperty(PropertyDeclarationNode* line);
    PropertyDeclarationNode* GetProperty(int index);
    unsigned int GetLineCount();

    std::string ToString();

   private:
    std::vector<std::unique_ptr<PropertyDeclarationNode>> lines;
};

void TypeDefCodeNode::AddProperty(PropertyDeclarationNode* codeLine) { lines.push_back(std::unique_ptr<PropertyDeclarationNode>(codeLine)); }

PropertyDeclarationNode* TypeDefCodeNode::GetProperty(int index) { return lines[index].get(); }

unsigned int TypeDefCodeNode::GetLineCount() { return lines.size(); }

std::string TypeDefCodeNode::ToString()
{
    std::string result = "{\n";

    for (std::unique_ptr<PropertyDeclarationNode>& line : lines)
    {
        result += "\t" + line->ToString() + "\n";
    }

    result += "}";

    return result;
}