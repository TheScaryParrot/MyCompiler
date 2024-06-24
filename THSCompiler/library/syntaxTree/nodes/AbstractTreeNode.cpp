#pragma once

#include <string>

class AbstractTreeNode
{
   public:
    AbstractTreeNode();
    virtual ~AbstractTreeNode();

    virtual std::string ToString() = 0;
};

AbstractTreeNode::AbstractTreeNode() {}

AbstractTreeNode::~AbstractTreeNode() {}