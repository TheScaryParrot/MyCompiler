#pragma once

#include <string>

class AssemblyCode
{
   public:
    void AddCode(std::string code);

    std::string GetCode();
    std::string ToString();

   private:
    std::string code = "";
};

void AssemblyCode::AddCode(std::string code)
{
    // Remove empty lines
    if (this->code.back() == '\n' && code.front() == '\n')
    {
        code = code.substr(1);
    }

    this->code += code;
}

std::string AssemblyCode::GetCode() { return code; }

std::string AssemblyCode::ToString() { return GetCode(); }
