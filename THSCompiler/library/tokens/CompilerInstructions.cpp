#pragma once

#include "AbstractCompilerInstructionToken.cpp"

static class CompilerInstructions
{
   public:
    std::shared_ptr<AbstractCompilerInstructionToken> EXTERN_INSTRUCTION = std::make_shared<AbstractCompilerInstructionToken>("extern");
    std::shared_ptr<AbstractCompilerInstructionToken> GLOBAL_INSTRUCTION = std::make_shared<AbstractCompilerInstructionToken>("global");

    std::shared_ptr<AbstractCompilerInstructionToken> GetCompilerInstructionToken(std::string instruction)
    {
        if (EXTERN_INSTRUCTION->IsThisInstruction(instruction))
        {
            return EXTERN_INSTRUCTION;
        }

        if (GLOBAL_INSTRUCTION->IsThisInstruction(instruction))
        {
            return GLOBAL_INSTRUCTION;
        }

        return nullptr;
    }
} CompilerInstructions;