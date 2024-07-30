#pragma once

#include "../Type.cpp"

class PrimitiveType : public Type
{
   protected:
    std::string ConstructVarLocationAccess(IVariableLocation* location)
    {
        std::string result = location->ToAssemblyString();

        if (location->RequiresSizeKeyword())
        {
            result = GetSizeKeyword() + " " + result;
        }

        return result;
    }

    void GenerateComparison(std::string comparison, IVariableLocation* destination, IVariableLocation* source, AssemblyCode* assemblyCode)
    {
        if (destination->RequiresRegister() && source->RequiresRegister())
        {
            source = ShortSafeIVarlocationOfThisTypeInRegister(source, assemblyCode);
        }

        AssemblyInstructionLine* line = new AssemblyInstructionLine("cmp");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument(ConstructVarLocationAccess(source));
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("set" + comparison);
        line->AddArgument("al");
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("movzx");
        line->AddArgument(ConstructVarLocationAccess(destination));
        line->AddArgument("al");
        assemblyCode->AddLine(line);
    }

   private:
    std::string GetSizeKeyword()
    {
        switch (this->GetSize())
        {
            case 1:
                return "byte";
            case 2:
                return "word";
            case 4:
                return "dword";
            case 8:
                return "qword";
        }

        Logger.Log("Cannot get size keyword as argument size is not 1, 2, 4 or 8", Logger::ERROR);
        return "";
    }
};