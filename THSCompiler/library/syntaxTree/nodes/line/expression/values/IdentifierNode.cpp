#pragma once

#include "AbstractValueNode.cpp"

/// @brief Represents a value node that holds an ID. Essentially a mutable
class IdentifierNode : public AbstractValueNode
{
   public:
    IdentifierNode(std::string id);

    virtual std::string ToString() override;

    std::string id;
};

IdentifierNode::IdentifierNode(std::string id) { this->id = id; }

std::string IdentifierNode::ToString() { return id; }