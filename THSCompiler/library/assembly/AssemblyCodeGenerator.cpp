#pragma once

#include "../codeGenerator/varLocation/RegistryPointerVarLocation.cpp"
#include "../codeGenerator/varLocation/RegistryVarLocation.cpp"
#include "AssemblyCode.cpp"
#include "AssemblyInstructionLine.cpp"

static class AssemblyCodeGenerator
{
   private:
    int localVariableOffset = 0;
    int parameterOffset = 4;

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

    IVariableLocation* GetNewRegistryVarLocation(unsigned int size, AssemblyCode* assemblyCode)
    {
        switch (size)
        {
            case 1:
                return new RegistryVarLocation("al");
            case 2:
                return new RegistryVarLocation("ax");
            case 4:
                return new RegistryVarLocation("eax");
            case 8:
                return new RegistryVarLocation("rax");
        }

        Logger.Log("Invalid size for registry variable location " + std::to_string(size), Logger::ERROR);
        return nullptr;
    }

    IVariableLocation* GetNewLocalVarLocation(unsigned int size, AssemblyCode* assemblyCode)
    {
        DecrementRSP(size, assemblyCode);
        RegistryPointerVarLocation* location = new RegistryPointerVarLocation("rbp", -localVariableOffset);
        localVariableOffset += size;
        return location;
    }
    void ClearLocalVariableCounter() { localVariableOffset = 0; }

    IVariableLocation* GetNewParameterLocation(unsigned int size, AssemblyCode* assemblyCode)
    {
        RegistryPointerVarLocation* location = new RegistryPointerVarLocation("rbp", parameterOffset);
        parameterOffset += size;
        return location;
    }
    void ClearParameterCounter() { parameterOffset = 4; }
} AssemblyCodeGenerator;