#pragma once

#include "../codeGenerator/varLocation/RegistryPointerVarLocation.cpp"
#include "../codeGenerator/varLocation/RegistryVarLocation.cpp"
#include "AssemblyCode.cpp"
#include "AssemblyInstructionLine.cpp"

static class AssemblyCodeGenerator
{
   private:
    int localVariableOffset = 0;
    int parameterOffset = 16;

   public:
    void IncrementRSP(int increment, AssemblyCode* assemblyCode)
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("add");
        line->AddArgument("rsp");
        line->AddArgument(std::to_string(increment));
        assemblyCode->AddLine(line);
    }
    void ChangeLocalVarOffset(int change) { localVariableOffset += change; }

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
        localVariableOffset += size;
        return new RegistryPointerVarLocation("rbp", -localVariableOffset);
    }
    void ClearLocalVariableCounter() { localVariableOffset = 0; }

    IVariableLocation* GetNewParameterLocation(unsigned int size, AssemblyCode* assemblyCode)
    {
        RegistryPointerVarLocation* location = new RegistryPointerVarLocation("rbp", parameterOffset);
        parameterOffset += size;
        return location;
    }
    void ClearParameterCounter() { parameterOffset = 16; }

    IVariableLocation* GetReturnLocation(unsigned int size, AssemblyCode* assemblyCode) { return new RegistryPointerVarLocation("rbp", -size); }
    void MoveReturnLocationToRax(unsigned int returnTypeSize, AssemblyCode* assemblyCode)
    {
        AssemblyInstructionLine* line = new AssemblyInstructionLine("mov");
        line->AddArgument("rax");
        line->AddArgument("rbp");
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("sub");
        line->AddArgument("rax");
        line->AddArgument(std::to_string(returnTypeSize));
        assemblyCode->AddLine(line);
    }

    /// @brief Adds code that is need at the start of the _start function
    void AddPreStartBody(AssemblyCode* assemblyCode)
    {
        // set rbp to rsp
        AssemblyInstructionLine* line = new AssemblyInstructionLine("mov");
        line->AddArgument("rbp");
        line->AddArgument("rsp");
        assemblyCode->AddLine(line);
    }
    /// @brief Adds code that is need at the end of the _start function
    void AddPostStartBody(AssemblyCode* assemblyCode)
    {
        // exit syscall
        AssemblyInstructionLine* line = new AssemblyInstructionLine("mov");
        line->AddArgument("eax");
        line->AddArgument("60");
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("xor");
        line->AddArgument("edi");
        line->AddArgument("edi");
        assemblyCode->AddLine(line);

        line = new AssemblyInstructionLine("syscall");
        assemblyCode->AddLine(line);
    }

    void AddPreCall(AssemblyCode* assemblyCode)
    {
        // push rbp
        AssemblyInstructionLine* line = new AssemblyInstructionLine("push");
        line->AddArgument("rbp");
        assemblyCode->AddLine(line);
    }
    void AddPostCall(AssemblyCode* assemblyCode)
    {
        // pop rbp
        AssemblyInstructionLine* line = new AssemblyInstructionLine("pop");
        line->AddArgument("rbp");
        assemblyCode->AddLine(line);
    }

    void AddPreBody(AssemblyCode* assemblyCode)
    {
        // set rbp to rsp
        AssemblyInstructionLine* line = new AssemblyInstructionLine("mov");
        line->AddArgument("rbp");
        line->AddArgument("rsp");
        assemblyCode->AddLine(line);
    }
    void AddPostBody(AssemblyCode* assemblyCode)
    {
        // forget about local variables
        AssemblyInstructionLine* line = new AssemblyInstructionLine("mov");
        line->AddArgument("rsp");
        line->AddArgument("rbp");
        assemblyCode->AddLine(line);
    }
} AssemblyCodeGenerator;