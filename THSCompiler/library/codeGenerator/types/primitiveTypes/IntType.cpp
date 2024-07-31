#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class IntType : public PrimitiveType
{
    virtual void GenerateAssign(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("mov");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateAdd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("add");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("sub");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("mul");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("div");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        // TODO: Add mod instruction
    }

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("not");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("neg");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("inc");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("dec");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateAnd(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("and");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateOr(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                            AssemblyCode* assemblyCode) override
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("or");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                               AssemblyCode* assemblyCode) override
    {
        GenerateComparison("e", destination, source, assemblyCode);
    }

    virtual void GenerateNotEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                  AssemblyCode* assemblyCode) override
    {
        GenerateComparison("ne", destination, source, assemblyCode);
    }

    virtual void GenerateLess(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                              AssemblyCode* assemblyCode) override
    {
        GenerateComparison("l", destination, source, assemblyCode);
    }

    virtual void GenerateLessEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                   AssemblyCode* assemblyCode) override
    {
        GenerateComparison("le", destination, source, assemblyCode);
    }

    virtual void GenerateGreater(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                 AssemblyCode* assemblyCode) override
    {
        GenerateComparison("g", destination, source, assemblyCode);
    }

    virtual void GenerateGreaterEqual(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                                      AssemblyCode* assemblyCode) override
    {
        GenerateComparison("ge", destination, source, assemblyCode);
    }

    virtual void GenerateStackPush(std::shared_ptr<IVariableLocation> source, AssemblyCode* assemblyCode) override
    {
        // although push is possible (not like in BoolType, see BoolType.cpp), for consistency with the rest of the code, I do this
        std::shared_ptr<IVariableLocation> stackVar =
            std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewLocalVarLocation(this->GetSize(), assemblyCode));
        GenerateAssign(stackVar, source, assemblyCode);
    }

    virtual unsigned int GetSize() override { return 4; }
};