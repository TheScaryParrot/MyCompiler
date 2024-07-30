#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class IntType : public PrimitiveType
{
    virtual void GenerateAssign(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateAdd(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateSub(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateMul(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateDiv(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateMod(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add mod instruction
    }

    virtual void GenerateNot(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("not");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateNeg(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("neg");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateInc(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("inc");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateDec(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("dec");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }

    virtual void GenerateAnd(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateOr(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
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

    virtual void GenerateEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add equal instruction
    }

    virtual void GenerateNotEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add not equal instruction
    }

    virtual void GenerateLess(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add less instruction
    }

    virtual void GenerateLessEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add less equal instruction
    }

    virtual void GenerateGreater(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add greater instruction
    }

    virtual void GenerateGreaterEqual(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add greater equal instruction
    }

    virtual void GenerateStackPush(IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // although push is possible (not like in BoolType, see BoolType.cpp), for consistency with the rest of the code, I do this
        IVariableLocation* stackVar = AssemblyCodeGenerator.GetNewLocalVarLocation(this->GetSize(), assemblyCode);
        GenerateAssign(stackVar, source, assemblyCode);
    }

    virtual unsigned int GetSize() override { return 4; }
};