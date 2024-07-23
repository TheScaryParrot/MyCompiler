#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class FloatType : public PrimitiveType
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
        // TODO: Add add instruction
    }

    virtual void GenerateSub(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add sub instruction
    }

    virtual void GenerateMul(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add mul instruction
    }

    virtual void GenerateDiv(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add div instruction
    }

    virtual void GenerateMod(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add mod instruction
    }

    virtual void GenerateNot(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add not instruction
    }

    virtual void GenerateNeg(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add neg instruction
    }

    virtual void GenerateInc(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add inc instruction
    }

    virtual void GenerateDec(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        // TODO: Add dec instruction
    }

    virtual void GenerateAnd(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add and instruction
    }

    virtual void GenerateOr(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        // TODO: Add or instruction
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