#include "ExitInstruction.hpp"

std::string ExitInstruction::GetAssemblyCode(unsigned int line, std::string precedingSpaces, std::vector<std::string> arguments, std::string comment)
{
    CodeBlockHolder result = CodeBlockHolder(precedingSpaces);

    if (comment != "")
    {
        result.AddLine(comment);
    }

    result.AddLine("mov rax, 60");
    result.AddLine("mov rdi, " + arguments[0]);
    result.AddLine("syscall");

    return result.GetString();
}