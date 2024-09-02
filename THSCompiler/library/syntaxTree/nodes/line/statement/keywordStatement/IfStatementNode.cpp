#pragma once

#include <vector>

#include "../../expression/AbstractExpressionNode.cpp"
#include "AbstractKeywordStatementNode.cpp"
#include "ElifStatementNode.cpp"

class IfStatementNode : public AbstractKeywordStatementNode
{
   public:
    IfStatementNode(AbstractExpressionNode* expression, AbstractStatementNode* statement, std::vector<ElifStatementNode*> elifStatements,
                    AbstractStatementNode* elseStatement)
        : AbstractKeywordStatementNode()
    {
        this->expression = expression;
        this->statement = statement;
        this->elifStatements = elifStatements;
        this->elseStatement = elseStatement;
    }

    ~IfStatementNode()
    {
        delete expression;
        delete statement;

        for (ElifStatementNode* elifStatement : elifStatements)
        {
            delete elifStatement;
        }

        delete elseStatement;
    }
    virtual void Traverse(CodeGenerator* codeGenerator, AssemblyCode* assemblyCode) override
    {
        std::string endLabel = AssemblyCodeGenerator.GetNewJumpLabel();

        std::vector<std::string> elseLabels;

        for (ElifStatementNode* elif : this->elifStatements)
        {
            elseLabels.push_back(AssemblyCodeGenerator.GetNewJumpLabel());
        }

        if (this->elseStatement != nullptr)
        {
            elseLabels.push_back(AssemblyCodeGenerator.GetNewJumpLabel());
        }

        elseLabels.push_back(endLabel);

        std::shared_ptr<Variable> condition = this->expression->TraverseExpression(codeGenerator, assemblyCode);
        codeGenerator->GenerateConditionalJump(condition, elseLabels[0], assemblyCode);

        this->statement->Traverse(codeGenerator, assemblyCode);
        assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + endLabel));

        unsigned int elseCounter = 0;

        for (ElifStatementNode* elif : this->elifStatements)
        {
            assemblyCode->AddLine(new AssemblyLabelLine(elseLabels[elseCounter]));

            std::shared_ptr<Variable> elifCondition = elif->expression->TraverseExpression(codeGenerator, assemblyCode);
            codeGenerator->GenerateConditionalJump(elifCondition, elseLabels[elseCounter + 1], assemblyCode);

            elif->statement->Traverse(codeGenerator, assemblyCode);
            assemblyCode->AddLine(new AssemblyInstructionLine("jmp " + endLabel));

            elseCounter++;
        }

        if (this->elseStatement != nullptr)
        {
            assemblyCode->AddLine(new AssemblyLabelLine(elseLabels[elseCounter]));

            this->elseStatement->Traverse(codeGenerator, assemblyCode);
        }

        assemblyCode->AddLine(new AssemblyLabelLine(endLabel));
    }

    virtual std::string ToString() override
    {
        std::string result = "if (";

        result += expression->ToString() + ")\n";
        result += statement->ToString();

        for (ElifStatementNode* elifStatement : elifStatements)
        {
            result += elifStatement->ToString();
        }

        if (elseStatement != nullptr)
        {
            result += "else\n";
            result += elseStatement->ToString();
        }

        return result;
    }

    AbstractExpressionNode* expression;
    AbstractStatementNode* statement;

    std::vector<ElifStatementNode*> elifStatements;

    AbstractStatementNode* elseStatement;
};