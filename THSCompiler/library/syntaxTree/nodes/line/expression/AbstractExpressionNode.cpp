#pragma once

#include "../statement/AbstractStatementNode.cpp"

/// @brief Node used for everything that is an expression. So also sumExp or unaryExp
class AbstractExpressionNode : public AbstractStatementNode
{
   public:
    virtual bool RequiresAXRegister() = 0;

    virtual std::shared_ptr<Variable> TraverseExpression(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) = 0;

    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override { TraverseExpression(codeGenerator, assemblyCode); }
};