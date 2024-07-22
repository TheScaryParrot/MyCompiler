#pragma once

#include "AssemblyCode.cpp"
#include "AssemblyInstructionLine.cpp"

class AssemblyCodeGenerator
{
   public:
    void IncrementRSP(int increment, AssemblyCode* assemblyCode)
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("add");
        line->AddArgument("rsp");
        line->AddArgument(std::to_string(increment));
        assemblyCode->AddLine(line);
    }

    void DecrementRSP(int decrement, AssemblyCode* assemblyCode)
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("sub");
        line->AddArgument("rsp");
        line->AddArgument(std::to_string(decrement));
        assemblyCode->AddLine(line);
    }
};