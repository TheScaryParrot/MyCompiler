#include "PrintInstruction.hpp"

std::string PrintInstruction::GetAssemblyCode(unsigned int line, std::vector<std::string> arguments, std::string comment)
{
    std::string result = "";

    if (comment != "")
    {
        result += comment + "\n";
    }

    result +=   "mov rax, 1 \n"
                "mov rdi, 1 \n"
                "mov rsi, " + arguments[0] + "\n"
                "mov rdx, " + arguments[1] + "\n"
                "syscall";

    return result;
}