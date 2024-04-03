#pragma once

#include "../AbstractValueNode.cpp"

/// @brief Represents a value node that holds an ID. Essentially a mutable
class IDValueNode : public AbstractValueNode
{
public:
    IDValueNode(std::string id);
    ~IDValueNode();

    std::string GetValue();

    virtual std::string ToString() override; 

private:
    std::string id;
};

IDValueNode::IDValueNode(std::string id)
{
    this->id = id;
}

IDValueNode::~IDValueNode()
{
}

std::string IDValueNode::GetValue()
{
    return id;
}

std::string IDValueNode::ToString()
{
    return id;
}