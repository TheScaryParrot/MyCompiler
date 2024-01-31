#include "PrintInstruction.hpp"

std::string PrintInstruction::GetAssemblyCode(unsigned int line, std::string precedingSpaces, std::vector<std::string> arguments, std::string comment)
{
    std::string result = "";

    if (comment != "")
    {
        result += precedingSpaces + comment + "\n";
    }

    result +=   precedingSpaces + "mov rax, 1 \n" +
                precedingSpaces + "mov rdi, 1 \n" +
                precedingSpaces + "mov rsi, " + arguments[0] + "\n" +
                precedingSpaces + "mov rdx, " + arguments[1] + "\n" +
                precedingSpaces + "syscall";

    return result;
}