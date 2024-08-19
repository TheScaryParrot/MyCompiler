#pragma once

#include <map>
#include <string>

#include "Instruction.cpp"

static class InstructionHandler
{
   private:
    std::map<std::string, Instruction> instructions = {{"debug", Instruction([]() {}, []() {})}};

   public:
    Instruction* GetInstruction(std::string name)
    {
        auto instructionPair = this->instructions.find(name);

        if (instructionPair == this->instructions.end()) nullptr;

        return &instructionPair->second;
    }
} InstructionHandler;