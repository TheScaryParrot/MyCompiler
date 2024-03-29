#include "PrintInstruction.hpp"

std::string PrintInstruction::GetAssemblyCode(unsigned int line, std::string precedingSpaces, std::vector<std::string> arguments, std::string comment)
{
    CodeBlockHolder result = CodeBlockHolder(precedingSpaces);

    if (comment != "")
    {
        result.AddLine(comment);
    }

    result.AddLine("mov rax, 1");
    result.AddLine("mov rdi, 1");
    result.AddLine("mov rsi, " + arguments[0]);
    result.AddLine("mov rdx, " + arguments[1]);
    result.AddLine("syscall");

    return result.GetString();
}