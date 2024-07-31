#pragma once

#include "../../../assembly/AssemblyInstructionLine.cpp"
#include "PrimitiveType.cpp"

class BoolType : public PrimitiveType
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
        Logger.Log("Cannot add two bools", Logger::ERROR);
    }
    virtual void GenerateSub(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot subtract two bools", Logger::ERROR);
    }
    virtual void GenerateMul(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot multiply two bools", Logger::ERROR);
    }
    virtual void GenerateDiv(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot divide two bools", Logger::ERROR);
    }
    virtual void GenerateMod(std::shared_ptr<IVariableLocation> destination, std::shared_ptr<IVariableLocation> source,
                             AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot mod two bools", Logger::ERROR);
    }

    virtual void GenerateNot(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("not");
        line->AddArgument(ConstructVarLocationAccess(destination));
        assemblyCode->AddLine(line);
    }
    virtual void GenerateNeg(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot negate a bool", Logger::ERROR);
    }
    virtual void GenerateInc(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot increment a bool", Logger::ERROR);
    }
    virtual void GenerateDec(std::shared_ptr<IVariableLocation> destination, AssemblyCode* assemblyCode) override
    {
        Logger.Log("Cannot decrement a bool", Logger::ERROR);
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
        // As push requires 32-bit register, we do a direct mov to the stack
        std::shared_ptr<IVariableLocation> stackVar =
            std::shared_ptr<IVariableLocation>(AssemblyCodeGenerator.GetNewLocalVarLocation(this->GetSize(), assemblyCode));
        GenerateAssign(stackVar, source, assemblyCode);
    }

    virtual unsigned int GetSize() override { return 1; }
};