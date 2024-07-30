#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class BoolType : public PrimitiveType
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
        Logger.Log("Cannot add two bools", Logger::ERROR);
    }
    virtual void GenerateSub(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot subtract two bools", Logger::ERROR);
    }
    virtual void GenerateMul(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot multiply two bools", Logger::ERROR);
    }
    virtual void GenerateDiv(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot divide two bools", Logger::ERROR);
    }
    virtual void GenerateMod(IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot mod two bools", Logger::ERROR);
    }

    virtual void GenerateNot(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("not");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }
    virtual void GenerateNeg(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot negate a bool", Logger::ERROR);
    }
    virtual void GenerateInc(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot increment a bool", Logger::ERROR);
    }
    virtual void GenerateDec(IVariableLocation* destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot decrement a bool", Logger::ERROR);
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
        // As push requires 32-bit register, we do a direct mov to the stack
        IVariableLocation* stackVar = AssemblyCodeGenerator.GetNewLocalVarLocation(this->GetSize(), assemblyCode);
        GenerateAssign(stackVar, source, assemblyCode);
    }

    virtual unsigned int GetSize() override { return 1; }
};