#pragma once

#include <string>

class AssemblyInstruction
{
   public:
    AssemblyInstruction() = default;
    AssemblyInstruction(std::string instruction) { this->instruction = instruction; };
    std::string ToString() { return instruction; };

   private:
    std::string instruction;
};