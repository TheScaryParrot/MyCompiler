#pragma once

#include "AbstractCompilerInstructionNode.cpp"

class GlobalInstructionNode : public AbstractCompilerInstructionNode
{
   public:
    std::string identifier;

    GlobalInstructionNode(std::string identifier) : AbstractCompilerInstructionNode() { this->identifier = identifier; }

    virtual std::string ToString() override { return "global " + identifier; }
};